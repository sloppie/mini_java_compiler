#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_line(string source_code, Node* RESPECTIVE_NODE) {
    // cout<< "Unpacking line..."<< endl;
    string error_message;
    int LINE_CURSOR = 0;
    const char* line = source_code.c_str();
    Queue<string> term_stack;
    Queue<string> second_part;
    bool is_assignment = false;
    bool is_init_assignment = false;
    string term_found = "";

    bool is_defined = false;

    int breakout_index = -1;

    string equation_tokens[] = {"*", "/", "+", "-"};

    if(is_function_call(source_code)) {
        unpack_function_call(source_code, RESPECTIVE_NODE);
    } else {

        while(line[LINE_CURSOR] != '\0') {

            if(line[LINE_CURSOR] == ' ') {
                
                if(term_found.compare("=") == 0) {
                    breakout_index = CURSOR + 1;
                    is_assignment = true;
                    is_init_assignment = (term_stack.size() == 2);
                } else if(is_assignment) {
                    second_part.enqueue(term_found);
                }

                term_stack.enqueue(term_found);
                term_found = "";
            } else {
                term_found += line[LINE_CURSOR];
            }

            LINE_CURSOR++;
        }

        if(term_found.compare("") != 0) {
            term_stack.enqueue(term_found);

            if(is_assignment) {
                second_part.enqueue(term_found);
            }

        }

        int stack_size = term_stack.size();

        if(is_assignment) { // looks for equation in second part
            int second_stack_size = second_part.size();

            bool arithmetic_op_found = false;
            for(int i=0; i<second_stack_size; i++) {

                for(int x=0; x<4; x++) {
                    arithmetic_op_found = second_part.get_queue().at(i).compare(equation_tokens[x]) == 0;

                    if(arithmetic_op_found)
                        break;

                }

                if(arithmetic_op_found)
                    break;
            
            }
                if(arithmetic_op_found) {

                    if(is_init_assignment) {
                        string type = term_stack.get_queue().at(0);
                        string var_name = term_stack.get_init_queue().at(1);
                        if(!is_defined) {
                            RESPECTIVE_NODE->add_children(Node(false, "type_defined", type));
                            cout<< "\033[1;21m"<< type<<"\033[0m token(type_definition) added"<< endl;
                            SYMBOL_TABLE->add_member(var_name, type, "FUNCTIONAL_CONTEXT");
                            cout<< "\033[1;21m"<< var_name<<"\033[0m token(variable_name_definition) added"<< endl;
                            RESPECTIVE_NODE->add_children(Node(false, "property_name", var_name));
                            RESPECTIVE_NODE->add_children(Node(true, "="));
                            cout<< "\033[1;21m=\033[0m tokken added"<< endl;
                            unpack_arithmetic_eq(second_part, type, RESPECTIVE_NODE);
                            is_defined = true;
                        }
                    } else {
                        string var_name = term_stack.get_queue().at(0);
                        string type = SYMBOL_TABLE->find(var_name)[1];

                        if(type.compare("undefined") == 0) {
                            error_message = "The variable \033[1;21m";
                            error_message += var_name;
                            error_message += "\033[0m is undefined";

                            (*ERROR_STREAM)<< error_message;
                        } else {
                            RESPECTIVE_NODE->add_children(Node(false, "property_name", var_name));
                            cout<< "\033[1;21m"<< var_name<<"\033[0m token(variable_name_definition) added"<< endl;
                            RESPECTIVE_NODE->add_children(Node(true, "="));
                            cout<< "\033[1;21m=\033[0m token(assignment_token) added"<< endl;
                            // unpack_arithmetic_eq(term_stack, type, RESPECTIVE_NODE);
                            unpack_arithmetic_eq(second_part, type, RESPECTIVE_NODE);
                        }
                    }

                } else {
                    string type = term_stack.get_init_queue().at(0);

                    if(is_init_assignment) { // add tokents
                        if(!is_defined) {
                            RESPECTIVE_NODE->add_children(Node(false, "type_defined", term_stack.get_init_queue().at(0)));
                            cout<< "\033[1;21m"<< term_stack.get_init_queue().at(0)<<"\033[0m token(type_definition) added"<< endl;
                            RESPECTIVE_NODE->add_children(Node(false, "property_name", term_stack.get_init_queue().at(1)));
                            cout<< "\033[1;21m"<< term_stack.get_init_queue().at(1)<<"\033[0m token(variable_name_definition) added"<< endl;
                            RESPECTIVE_NODE->add_children(Node(true, "="));
                            SYMBOL_TABLE->add_member(term_stack.get_init_queue().at(1), type, "FUNCTIONAL_CONTEXT");
                            is_defined = true;
                        }
                    } else {
                        RESPECTIVE_NODE->add_children(Node(false, "property_name", term_stack.get_init_queue().at(0)));
                        cout<< "\033[1;21m"<< term_stack.get_init_queue().at(0)<<"\033[0m token(variable_name_definition) added"<< endl;
                        RESPECTIVE_NODE->add_children(Node(true, "="));
                        cout<< "\033[1;21m=\033[0m token(assignment_token) added"<< endl;
                    }
                    
                    if(second_stack_size == 1) {
                        string assigned = second_part.get_init_queue().at(0);
                        cout<< "Assigneed"<< assigned<< endl;

                        if(is_function_call(assigned)) {
                            int i = 0;
                            const char* function_code = assigned.c_str();
                            string function_name = "";

                            while(function_code[i] != ' ' && function_code[i] != '(') {
                                function_name += function_code[i];
                            }

                            // also handle the funtion call itself

                            string* function_details = FUNCTION_TABLE->find(function_name);

                            if(function_details[1].compare(type) == 0) {
                                //handle successful token
                                // RESPECTIVE_NODE->add_children(Node(false, "type_defined", type));
                                RESPECTIVE_NODE->add_children(Node(false, "function_call", term_stack.get_init_queue().at(1)));
                                cout<< "\033[1;21m"<< term_stack.get_init_queue().at(1)<<"\033[0m token(function_call) added"<< endl;
                            } else {
                                error_message = "Conflicting types. The function \033[1;0m";
                                error_message += function_name;
                                error_message += "\033[0m returns \033[1;21m";
                                error_message += function_details[1];
                                error_message += "\033[0m expected \033[1;0m";
                                error_message += type;
                                error_message += "\033[0m";

                                (*ERROR_STREAM)<< error_message;
                            }

                        } else if(CFG().is_word(assigned.c_str())) {
                            string* var_details = SYMBOL_TABLE->find(assigned);

                            if(var_details[1].compare(type) == 0) {
                                //handle successful token
                                // RESPECTIVE_NODE->add_children(Node(false, "type_defined", type));
                                RESPECTIVE_NODE->add_children(Node(false, "property_name", term_stack.get_init_queue().at(1)));
                                cout<< "\033[1;21m"<< var_details[0]<< "\033[0m token added"<< endl;
                            } else {
                                error_message = "\033[1;0mConflicting types error\033[0m: the variable";
                                error_message += assigned;
                                error_message += " is of type: ";
                                error_message += var_details[0];
                                error_message += " expected: \033[1;21";
                                error_message += type;
                                error_message += "\033[0m";

                                (*ERROR_STREAM)<< error_message;
                                // cout<< "conflicting types error: the variable \""<< assigned<< "\" is of type "<< var_details[0]<< "expected: "<< type<< endl;
                            }

                        } else {
                            if(type.compare("float") == 0 || type.compare("double") == 0) {
                                if(CFG().is_decimal(assigned.c_str())) {
                                    string new_float = type;
                                    new_float += assigned;
                                    RESPECTIVE_NODE->add_children(Node(false, "number", new_float));
                                    cout<< "\033[1;21m"<< type<< "\033[0m token added"<< assigned<< endl;
                                } else {
                                    error_message = "Invalid type: \033[1;21m";
                                    error_message += assigned;
                                    error_message += "\033[0m is not of type ";
                                    error_message += type;

                                    (*ERROR_STREAM)<< error_message;
                                    // cout<< "Invalid type"<< endl;
                                }
                            } else if(type.compare("int") == 0) {

                                if(CFG().is_int(assigned.c_str())) {
                                    string new_float = type;
                                    new_float += assigned;
                                    RESPECTIVE_NODE->add_children(Node(false, "number", new_float));
                                    cout<< "\033[1;21m"<< type<< "\033[0m token added"<< assigned<< endl;
                                } else {
                                    error_message = "Invalid type: \033[1;21m";
                                    error_message += assigned;
                                    error_message += "\033[0m is not of type ";
                                    error_message += type;

                                    (*ERROR_STREAM)<< error_message;
                                    // cout<< "Invalid type"<< endl;
                                }

                            }
                        }
                    }
                    // string var_name = term_stack
                }
                
            // }

        } else {

            bool arithmetic_op_found;
            for(int i=0; i<stack_size; i++) {

                for(int x=0; x<4; x++) {
                    arithmetic_op_found = term_stack.get_queue().at(i).compare(equation_tokens[x]) == 0;

                    if(arithmetic_op_found)
                        break;

                }

                if(arithmetic_op_found)
                    break;
            }

                if(arithmetic_op_found) {
                    CFG cfg;
                    string type;
                    string first_number = term_stack.get_queue().at(0);

                    if(cfg.is_int((first_number.c_str()))) {
                        type = "int";
                        unpack_arithmetic_eq(term_stack, type, RESPECTIVE_NODE);
                    } else if(cfg.is_decimal(first_number.c_str())) {
                        type = "float";
                        unpack_arithmetic_eq(term_stack, type, RESPECTIVE_NODE);
                    } else if(cfg.is_word(first_number.c_str())) {
                        type = SYMBOL_TABLE->find(first_number)[1];

                        if(type.compare("undefined") == 0) {
                            error_message = "The token \033[1;21m";
                            error_message += first_number;
                            error_message += "\033[0m is undefined";

                            (*ERROR_STREAM)<< error_message;
                            // cout<< "Tried to access an __UNDEFINED__ variable"<< first_number<< endl;
                        } else {
                            unpack_arithmetic_eq(term_stack, type, RESPECTIVE_NODE);
                        }
                        
                    } else {
                        error_message = "Invalid variable name: \033[1;21m";
                        error_message += first_number;
                        error_message += "\033[0m";

                        (*ERROR_STREAM)<< error_message;
                        // cout<< "INVALID variable name: "<< first_number<< endl;
                    }

                } else { // handles the lack of an arithmetic operation
                    
                    if(stack_size > 1) { // may be an uninitialised variable declaration
                        if(stack_size == 2) {
                            string type_id = term_stack.get_queue().at(0);
                            string var_name = term_stack.get_queue().at(1);

                            bool is_def = (SYMBOL_TABLE->find(var_name)[0].compare("undefined") != 0);

                            if(is_def) {
                                error_message = "Variable \033[1;21m";
                                error_message += var_name;
                                error_message += " \033[0malready defined";

                                (*ERROR_STREAM)<< error_message;
                                // cout<< "Errror: Variable already defined\n    Token Name: "<< var_name<< endl;
                            } else {
                                SYMBOL_TABLE->add_member(var_name, type_id, "FUNCTION_NAME");
                                RESPECTIVE_NODE->add_children(Node(false, "type_defined", type_id));
                                cout<< "\033[1;21m"<< type_id<< "token(type_defined) added"<< endl;
                                RESPECTIVE_NODE->add_children(Node(false, "property_name", var_name));
                                cout<< "\033[1;21m"<< var_name<< "token(variable_name_definition) added"<< endl;
                            }

                        } else {
                            error_message = "Invalid line progression";

                            (*ERROR_STREAM)<< error_message;
                            // cout<< "Invalid line progression"<< endl;
                        }

                    } else {
                        string* var = SYMBOL_TABLE->find(term_stack.dequeue("undefined"));

                        if(var[0].compare("undefined") != 0) {
                            error_message = "Token \033[1;21m";
                            error_message += var[0];
                            error_message += "\033[0m already defined";

                            (*ERROR_STREAM)<< error_message;
                            // cout<< "Token already created "<< var[0]<< endl;
                        } else { // block to handle undefined functions
                            string test_var = term_stack.get_init_queue().at(0); // doesn't work.. the queue mimicks memory erasing after dequeue

                            if(is_function_call(test_var)) {
                                unpack_function_call(test_var, RESPECTIVE_NODE);
                            } else {
                                error_message = "Undefined token: \033[1;21m";
                                error_message += var[0];
                                error_message += "\033[0m";

                                (*ERROR_STREAM)<< error_message;
                            }

                        }
                    }
                }
            // }

        }
    }

}


