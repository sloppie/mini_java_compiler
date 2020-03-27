#include "lexer.h"

Lexer::Lexer(string source_code, SymbolTable* SYMBOL_TABLE, PackageTable* PACKAGE_TABLE, FunctionTable* FUNCTION_TABLE): source_code(source_code), SYMBOL_TABLE(SYMBOL_TABLE), PACKAGE_TABLE(PACKAGE_TABLE), FUNCTION_TABLE(FUNCTION_TABLE) {
    this->source_code = source_code;
    CURSOR = 0;
}

string Lexer::find_bracketed_code(string source_code, char bracket_type, int& CURSOR) {
    string code = "";
    char OPENING = bracket_type;
    char CLOSING;
    bool opening_spotted = false;
    Stack<char> bracket_stack;
    const char* sc = source_code.c_str();

    if(bracket_type == '(') {
        CLOSING = ')';
    } else if(bracket_type == '{') {
        CLOSING = '}';
    } else if(bracket_type == '[') {
        CLOSING = ']';
    }
    
    while(sc[CURSOR] != '\0') {

        if(sc[CURSOR] == OPENING) {

            if(!opening_spotted)
                opening_spotted = true;
            code += sc[CURSOR];
            bracket_stack.push(OPENING);
        } else if(sc[CURSOR] == CLOSING) {
            code += sc[CURSOR];
            bracket_stack.pop();

            if(bracket_stack.get_stack().size() == 0) {
                CURSOR++;
                break;
            }

        } else {
            if(opening_spotted)
                code += sc[CURSOR];
        }

        CURSOR++;
    }

    return code;
}


void Lexer::unpack_block(string sample_code) {
    const char* block_code = sample_code.c_str();
    int BLOCK_CURSOR = 0;
    string token_found = "";
    
    while(block_code[BLOCK_CURSOR] != '\0') {

        if(block_code[BLOCK_CURSOR] == ' ') {
            
            if(token_found.compare("if") == 0) {
                // handle if block
            } else if(token_found.compare("while") == 0) {
                // handle while-block
            } else {
                // handle statement
                string line = "";
                
                while(block_code[CURSOR] != ';') {
                    if(block_code[CURSOR] == '\n') {
                        cout<< "Expected a ';' at the end of line"<< line<< endl;
                    } else {
                        line += block_code[CURSOR];
                    }

                    BLOCK_CURSOR++;
                }

                unpack_line(line);
            }

        }

        BLOCK_CURSOR++;
    }

}


