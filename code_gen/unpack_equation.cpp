#include "code_gen.h"

// The gist of these two methods is that they go shrinking the postfix equation by reducing
// an operand sign and its preceding two numbers to one value recursic=vely until the whole
// equation is reduced to one variable which is assigned to a term_id which may be new
// (as in the case of the first override of the method)
// or passed onto the quation (as in the case of override 2)

std::string ICG::CodeGenerator::unpack_equation(Node postfixed, bool is_conditional_block) {
    std::string generated_code = "";
    vector<Node> equation = postfixed.get_children();

    std::string term_id = get_term_id();

    std::string indent = "";

    // indent
    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    // The Vector reduces in a ratio of 3:1 hence the test of whether it is greater than two suits it
    // because,, if it is 3, it will then reduce to 1, which will have then got the answer we needed
    // and generated the code
    while(equation.size() > 2) {
        Node second_last(false, "#");
        Node last(false, "#");

        for(int i=1; i<equation.size(); i++) {
            
            if(equation.at(i).is_terminal()) {
                // stores the three positions to be replaced
                int c_1 = i;
                int c_2 = i - 1;
                int c_3 = i - 2;

                // this named_variable node is created by thee function in the event that the two nodes preceding
                // the mathematical operand are both raw numbers, this named_variable is used as a temporary storage
                //  and eventually the vatiable is used to compute the final value thart is to be stored in the term_id
                // variable created
                if(second_last.get_name().compare("named_variable") == 0 || last.get_name().compare("named_variable") == 0) {

                    generated_code += (is_conditional_block)? "    ": indent;
                    generated_code += term_id;
                    generated_code += " = ";
                    generated_code += (second_last.get_name().compare("property_defined") == 0)? NEW_VAR_LOOKUP.find(second_last.get_value())[2]: second_last.get_value();
                    generated_code += " ";
                    generated_code += equation.at(i).get_name();
                    generated_code += " ";
                    generated_code += (last.get_name().compare("property_defined") == 0)? NEW_VAR_LOOKUP.find(last.get_value())[2]: last.get_value();
                    generated_code += "\n";

                    // we have to create a new vector now that has sliced of the worked out values
                    vector<Node> new_equation;

                    // this loop is used to reassign the last two computed variables and their mathematical operand
                    // to one stored variable that will replace the three so as to shrink the postfox equation
                    for(int x=0; x<equation.size(); x++) {
                        if(x < c_3) {
                            new_equation.push_back(equation.at(x));
                        } else if(x == c_3) { 
                            new_equation.push_back(Node(false, "named_variable", term_id));
                        } else if(x > c_1) {
                            new_equation.push_back(equation.at(x));
                        }
                    }

                    //  replace with the new equation after shrinking it
                    equation = new_equation;
                    break;
                    
                } else {
                    std::string new_term_id = get_term_id();

                    generated_code += (is_conditional_block)? "    ": indent;
                    generated_code += new_term_id;
                    generated_code += " = ";
                    generated_code += (second_last.get_name().compare("property_defined") == 0)? NEW_VAR_LOOKUP.find(second_last.get_value())[2]: second_last.get_value();
                    generated_code += " ";
                    generated_code += equation.at(i).get_name();
                    generated_code += " ";
                    generated_code += (last.get_name().compare("property_defined") == 0)? NEW_VAR_LOOKUP.find(last.get_value())[2]: last.get_value();
                    generated_code += "\n";

                    // we have to create a new vector now that has sliced of the worked out values
                    vector<Node> new_equation;

                    // this loop is used to reassign the last two computed variables and their mathematical operand
                    // to one stored variable that will replace the three so as to shrink the postfox equation
                    for(int x=0; x<equation.size(); x++) {
                        if(x < c_3) {
                            new_equation.push_back(equation.at(x));
                        } else if(x == c_3) {
                            new_equation.push_back(Node(false, "named_variable", new_term_id));
                        } else if(x > c_1) {
                            new_equation.push_back(equation.at(x));
                        }
                    }

                    //  replace with the new equation after shrinking it
                    equation = new_equation;
                    break;
                }

            } else {
                // keepds track of the last two seen variables to help ease the process of
                // carring out operations on them once a mathematical operand is found
                last = equation.at(i);
                second_last = equation.at((i - 1));
            }

        }
    }

    return generated_code;
}