void Lexer::unpack_arithmetic_eq(Queue<string> equation, string NUMBER_TYPE, Node* RESPECTIVE_NODE) {
    CFG cfg;
    int QUEUE_SIZE = equation.size();
    string values[QUEUE_SIZE];
    bool valid_equation = true;

    string error_message;

    // spread out equation
    for(int i=0; i<QUEUE_SIZE; i++) {
        values[i] = equation.get_init_queue().at(i);
    }

    if(!cfg.is_word(values[0].c_str())) {
        string new_number = NUMBER_TYPE;

        if(NUMBER_TYPE.compare("int") == 0) {

            if(cfg.is_int(values[0].c_str())) {
                new_number += values[0];
                RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                cout<< "\033[1;21m"<< new_number<< "\033[0m token added"<< endl;
                // cout<< "TOKEN: int"<<values[0]<< endl;
            } else {
                error_message = "Invalid token \033[1;21m";
                error_message += values[0];
                error_message += "\033[0m . Expected token of type \033[1;0mint\033[0m";

                (*ERROR_STREAM)<< error_message;
            }

        } else if(NUMBER_TYPE.compare("float") || NUMBER_TYPE.compare("double") == 0){
            new_number += values[0];
            if(cfg.is_decimal(values[0].c_str())) {
                RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                cout<< "\033[1;21m"<< new_number<< "\033[0m token added"<< endl;
            } else {
                error_message = "Invalid token \033[1;21m";
                error_message += values[0];
                error_message += "\033[0m. Expected token of type \033[1;21m";
                error_message += NUMBER_TYPE;               
                error_message += "\033[0m";

                (*ERROR_STREAM)<< error_message;
            }

        }
    } else {
        std::string v_name = values[0];
        std::string v_type = SYMBOL_TABLE->find(v_name)[1];
        
        if(is_function_call(values[0])) {
            // handle function_call
        } else {
            
            if(NUMBER_TYPE.compare(v_type) == 0) {
                RESPECTIVE_NODE->add_children(Node(false, "property_defined", v_name));
                cout<< "\033[1;21m"<< v_name<< "\033[0m token(propety_name) added"<< endl;
            } else {
                error_message = "Invalid token \033[1;21m";
                error_message += values[0];
                error_message += "\033[0m . Expected token of type \033[1;21m";
                error_message += NUMBER_TYPE;
                error_message += "\033[0m";

                (*ERROR_STREAM)<< error_message;
            }

        }

    }

    for(int i=1; i<QUEUE_SIZE; i++) {
        string previous = values[i - 1];
        string current = values[i];
        string next = ((i + 1) == QUEUE_SIZE)? "": values[i + 1];

        bool is_eq_token = is_equation_token(current);

        if(next.compare("") != 0) { // checks if the current is the endinfng token

            if(is_eq_token) {

                if(!is_equation_token(next)) {

                    if(cfg.is_word(next.c_str())) {

                        if(SYMBOL_TABLE->find(next)[1].compare(NUMBER_TYPE) == 0) {
                            // pass
                            // cout<< "TOKEN: "<< NUMBER_TYPE<< next<< endl;
                        } else {
                            error_message = "Conflicting types: Expected \033[1;21m";
                            error_message += NUMBER_TYPE;
                            error_message += ". However, got: \033[1;21m";
                            error_message += SYMBOL_TABLE->find(next)[1];
                            error_message += "\033[0m";

                            (*ERROR_STREAM)<< error_message;
                            break;
                            // cout<< "CONFLICTING TYPES!\n    EXPECTED TYPE: "<< NUMBER_TYPE<< ", GOT: "<< SYMBOL_TABLE->find(next)[1]<< endl;
                        }

                    } else {

                        if(is_function_call(next)) { // check if is function call
                            // pass
                        } else if(NUMBER_TYPE.compare("int") == 0) {

                            if(!cfg.is_int(next.c_str())) {
                                error_message = "Invalid type for token: \033[1;21m";
                                error_message += next;
                                error_message += "\033[0m. Expected \033[1;21mint\033[0m";

                                (*ERROR_STREAM)<< error_message;
                                break;
                                // cout<< "INVALID TOKEN TYPE for token \""<< next<< "\". Expected \"int\""<< endl;
                            } else {
                                // cout<< "TOKEN: "<< NUMBER_TYPE<< next<< endl;
                            }

                        } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {

                            if(!cfg.is_decimal(next.c_str())) {
                                error_message = "Invalid type for token: \033[1;21m";
                                error_message += next;
                                error_message += "\033[0m. Expected \033[1;21m";
                                error_message += NUMBER_TYPE;
                                error_message += "int\033[0m";

                                (*ERROR_STREAM)<< error_message;
                                break;
                            } else {
                            }

                        } else {
                            // handles function calls
                            error_message = "Invalid token: \033[1;21m";
                            error_message += next;
                            error_message += "\033[0m";

                            (*ERROR_STREAM)<< error_message;
                            break;
                            // cout<< "INVALID TOKEN: \""<< next<< "\""<< endl;
                        }
                    }

                } else if(is_equation_token(next) && (next.compare("-") == 0) && (i + 2 < QUEUE_SIZE)) {

                } else if(is_equation_token(next) && next.compare("-") != 0) {
                    error_message = "\033[1;21m";
                    error_message += current;
                    error_message += "\033[0m cannot be followed by \033[1;0m";
                    error_message += next;

                    (*ERROR_STREAM)<< error_message;
                    break; 
                }
                RESPECTIVE_NODE->add_children(Node(true, current));
                cout<< "\033[1;21m"<< current<< "\033[0m token added"<< endl;
            } else {

                if(!is_equation_token(next)) {
                    error_message = "Invalid token progression. Expected arithmetic token after: \033[1;21m";
                    error_message += current;
                    error_message += "\033[0m";

                    (*ERROR_STREAM)<< error_message;
                } else {

                    if(cfg.is_word(current.c_str())) {

                        if(SYMBOL_TABLE->find(current)[1].compare(NUMBER_TYPE) == 0) {
                            // pass
                            RESPECTIVE_NODE->add_children(Node(false, "property_name", current));
                            cout<< "\033[1;21m"<< current<< "\033[0m token(propety_name) added"<< endl;
                        } else {
                            error_message = "\033[1;0mType Conflic\033[0m. Expected: ";
                            error_message += NUMBER_TYPE;
                            error_message += "\033[1;0m, got: \033[1;0m" ;
                            error_message += SYMBOL_TABLE->find(current)[1];
                            error_message += "\033[0m";

                            (*ERROR_STREAM)<< error_message;
                            // cout<< "CONFLICTING TYPES!\n    EXPECTED TYPE: "<< NUMBER_TYPE<< ", GOT: "<< SYMBOL_TABLE->find(current)[1]<< endl;
                        }

                    } else {

                        if(is_function_call(current)) {
                            cout<< "verifying function call..."<< endl;
                            unpack_function_call(current, RESPECTIVE_NODE);
                        } else if(NUMBER_TYPE.compare("int") == 0) {
                            string new_number = NUMBER_TYPE;
                            new_number += current;
                            if(!cfg.is_int(current.c_str())) {
                                error_message = "Invalid type for token: \033[1;21m";
                                error_message += current;
                                error_message += "\033[0m. Expected \033[1;21mint\033[0m";

                                (*ERROR_STREAM)<< error_message;
                                break;
                                // cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"int\""<< endl;
                            } else {
                                RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                                cout << "\033[1;21m" << current << "\033[0m token(number) added" << endl;
                                cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                            }

                        } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {
                            string new_number = NUMBER_TYPE;
                            new_number += current;

                            if(!cfg.is_decimal(current.c_str())) {
                                error_message = "Invalid type for token: \033[1;0m";
                                error_message += current;
                                error_message += "\033[0m. Expected \033[1;0m";
                                error_message += NUMBER_TYPE;
                                error_message += "\033[0m";

                                (*ERROR_STREAM)<< error_message;
                                break;
                                // cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"float\""<< endl;
                            } else {
                                RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                                cout << "\033[1;21m" << current << "\033[0m token(number) added" << endl;
                            }

                        } else {
                            error_message = "Invalid token: \033[1;0m";
                            error_message += current;
                            error_message += "\033[0m";

                            (*ERROR_STREAM)<< error_message;
                            break;
                            // cout<< "INVALID TOKEN: \""<< current<< "\""<< endl;

                        }
                    }

                }

            }

        } else {
            //compare current to equation tokens
            if(is_eq_token) {
                error_message = "\033[1;21mInvalid progression\033[0m: Equation token cannot end an equation";

                (*ERROR_STREAM)<< error_message;
                // cout<< "Equation token cannot end an equation"<< endl;
            } else {
                string new_number = NUMBER_TYPE;
                new_number += current;

                if(is_function_call(current)) {

                }else if(NUMBER_TYPE.compare("int") == 0) {

                    if(!cfg.is_int(current.c_str())) {
                        error_message = "\033[1;21mInvalid type\033[0m found in token \033[1;21m";
                        error_message += current;
                        error_message += "\033[0m Expected \033[1;21mint\033[0m";

                        (*ERROR_STREAM)<< error_message;
                    } else {
                        RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                        cout<< "\033[1;21m"<< new_number<< "\033[0m token(number) added"<< endl;
                    }

                } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {

                    if(!cfg.is_decimal(current.c_str())) {
                        error_message = "\033[1;21mInvalid type\033[0m found in token \033[1;21m";
                        error_message += current;
                        error_message += "\033[0m Expected \033[1;21m";
                        error_message += NUMBER_TYPE;
                        error_message +="\033[0m";

                        (*ERROR_STREAM)<< error_message;
                    } else {
                        RESPECTIVE_NODE->add_children(Node(false, "number", new_number));
                        cout<< "\033[1;21m"<< new_number<< "\033[0m token(number) added"<< endl;
                    }

                } else {
                    error_message = "Invalid token \033[1;21m";
                    error_message += current;
                    error_message += "\033[0m";

                    (*ERROR_STREAM)<< error_message;
                }

                // if (SYMBOL_TABLE->find(current)[1].compare(NUMBER_TYPE) != 0) {
                //     cout<< "Invalid Type in arithmetic equation. VAR_NAME: \""<< current<< "\""<< endl; 
                // }
            }

        }

    }

}