void Lexer::unpack_line(string source_code) {
    int LINE_CURSOR = 0;
    const char* line = source_code.c_str();
    Queue<string> term_stack;
    Queue<string> second_part;
    bool is_assignment = false;
    bool is_init_assignment = false;
    string term_found = "";

    int breakout_index = -1;

    string equation_tokens[] = {"*", "/", "+", "-"};


    if(is_function_call(source_code)) {
        unpack_function_call(source_code);
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

        cout<< endl<< endl<< "SECOND STACK"<< endl<< endl;

        if(is_assignment) { // looks for equation in second part
            int second_stack_size = second_part.size();

            for(int i=0; i<second_stack_size; i++) {
                bool arithmetic_op_found;

                for(int x=0; x<4; x++) {
                    arithmetic_op_found = second_part.get_queue().at(i).compare(equation_tokens[x]);
                    if(arithmetic_op_found)
                        break;
                }

                if(arithmetic_op_found) {
                    if(is_init_assignment) {
                        string type = term_stack.get_queue().at(0);
                        unpack_arithmetic_eq(second_part, type);
                        string var_name = term_stack.get_queue().at(1); 
                        // cout<< "Unpacking equation..."<< endl;
                        // cout<< "    Type: "<< type<< endl;
                        SYMBOL_TABLE->add_member(var_name, type, "FUNCTIONAL_CONTEXT");
                    } else {
                        string var_name = term_stack.get_queue().at(0);
                        string type = SYMBOL_TABLE->find(var_name)[1];

                        if(type.compare("undefined") == 0) {
                            cout<< "Tried to access an __UNDEFINED__ variable "<< var_name<< endl;
                        } else {
                            unpack_arithmetic_eq(term_stack, type);
                            // cout<< "Unpacking equation..."<< endl;
                            // cout<< "    Type: "<< type<< endl;
                        }
                    }
                } else {
                    // string type = term_stack.get_queue().at(0);
                    // string var_name = term_stack
                }
                
            }

        } else {

            for(int i=0; i<stack_size; i++) {
                bool arithmetic_op_found;

                for(int x=0; x<4; x++) {
                    arithmetic_op_found = term_stack.get_queue().at(i).compare(equation_tokens[x]) == 0;
                    if(arithmetic_op_found)
                        break;
                }

                if(arithmetic_op_found) {
                    CFG cfg;
                    string type;
                    string first_number = term_stack.get_queue().at(0);
                    if(cfg.is_int((first_number.c_str()))) {
                        type = "int";
                        unpack_arithmetic_eq(term_stack, type);
                        cout<< "Unpacking equation..."<< endl;
                        cout<< "    Type: "<< type<< endl;
                    } else if(cfg.is_decimal(first_number.c_str())) {
                        type = "float";
                        unpack_arithmetic_eq(term_stack, type);
                        cout<< "Unpacking equation..."<< endl;
                        cout<< "    Type: "<< type<< endl;
                    } else if(cfg.is_word(first_number.c_str())) {
                        type = SYMBOL_TABLE->find(first_number)[1];

                        if(type.compare("undefined") == 0) {
                            cout<< "Tried to access an __UNDEFINED__ variable"<< first_number<< endl;
                        } else {
                            unpack_arithmetic_eq(term_stack, type);
                            cout<< "Unpacking equation..."<< endl;
                            cout<< "    Type: "<< type<< endl;
                        }
                        
                    } else {
                        cout<< "INVALID variable name: "<< first_number<< endl;
                    }

                } else { // handles the lack of an arithmetic operation
                    cout<< stack_size<< " Stack SIZE"<< endl; 
                    if(stack_size > 1) { // may be an uninitialised variable declaration
                        if(stack_size == 2) {
                            string type_id = term_stack.get_queue().at(0);
                            string var_name = term_stack.get_queue().at(1);

                            bool is_def = (SYMBOL_TABLE->find(var_name)[0].compare("undefined") != 0);

                            if(is_def)
                                cout<< "Errror: Variable already defined\n    Token Name: "<< var_name<< endl;
                            else {
                                SYMBOL_TABLE->add_member(var_name, type_id, "FUNCTION_NAME");
                            }

                        } else {
                            cout<< "Invalid line progression"<< endl;
                        }
                    } else {
                        string* var = SYMBOL_TABLE->find(term_stack.dequeue("undefined"));

                        if(var[0].compare("undefined") != 0) {
                            cout<< "Token already created "<< var[0]<< endl;
                        } else { // block to handle undefined functions
                            string test_var = term_stack.get_init_queue().at(0); // doesn't work.. the queue mimicks memory erasing after dequeue
                            if(is_function_call(test_var)) {
                                unpack_function_call(test_var);
                            } else {
                                cout<< "UNDEFINED token found : "<< var[0]<< endl;
                            }
                        }
                    }
                }
            }

        }
    }

}