std::string ICG::CodeGenerator::unpack_equation(Node postfixed, std::string assigned_to, bool is_conditional_block) {
    int TEST_ID = 0; 
    std::string generated_code = "";
    vector<Node> equation = postfixed.get_children();

    std::string term_id = assigned_to;

    std::string indent = "";

    // indent
    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    // The Vector reduces in a ratio of 3:1 hence the test of whether it is greater than two suits it
    // because,, if it is 3, it will then reduce to 1, which will have then got the answer we needed
    // and generated the code
    while(equation.size() > 2) {
        Node second_last(false, "#");
        Node last(false, "#");

        for(int i=1; i<equation.size(); i++) {
            
            if(equation.at(i).is_terminal()) {
                // stores the three positions to be replaced
                int c_1 = i;
                int c_2 = i - 1;
                int c_3 = i - 2;

                // this named_variable node is created by thee function in the event that the two nodes preceding
                // the mathematical operand are both raw numbers, this named_variable is used as a temporary storage
                //  and eventually the vatiable is used to compute the final value thart is to be stored in the term_id
                // variable created
                if(second_last.get_name().compare("named_variable") == 0 || last.get_name().compare("named_variable") == 0) {

                    generated_code += (is_conditional_block)? "    ": indent;
                    generated_code += term_id;
                    generated_code += " = ";
                    generated_code += (second_last.get_name().compare("property_name") == 0)? NEW_VAR_LOOKUP.find(second_last.get_value())[2]: second_last.get_value();
                    generated_code += " ";
                    generated_code += equation.at(i).get_name();
                    generated_code += " ";
                    generated_code += (last.get_name().compare("property_name") == 0)? NEW_VAR_LOOKUP.find(last.get_value())[2]: last.get_value();
                    generated_code += "\n";

                    // we have to create a new vector now that has sliced of the worked out values
                    vector<Node> new_equation;

                    // this loop is used to reassign the last two computed variables and their mathematical operand
                    // to one stored variable that will replace the three so as to shrink the postfox equation
                    for(int x=0; x<equation.size(); x++) {
                        if(x < c_3) {
                            new_equation.push_back(equation.at(x));
                        } else if(x == c_3) {
                            new_equation.push_back(Node(false, "named_variable", term_id));
                        } else if(x > c_1) {
                            new_equation.push_back(equation.at(x));
                        }
                    }

                    //  replace with the new equation after shrinking it
                    equation = new_equation;
                    break;
                    
                } else {
                    std::string new_term_id = get_term_id();

                    generated_code += (is_conditional_block)? "    ": indent;
                    generated_code += new_term_id;
                    generated_code += " = ";
                    generated_code += (second_last.get_name().compare("property_name") == 0)? NEW_VAR_LOOKUP.find(second_last.get_value())[2]: second_last.get_value();
                    generated_code += " ";
                    generated_code += equation.at(i).get_name();
                    generated_code += " ";
                    generated_code += (last.get_name().compare("property_name") == 0)? NEW_VAR_LOOKUP.find(last.get_value())[2]: last.get_value();
                    generated_code += "\n";

                    // we have to create a new vector now that has sliced of the worked out values
                    vector<Node> new_equation;

                    // this loop is used to reassign the last two computed variables and their mathematical operand
                    // to one stored variable that will replace the three so as to shrink the postfox equation
                    for(int x=0; x<equation.size(); x++) {
                        if(x < c_3) {
                            new_equation.push_back(equation.at(x));
                        } else if(x == c_3) {
                            new_equation.push_back(Node(false, "named_variable", new_term_id));
                        } else if(x > c_1) {
                            new_equation.push_back(equation.at(x));
                        }
                    }

                    //  replace with the new equation after shrinking it
                    equation = new_equation;
                    break;
                }

            } else {
                // keepds track of the last two seen variables to help ease the process of
                // carring out operations on them once a mathematical operand is found
                last = equation.at(i);
                second_last = equation.at((i - 1));
            }

        }
    }

    return generated_code;
}