bool Lexer::is_equation_token(string token) {
    bool is_eq_tok = false;

    for (int x = 0; x < EQ_TOKEN_SIZE; x++) {
        is_eq_tok = (token.compare(EQUATION_TOKENS[x]) == 0);

        if (is_eq_tok) {
            break;
        }

    }

    return is_eq_tok;
}


void Lexer::unpack_function_call(string function_call, Node* RESPECTIVE_NODE) {
    cout<< "Unpacking function call..."<< endl;
    const char* fc = function_call.c_str();
    string function_name = "";
    string function_param = "";
    bool fn_found = false;
    vector<string> function_args;
    string error_message;

    int CURSOR = 0;

    while (fc[CURSOR] != '\0') {

        if(fc[CURSOR] != '(' && !fn_found) {

            if(fc[CURSOR] != ' ') {
                function_name += fc[CURSOR];
            }

        } else {

            if(fc[CURSOR] == '(') {
                fn_found = true;
                CURSOR++;
                continue;
            } else {

                if(fc[CURSOR] != ' ' && fc[CURSOR] != ',' && fc[CURSOR] != ')') {
                    function_param += fc[CURSOR];
                } else {

                    if(fc[CURSOR] == ' ' || fc[CURSOR] == ',') {

                        if(function_param.compare("") != 0) {
                            function_args.push_back(function_param);
                            function_param = "";
                        }

                    } else {

                        if(function_param.compare("") != 0) {
                            function_args.push_back(function_param);
                            function_param = "";
                        }

                    }

                }

            }
        }

        CURSOR++;       
    }

    // fetch function info
    string* function_details = FUNCTION_TABLE->find(function_name);

    if(function_details[0].compare("undefined") != 0) {
        Node fn_call(false, "function_call", FUNCTION_TABLE->get_function_id(function_name));
        params_queue function_params = FUNCTION_TABLE->find_param_details(function_name);
        
        if(function_params.size() == function_args.size()) {

            for(int i=0; i<function_params.size(); i++) {
                string arg_type;
                arg_type = SYMBOL_TABLE->find(function_args.at(i))[1];
                string default_return[3] = {"No param", "No param", "No param"};

                if(function_params.dequeue(default_return)[1].compare(arg_type) == 0) {
                    // ritght argument code :)
                    Node arg(false, "arguments", function_args.at(i));
                    fn_call.add_children(arg);
                } else {
                    error_message = "Argument ";
                    error_message += (i + 1);
                    error_message += "for funtion \033[1;0m";
                    error_message += "\033[0m is supposed to be of type";
                    error_message += function_params.get_init_queue().at(i)[1];

                    (*ERROR_STREAM)<< error_message;
                    // cout<< "Argument"<< i + 1<< "for function \""<< function_name<< "\" is supposed to be of type: "<< function_params.get_init_queue().at(i)[1]<< endl;
                }

            }

        } else {
            error_message = "Expected: ";
            error_message += function_params.size();
            error_message += " arguments but instead got: ";
            error_message += function_args.size();
            error_message += "\n\t\t\033[1;0m";
            error_message += FUNCTION_TABLE->create_function_template(function_name);
            error_message += "\033[0m";

            (*ERROR_STREAM)<< error_message;
            // cout<< "ERROR:"<< endl;
            // cout<< "    Expected "<< function_params.size()<< " arguments. Instead gt: "<< function_args.size()<< endl;
            // // insert template example here
            // cout<< "    Function Template: "<< FUNCTION_TABLE->create_function_template(function_name)<< endl;
        }

        RESPECTIVE_NODE->add_children(fn_call);

    } else {
        error_message = "Undefined function \033[1;0m";
        error_message += function_name;
        error_message += "\033[0m called";

        (*ERROR_STREAM)<< error_message;
        //cout<< "UNDEFINED function called: "<< endl<< "  Name: "<< function_name<< endl;
    }
    
}