void Lexer::unpack_arithmetic_eq(Queue<string> equation, string NUMBER_TYPE) {
    CFG cfg;
    int QUEUE_SIZE = equation.size();
    string values[QUEUE_SIZE];
    bool valid_equation = true;

    // spread out equation
    for(int i=0; i<QUEUE_SIZE; i++) {
        values[i] = equation.dequeue("NO_VALUE");
    }

    if(!cfg.is_word(values[0].c_str())) {

        if(NUMBER_TYPE.compare("int") == 0) {

            if(cfg.is_int(values[0].c_str())) {
                cout<< "TOKEN: int"<<values[0]<< endl;
            } else {
                cout<< "INVALID TOKEN "<< values[0]<< ". Expected token of type \"int\""<< endl;
            }

        } else if(NUMBER_TYPE.compare("float") || NUMBER_TYPE.compare("double") == 0){

            if(cfg.is_decimal(values[0].c_str())) {
                cout<< "TOKEN: double"<<values[0]<< endl;
            } else {
                cout<< "INVALID TOKEN "<< values[0]<< "Expected token of type \"double\""<< endl;
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
                            cout<< "CONFLICTING TYPES!\n    EXPECTED TYPE: "<< NUMBER_TYPE<< ", GOT: "<< SYMBOL_TABLE->find(next)[1]<< endl;
                        }

                    } else {
                        if(is_function_call(next)) { // check if is function call
                            // pass
                        } else if(NUMBER_TYPE.compare("int") == 0) {
                            if(!cfg.is_int(next.c_str())) {
                                cout<< "INVALID TOKEN TYPE for token \""<< next<< "\". Expected \"int\""<< endl;
                            } else {
                                // cout<< "TOKEN: "<< NUMBER_TYPE<< next<< endl;
                            }
                        } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {
                            if(!cfg.is_decimal(next.c_str())) {
                                cout<< "INVALID TOKEN TYPE for token \""<< next<< "\". Expected \"float\""<< endl;
                            } else {
                                // cout<< "TOKEN: "<< NUMBER_TYPE<< next<< endl;
                            }
                        } else {
                            // handles function calls
                            cout<< "INVALID TOKEN: \""<< next<< "\""<< endl;
                        }
                    }

                } else if(is_equation_token(next) && (next.compare("-") == 0) && (i + 2 < QUEUE_SIZE)) {

                } else if(is_equation_token(next) && next.compare("-") != 0) {
                    cout<< "EQUATION TOKEN: \""<< current<< "\" cannot be followed by \""<< next<< "\""<< endl;
                }

            } else {

                if(!is_equation_token(next)) {
                    cout<< "INVALID Token progression: EXPECTED arithmetic token after: "<< current<< endl;
                } else {
                    if(cfg.is_word(current.c_str())) {

                        if(SYMBOL_TABLE->find(current)[1].compare(NUMBER_TYPE) == 0) {
                            // pass
                            cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                        } else {
                            cout<< "CONFLICTING TYPES!\n    EXPECTED TYPE: "<< NUMBER_TYPE<< ", GOT: "<< SYMBOL_TABLE->find(current)[1]<< endl;
                        }

                    } else {
                        if(is_function_call(current)) {
                            cout<< "verifying function call..."<< endl;
                            // string* function_details = FUNCTION_TABLE->find(function_name);
                            // if(function_details[1].compare(NUMBER_TYPE) == 0) {
                                unpack_function_call(current);
                            // } else {
                            //     cout<< "UNDECLARED FUNCTION called\n   FUNCTION DETAILS:\n        Name:"<< function_name<< endl;
                            // }

                        } else if(NUMBER_TYPE.compare("int") == 0) {
                            if(!cfg.is_int(current.c_str())) {
                                cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"int\""<< endl;
                            } else {
                                cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                            }
                        } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {
                            if(!cfg.is_decimal(current.c_str())) {
                                cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"float\""<< endl;
                            } else {
                                cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                            }
                        } else {
                            cout<< "INVALID TOKEN: \""<< current<< "\""<< endl;

                        }
                    }

                }

            }

        } else {
            //compare current to equation tokens
            if(is_eq_token) {
                cout<< "Equation token cannot end an equation"<< endl;
            } else {
                if(is_function_call(current)) {

                }else if(NUMBER_TYPE.compare("int") == 0) {
                    if(!cfg.is_int(current.c_str())) {
                        cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"int\""<< endl;
                    } else {

                    cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                    }
                } else if(NUMBER_TYPE.compare("float") == 0 || NUMBER_TYPE.compare("double") == 0) {
                    if(!cfg.is_decimal(current.c_str())) {
                        cout<< "INVALID TOKEN TYPE for token \""<< current<< "\". Expected \"float\""<< endl;
                    } else {
                        cout<< "TOKEN: "<< NUMBER_TYPE<< current<< endl;
                    }
                } else {
                    cout<< "INVALID TOKEN: \""<< current<< "\""<< endl;
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


void Lexer::unpack_function_call(string function_call) {
    const char* fc = function_call.c_str();
    string function_name = "";
    string function_param = "";
    bool fn_found = false;
    vector<string> function_args;

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
        params_queue function_params = FUNCTION_TABLE->find_param_details(function_name);
        
        if(function_params.size() == function_args.size()) {

            for(int i=0; i<function_params.size(); i++) {
                string arg_type;
                arg_type = SYMBOL_TABLE->find(function_args.at(i))[1];
                string default_return[3] = {"No param", "No param", "No param"};

                if(function_params.dequeue(default_return)[1].compare(arg_type) == 0) {
                    // ritght argument code :)
                } else {
                    cout<< "Argument"<< i + 1<< "for function \""<< function_name<< "\" is supposed to be of type: "<< function_params.get_init_queue().at(i)[1]<< endl;
                }
            }

        } else {
            cout<< "ERROR:"<< endl;
            cout<< "    Expected "<< function_params.size()<< " arguments. Instead gt: "<< function_args.size()<< endl;
            // insert template example here
            cout<< "    Function Template: "<< FUNCTION_TABLE->create_function_template(function_name)<< endl;
        }

    } else {
        cout<< "UNDEFINED function called: "<< endl<< "  Name: "<< function_name<< endl;
    }
    
}

bool Lexer::is_function_call(string current) {
    bool is_func = true;
    const char* function_call = current.c_str();
    int CURSOR_TRACK = 0;
    bool opening_bracket = false;
    bool closing_bracket = false;
    string function_name = "";

    while(function_call[CURSOR_TRACK] != '\0') {
        if(!opening_bracket) {
            opening_bracket = function_call[CURSOR_TRACK] == '(';
            if(!opening_bracket)
                function_name += function_call[CURSOR_TRACK];
        } else {
            closing_bracket = function_call[CURSOR_TRACK] == ')';
            if(closing_bracket) {

                if(function_call[CURSOR_TRACK + 1] != '\0') {
                    is_func = false;
                } 

                break;
            }
        }

        CURSOR_TRACK++;
    }

    if(!is_func)
        return false;
    else
        return closing_bracket && opening_bracket;

}