#include "code_gen.h"

// function prototypes
bool all_unpacked(bool*, int);

std::string ICG::CodeGenerator::unpack_equation(Node postfixed, std::string assigned_to, bool is_conditional_block) {
    std::string code_generated = "";
    int eq_size = postfixed.get_children().size();
    bool packed[eq_size];

    for(int i=0; i<eq_size; i++) {
        packed[i] = false;
    }

    std::string indent = "";

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }


    std::string result_stored = assigned_to;
    bool first_handled = false;

    while(!all_unpacked(packed, eq_size)) {
        
        for(int i=0; i<eq_size; i++) {

            if(packed[i]) {
                continue;
            } else {

                if(postfixed.get_children().at(i).is_terminal()) {
                    // dud initialised to be later replaced in the for-loop below
                    Node last_unhandled(true, "#");

                    // uses a for loop to get the most recent unhandled value
                    for(int x=(i - 1); x>=0; x--) {
                        
                        if(!packed[x]) {
                            last_unhandled = postfixed.get_children().at(x);
                            packed[x] = true;
                            break;
                        }

                    }

                    // checks if the first part is handled.
                    // if TRUE:
                    //     the code only gets an operand and only one prior unhandled node
                    // else:
                    //     the code takes an operand and operates on two previous nodes so as to kickstart the equation
                    if(first_handled) {
                        code_generated += (is_conditional_block)? "    ": indent;
                        code_generated += result_stored;
                        code_generated += " = ";
                        code_generated += result_stored;
                        code_generated += " ";
                        code_generated += postfixed.get_children().at(i).get_name();
                        code_generated += " ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (last_unhandled.get_name().compare("number") == 0)? last_unhandled.get_value(): NEW_VAR_LOOKUP.find(last_unhandled.get_value())[2];
                        code_generated += "\n";
                    } else {
                        // dud initialised to be later replaced in the for-loop below
                        Node second_last_unhandled(true, "#");

                        for(int x=(i - 1); x>=0; x--) {
                            
                            if(!packed[x]) {
                                second_last_unhandled = postfixed.get_children().at(x);
                                packed[x] = true;
                                break;
                            }

                        }

                        code_generated += (is_conditional_block)? "    ": indent;
                        code_generated += result_stored;
                        code_generated += " = ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (last_unhandled.get_name().compare("number") == 0)? last_unhandled.get_value(): NEW_VAR_LOOKUP.find(last_unhandled.get_value())[2];
                        code_generated += " ";
                        code_generated += postfixed.get_children().at(i).get_name();
                        code_generated += " ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (second_last_unhandled.get_name().compare("number") == 0)? second_last_unhandled.get_value() : NEW_VAR_LOOKUP.find(second_last_unhandled.get_value())[2];
                        code_generated += "\n";

                        first_handled = true;
                    }

                    packed[i] = true;
                    break;
                }

            }

        }

    }


    return code_generated;
}


std::string ICG::CodeGenerator::unpack_equation(Node postfixed, bool is_conditional_block) {
    std::string code_generated = "";
    int eq_size = postfixed.get_children().size();
    bool packed[eq_size];

    for(int i=0; i<eq_size; i++) {
        packed[i] = false;
    }

    std::string indent = "";

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }


    std::string result_stored = get_term_id();
    bool first_handled = false;

    while(!all_unpacked(packed, eq_size)) {
        
        for(int i=0; i<eq_size; i++) {

            if(packed[i]) {
                continue;
            } else {

                if(postfixed.get_children().at(i).is_terminal()) {
                    // dud initialised to be later replaced in the for-loop below
                    Node last_unhandled(true, "#");
                    // use a for loop to get the most recent unhandled value
                    for(int x=(i - 1); x>=0; x--) {
                        
                        if(!packed[x]) {
                            last_unhandled = postfixed.get_children().at(x);
                            packed[x] = true;
                            break;
                        }

                    }

                    // checks if the first part is handled.
                    // if TRUE:
                    //     the code only gets an operand and only one prior unhandled node
                    // else:
                    //     the code takes an operand and operates on two previous nodes so as to kickstart the equation
                    if(first_handled) {
                        code_generated += (is_conditional_block)? "    ": indent;
                        code_generated += result_stored;
                        code_generated += " = ";
                        code_generated += result_stored;
                        code_generated += " ";
                        code_generated += postfixed.get_children().at(i).get_name();
                        code_generated += " ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (last_unhandled.get_name().compare("number") == 0)? last_unhandled.get_value(): NEW_VAR_LOOKUP.find(last_unhandled.get_value())[2];
                        code_generated += "\n";
                    } else {
                        // dud initialised to be later replaced in the for-loop below
                        Node second_last_unhandled(true, "#");

                        for(int x=(i - 1); x>=0; x--) {
                            
                            if(!packed[x]) {
                                second_last_unhandled = postfixed.get_children().at(x);
                                packed[x] = true;
                                break;
                            }

                        }

                        code_generated += (is_conditional_block)? "    ": indent;
                        code_generated += result_stored;
                        code_generated += " = ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (last_unhandled.get_name().compare("number") == 0)? last_unhandled.get_value(): NEW_VAR_LOOKUP.find(last_unhandled.get_value())[2];
                        code_generated += " ";
                        code_generated += postfixed.get_children().at(i).get_name();
                        code_generated += " ";
                        // handles both numbers and also variables already pre-defined in the program
                        code_generated += (second_last_unhandled.get_name().compare("number") == 0)? second_last_unhandled.get_value() : NEW_VAR_LOOKUP.find(second_last_unhandled.get_value())[2];
                        code_generated += "\n";

                        first_handled = true;
                    }

                    packed[i] = true;
                    break;
                }
            }

        }

    }

    return code_generated;
}


bool all_unpacked(bool* packed, int eq_size) {
    bool unpacked = false;

    for(int i=0; i<eq_size; i++) {
        unpacked = packed[i];

        if(!unpacked) {
            break;
        }
    }


    return unpacked;
}