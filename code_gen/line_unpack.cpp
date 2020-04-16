#include "code_gen.h"
#include "symbol_associativity.h"
#include "postfix_it.h"

std::string ICG::CodeGenerator::unpack_line(Node line, bool is_conditional_block) {
    Node postfix_it(Node);
    std::string generated_code = "";
    // get the indent needed for the specific block this line is being dissected from
    std::string indent = "";

    for(int i=0; i<((is_conditional_block)? 1: INDENT); i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    Stack<char> ASSOC_STACK;    
    Node new_tree(false, "new_struct");
    bool is_assignment = false;
    bool op_found = false;
    Stack<Node> term_stack;
    Queue<Node> after_assignment_stack;

    for(Node children: line.get_children()) {
        
        if(children.is_terminal()) {
            
            if(children.get_name().compare("=") == 0) {
                is_assignment = true;
                continue;
            }

            if(!op_found)
                op_found = (
                    children.get_name().compare("+") == 0 ||
                    children.get_name().compare("-") == 0 ||
                    children.get_name().compare("*") == 0 ||
                    children.get_name().compare("/") == 0
                );

            if(children.get_name().compare(";") == 0)
                break;


        }

        if(is_assignment) {
            after_assignment_stack.enqueue(children);
        } else {
            term_stack.push(children);
        }

    }

    if(is_assignment) { // this is because we create two stacks if it is an asssignent
    
        std::string new_term_id = "";
        
        if(term_stack.get_stack().size() > 1) { // creates a new term id because this directly means this is an initialised var
            std::string t_id = get_term_id();
            new_term_id = t_id;

            NEW_VAR_LOOKUP.add_member(
                term_stack.get_stack().at(1).get_value(),
                term_stack.get_stack().at(0).get_value(),
                t_id
            );

        } else { // searches for the corresponding term_id since this is clearly not a new initialisation
            new_term_id = NEW_VAR_LOOKUP.find(term_stack.get_stack().at(0).get_value())[2];
        }

        if(op_found) {
            // create a new node that will hold the equation.
            // This equation will be rarranged to a postfix
            Node postfixed(false, "line"); 
            
            for(int i=0; i<after_assignment_stack.get_init_queue().size(); i++) {
                postfixed.add_children(after_assignment_stack.dequeue(Node(true, "something")));
            }
            
            postfixed = ICG::postfix_it(postfixed);

            generated_code = unpack_equation(postfixed, new_term_id, is_conditional_block);

        } else { // operation not found, hence must be a function call or intitialised to the value of another variable
            generated_code += (is_conditional_block) ? "    ": indent;
            generated_code += new_term_id;
            generated_code += " = ";
            
            Node assigned = after_assignment_stack.dequeue(Node(true, "#"));

            if(assigned.get_name().compare("function_call") == 0) {
                
                // traverse through the node to make sure the function call is recreated.
                // Also try to make sure the variables passed to the function are fetched by their
                // new term_ids as store in the NEW_VAR_LOOKUP SymbolTable class
                for(Node node: term_stack.get_stack().at(0).get_children()) {
                    
                    if(node.is_terminal()) { // allow the skipping of the semi-colon which is no longer usable

                        if(node.get_name().compare(";") != 0) {
                            generated_code += node.get_name();
                            generated_code += " ";
                        } 
                        
                    } else {

                        if(node.get_name().compare("function_call") == 0) {
                            generated_code += node.get_value();
                        } else if(node.get_name().compare("arguments") == 0) {
                            // this part assumes that onlu variables are passes onto the function call
                            generated_code += NEW_VAR_LOOKUP.find(node.get_value())[2];
                        }

                    }

                }

                generated_code += "\n";

            } else { // means the new_var is assigned to a pre-existing variable or to a number(float, double or int)

                if(assigned.get_name().compare("number") == 0)
                    generated_code += assigned.get_value();
                else if(assigned.get_name().compare("string_definition") == 0) {
                    generated_code += '"';
                    generated_code += assigned.get_value();
                    generated_code += '"';
                } else if(assigned.get_name().compare("boolean") == 0)
                    generated_code += assigned.get_value();
                else if(assigned.get_name().compare("condition") == 0) { // this tries to accoutn for booleans being initialised to conditions
                    std::string bool_id = "term_";
                    bool_id += to_string(TEST_ID - 1); // gets the boolean variable id since it has already been intialised
                    // initialise the boolean variable to an inital variable
                    generated_code += " = ";
                    generated_code += "false\n";
                    // unpack the condition node
                    generated_code += unpack_condition(assigned);
                    std::string result_id = "term_"; result_id += to_string(TEST_ID - 1); // gets the result of the id of the condition 
                    // initialise the boolean to the result of the condition
                    generated_code += (is_conditional_block)? "    ": indent;
                    generated_code += bool_id;
                    generated_code += " = ";
                    generated_code += result_id;
                }
                else
                    generated_code += NEW_VAR_LOOKUP.find(assigned.get_value())[2];
                
                generated_code += "\n";
            }
        }

    } else { // no assignment found in line

        if(op_found) {
            Node postfixed(false, "line");
            
            for(int i=0; i<term_stack.get_stack().size(); i++) {
                postfixed.add_children(term_stack.get_stack().at(i));
            }

            postfixed = ICG::postfix_it(postfixed);

            std::string code_generated = unpack_equation(postfixed, is_conditional_block); 
        } else {
            generated_code += (is_conditional_block)? "    ": indent;

            // means is an initialisation because the stack is greater than 1 even though its not an operation
            if(term_stack.get_stack().size() > 1) {
                std::string term_id = get_term_id();
                generated_code += term_id;
                generated_code += " = ";
                
                if(term_stack.get_stack().at(0).get_value().compare("int") == 0)
                    generated_code += "0\n";
                else 
                    generated_code += "0.0";
                
                NEW_VAR_LOOKUP.add_member( // create a new slot for a new variable initialisation
                    term_stack.get_stack().at(1).get_value(),
                    term_stack.get_stack().at(0).get_value(), 
                    term_id
                );

            } else { // is a function call or just a variable name written in a line

                // handles the case of it being a function call.
                // The logicc of only handling the function call is that,
                // if it was just a variable call, the variable was not used,
                // thus that was misuse of a line
                if(term_stack.get_stack().at(0).get_name().compare("function_call") == 0) {

                    // traverse through the node to make sure the function call is recreated.
                    // Also try to make sure the variables passed to the function are fetched by their
                    // new term_ids as store in the NEW_VAR_LOOKUP SymbolTable class
                    for(Node node: term_stack.get_stack().at(0).get_children()) {
                        
                        if(node.is_terminal()) { // allow the skipping of the semi-colon which is no longer usable

                            if(node.get_name().compare(",") == 0) {
                                generated_code += node.get_name();
                                generated_code += " ";
                            } else {

                                if(node.get_name().compare("(") == 0 || node.get_name().compare(")") == 0) {
                                    generated_code += node.get_name();
                                }

                            }
                            
                        } else {

                            if(node.get_name().compare("property_name") == 0) {
                                generated_code += node.get_value();
                            } else if(node.get_name().compare("arguments") == 0) {
                                // this part assumes that onlu variables are passes onto the function call
                                generated_code += NEW_VAR_LOOKUP.find(node.get_value())[2];
                            }

                        }

                    }

                    generated_code += "\n";
                }

            }

        }

    }

    return generated_code;
}