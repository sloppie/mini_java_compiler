#include "code_gen.h"

// condition node structure: name: "condition"
// Children
//     ( TERMINAL
//     tested_condition
//         condtition_paramter
//         comparator
//         condition_parameter
//     connector
//     ) TERMINAL

std::string ICG::CodeGenerator::unpack_condition(Node condition) {
    std::string generated_code = "";
    bool connector_found = false;
    bool comparator_found = false;

    for(Node child: condition.get_children()) {

        if(!connector_found) {
            connector_found = (child.get_name().compare("connector") == 0);
            continue;
        }

        if(!comparator_found) {
            comparator_found = (child.get_name().compare("comparator") == 0);
            continue;
        }

    }

    // accounting for the fact that each condition is housed in a tested_condition,
    //  this calls for passing of the index of the first child if it is in fact a single condition.
    // hence it is passed as unpack_single_condition(condition.get_children().at(0))

    generated_code = (connector_found)? unpack_chained_condition(condition): unpack_single_condition(condition.get_children().at(1));

    // cout<< intermediate_code<< endl;

    return generated_code;
}


std::string ICG::CodeGenerator::unpack_single_condition(Node condition) {
    std::string generated_code = "";
    std::string indent = "";

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    std::string term_id = get_term_id();
    generated_code += indent;
    generated_code += term_id;
    generated_code += " = ";

    for(Node child: condition.get_children()) {
        
        if(child.get_name().compare("condition_parameter") == 0) {
            
            if(child.get_value().compare("false") == 0 || child.get_value().compare("true") == 0) {
                generated_code += child.get_value();
                generated_code += " ";
            } else { // only handles variable names, code for handling functionn calls is yet to be added
                if(child.get_value().compare("undefined") == 0) {
                    generated_code += "undefined ";
                } else {
                    generated_code += NEW_VAR_LOOKUP.find(child.get_value())[2];
                    generated_code += " ";
                }
            }

        } else if(child.get_name().compare("comparator") == 0) {
            generated_code += child.get_value();
            generated_code += " ";
        }

    }

    generated_code += "\n";

    return generated_code;
}


std::string ICG::CodeGenerator::unpack_single_condition(Node condition, std::string term_id) {
    std::string indent = "";

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }
    std::string generated_code = indent;
    generated_code += term_id;
    generated_code += " = ";

    for(Node child : condition.get_children()) {// skips every other token except the condition_parameter and the comparator
        
        if(child.get_name().compare("condition_parameter") == 0) {
            
            if(child.get_value().compare("false") == 0 || child.get_value().compare("true") == 0) { // handles boolean values
                generated_code += child.get_value();
                generated_code += " ";
            } else { // only handles variable names, code for handling functionn calls is yet to be added
                if(child.get_value().compare("undefined") == 0) { // checks for the presence of an undefined variable
                    generated_code += "undefined ";
                } else {
                    generated_code += NEW_VAR_LOOKUP.find(child.get_value())[2];
                    generated_code += " ";
                }
            }

        } else if(child.get_name().compare("comparator") == 0) {
            generated_code += child.get_value();
            generated_code += " ";
        }

    }

    generated_code += "\n";

    return generated_code;
}


std::string ICG::CodeGenerator::unpack_chained_condition(Node condition) {
    std::string indent = "";

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    std::string generated_code = "";
    Queue<Queue<Node>> condition_queue;
    Queue<Node> current_condition;
    Queue<Node> connectors;
    // The part below is used to store the order of the terms created
    //  while also storing the order of connectors so as to help recreate the equivalent
    // three step vales that will help create an equivalent value term to the whole condition
    Queue<std::string> post_code_variables;
    Queue<std::string> post_code_connectors;

    //for-loop scans through the condition looking for conditions and connector tokens
    for(Node child : condition.get_children()) {

        if(child.get_name().compare("connector") == 0) {
            condition_queue.enqueue(current_condition);
            post_code_connectors.enqueue(child.get_value());
            current_condition = Queue<Node>();
        } else if(child.get_name().compare("tested_condition") == 0) {
            for(Node tested_condition_children: child.get_children()) {
                current_condition.enqueue(tested_condition_children);
            }
        } else if(child.get_name().compare("condition_parameter") == 0 || child.get_name().compare("comparator") == 0) {
            current_condition.enqueue(child);
        } else if(child.get_name().compare(")") == 0){ // This adds the last condition in the condition Node that is not in between connectors
            condition_queue.enqueue(current_condition);
        }

    }

    for(int i=0; i<condition_queue.get_init_queue().size(); i++) {

        // recreate a condition for the ICG::CodeGenerator::unpack_single_condition to use
        Node new_condition(false, "condition");
        Queue<Node> in_queue = condition_queue.dequeue(Queue<Node>());

        for(Node cond: in_queue.get_init_queue()) {
            new_condition.add_children(cond);
        }

        // handle the condition to get the equivalent three step code
        std::string term_id = get_term_id();
        post_code_variables.enqueue(term_id);
        generated_code += unpack_single_condition(new_condition, term_id);

    }

    std::string last_term = get_term_id();

    for(int i=0; i<post_code_variables.get_init_queue().size(); i++) {

        if(i == 0) {
            generated_code += indent;
            generated_code += last_term;
            generated_code += " = ";
            generated_code += post_code_variables.dequeue("");
            generated_code += " ";
            generated_code += post_code_connectors.dequeue("");
            generated_code += " ";
            generated_code += post_code_variables.dequeue("");
            generated_code += "\n";
            i++;
        } else {
            generated_code += indent;
            generated_code += last_term;
            generated_code += " = ";
            generated_code += last_term;
            generated_code += " ";
            generated_code += post_code_connectors.dequeue("#");
            generated_code += " ";
            generated_code += post_code_variables.dequeue("!");
            generated_code += "\n";
        }

    }

    return generated_code;
}