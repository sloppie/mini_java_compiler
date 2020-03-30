#include "lexer.h"

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


void Lexer::unpack_package(string source_code, string package_type) {

    if(package_type.compare("package") == 0)
        cout<< "Unpacking package declaration..."<< endl;
    else
        cout<< "Unpacking import declaration..."<< endl;

    int CURSOR = 0;
    const char* code = source_code.c_str();
    string term_found = "";
    bool opening_term_parsed = false;
    string package_name = "";
    int BRANCH;
    CFG mini_java_cfg;

    while(code[CURSOR] != '\n') {

        if(!(term_found.compare("") == 0 && (code[CURSOR] == ' ' || code[CURSOR] == '\t'))) {
            
            if(code[CURSOR] == ' ') {

                if(term_found.compare(package_type) == 0) {
                    opening_term_parsed = true;
                    CURSOR++;
                    
                    while(code[CURSOR] != ';' && code[CURSOR] != ' ' && code[CURSOR] != '\0' && code[CURSOR] != '\n') {
                        package_name += code[CURSOR];

                        CURSOR++;                        
                    }

                    cout<< "PACKAGE NAME: "<< package_name<< endl;
                    // package_name += ';';
            
                    bool is_package = (mini_java_cfg.is_package_name(package_name.c_str()));

                    if(is_package) {
                        cout<< "Valid package name identified: \""<< package_name<< "\""<< endl;
                    } else {
                        cout<< "Invalide package name: \""<< package_name<< "\""<< endl;
                    }

                    if(code[CURSOR] == ' ') { // whitespace remover

                        while(code[CURSOR] == ' ') {
                            CURSOR++;
                        }

                    }

                    if(code[CURSOR] == '\n') {
                        cout<< "expected ';' before moving on to a new line"<< endl;
                    } else {
                        // handle token add
                    }

                    break;
                } else {

                    if(package_type.compare("package") == 0)
                        cout<< "Expected the token \"package\""<< endl;
                    else {
                        // CURSOR = BRANCH;
                    }

                    opening_term_parsed = true;

                    break;
                }

            } else {

                if(term_found.compare("") == 0) // create a branch
                    BRANCH = CURSOR;

                term_found += code[CURSOR];
            }

        }

        CURSOR++;
    }

    if(!opening_term_parsed) {
        cout<< "Invalid package structure: expected: <import_keyword> | <package_keyword> <package_name>;"<< endl;
    }

}


bool Lexer::package_parser(string code) {
    const char* package_code = code.c_str();
    int CURSOR = 0;

    return false;
}


void Lexer::unpack_class(string code) {
    cout<< "Unpacking class..."<< endl;
    string access_modifier = "";
    string class_name = "";
    string class_token = "";
    int CURSOR = 0;

    string term_found = "";

    const char* class_code = code.c_str();

    while(class_code[CURSOR] != '\0') {

        if((term_found.compare("") == 0) && (class_code[CURSOR] == ' ' || class_code[CURSOR] == '\n' || class_code[CURSOR] == '\t')) {
            
            if(class_code[CURSOR] == '\n') {
                // handle new line
            }

            CURSOR++;
            continue;

        } else if(code[CURSOR] == ' ') {
                cout<< term_found<< endl;
                if(term_found.compare("public") == 0 || term_found.compare("private") == 0 || term_found.compare("protected") == 0) { // handle conditionals
                    int FUNCTION_BRANCH;
                    int VARIABLE_DEC_BRANCH;
                    access_modifier = term_found;
                    bool is_func = false;

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    while(code[CURSOR] != ' ' && code[CURSOR] != '{') {
                        class_token += code[CURSOR];

                        CURSOR++;
                    }

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    while(code[CURSOR] != ' ' && code[CURSOR] != '{') {
                        class_name += code[CURSOR];

                        CURSOR++;
                    }

                    if(CFG().is_word(class_name.c_str())) {
                        // handle class name to package table
                        cout<< "Class name: "<< class_name<< endl;
                    } else {
                        cout<< "Invalid class name \""<< class_name<< "\""<< endl;
                    }

                    while(code[CURSOR] == ' ') {
                        CURSOR++;
                    }

                    if(code[CURSOR] == '{') {
                        CURSOR++;
                        break;
                    } else {
                        cout<< "expected '{' token to open up the class body"<< endl;
                    }
                }
            } else {
                term_found += code[CURSOR];
            }

        CURSOR++;
    }

    term_found = "";

    while(class_code[CURSOR] != '\0') {

        if(term_found.compare("") == 0 && (class_code[CURSOR] == ' ' || class_code[CURSOR] == '\n' || class_code[CURSOR] == '\t')) {
            
            if(class_code[CURSOR] == '\n') {
                // handle new line
            }

            CURSOR++;
            continue;

        } else if(code[CURSOR] == ' ') {

                if(term_found.compare("public") == 0 || term_found.compare("private") == 0 || term_found.compare("protected") == 0) { // handle conditionals
                    int FUNCTION_BRANCH;
                    int VARIABLE_DEC_BRANCH;
                    bool is_func = false;

                    if(term_found.compare("public") == 0) {
                        FUNCTION_BRANCH = CURSOR - 5;
                    } else if(term_found.compare("private") == 0) {
                        FUNCTION_BRANCH = CURSOR - 6;
                    } else {
                        FUNCTION_BRANCH = CURSOR - 8;
                    }

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    VARIABLE_DEC_BRANCH = CURSOR;

                    term_found = "";

                    while(class_code[CURSOR] != '\n') {

                        if(class_code[CURSOR] == '(') { // enforce opening curly brace check to avoid sending function calls as fnction definitions
                            CURSOR = FUNCTION_BRANCH;
                            FUNCTION_TABLE->scan_function(code, CURSOR);
                            string function_block = Lexer::find_bracketed_code(code, '{', CURSOR);
                            unpack_block(function_block);
                            is_func = true;
                        }

                        if(is_func) {
                            is_func = class_code[CURSOR] == ';';
                        }

                        CURSOR++;
                    }

                    if(!is_func) {
                        string variable_dec = "";
                        CURSOR = VARIABLE_DEC_BRANCH;

                        while(code[CURSOR] != ';' && code[CURSOR] != '\n') {
                            // skip whitespaces
                            if(!(variable_dec.compare("") == 0 && code[CURSOR] == ' ')) {
                                variable_dec += code[CURSOR];
                            }

                            CURSOR++;
                        }

                        if(code[CURSOR] == '\n') {
                            cout<< "Error in line Expected ';' at the end of line"<< endl;
                        } else {
                            unpack_line(variable_dec);
                        }

                    }

                } else {
                    // !TODO add error handling
                    if(term_found.compare("}") == 0) {
                        break;
                    }
                }


        } else {
            term_found += class_code[CURSOR];
        }

        CURSOR++;
    }

}


void Lexer::unpack_if(string code) {
    int CURSOR = 0;
    const char* if_code = code.c_str();
    bool opening_term = false;
    string term = "";

    // create Node data structure to hold the data for the parse tree

    while(if_code[CURSOR] != '\0') {
        term += if_code[CURSOR];

        if(term.compare("if") == 0) {
            // handle adde=ing to Node tree
            cout<< "If spotted"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        unpack_condition(condition);
        unpack_block(block_code);
    }


    term = ""; // reset term to look for an 'else' 

    int RESET_CURSOR = CURSOR;
    bool if_body_ended = false;
    //
    while(!if_body_ended) {

        // eliminate white space
        while(if_code[CURSOR] != '\0' && (if_code[CURSOR] == ' ' || if_code[CURSOR] == '\n')) {
            
            if(if_code[CURSOR] == '\n') {
                // handle new line
            }

            CURSOR++;
        }

        if(if_code[CURSOR] != '\0') {
            bool else_found = false;
            
            while(if_code[CURSOR] != '\0' && if_code[CURSOR] != ' ') {
                term = if_code[CURSOR];
                CURSOR++;
            }

            if(term.compare("else") == 0) {
                // eliminate white space
                string second_term = "";

                while(if_code[CURSOR] == ' ') {
                    CURSOR++;
                }

                RESET_CURSOR = CURSOR;

                while(if_code[CURSOR] != ' ' && if_code[CURSOR] != ')') {
                    second_term += if_code[CURSOR];
                }

                if(second_term.compare("if") == 0) {
                    CURSOR = RESET_CURSOR;
                    unpack_if(code, CURSOR);
                } else {
                    Lexer::find_bracketed_code(code, '{', CURSOR);
                }

            } else {
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }

    }


    //
}


void Lexer::unpack_if(int& CURSOR, string code) {
    const char* if_code = code.c_str();
    bool opening_term = false;
    string term = "";

    // create Node data structure to hold the data for the parse tree

    while(if_code[CURSOR] != '\0') {
        term += if_code[CURSOR];

        if(term.compare("if") == 0) {
            // handle adde=ing to Node tree
            cout<< "If spotted"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        unpack_condition(condition);
        unpack_block(block_code);
    }


    term = ""; // reset term to look for an 'else' 

    int RESET_CURSOR = CURSOR;
    bool if_body_ended = false;
    //
    while(!if_body_ended) {

        // eliminate white space
        while(if_code[CURSOR] != '\0' && (if_code[CURSOR] == ' ' || if_code[CURSOR] == '\n')) {
            
            if(if_code[CURSOR] == '\n') {
                // handle new line
            }

            CURSOR++;
        }

        if(if_code[CURSOR] != '\0') {
            bool else_found = false;
            
            while(if_code[CURSOR] != '\0' && if_code[CURSOR] != ' ') {
                term = if_code[CURSOR];
                CURSOR++;
            }

            if(term.compare("else") == 0) {
                // eliminate white space
                string second_term = "";

                while(if_code[CURSOR] == ' ') {
                    CURSOR++;
                }

                RESET_CURSOR = CURSOR;

                while(if_code[CURSOR] != ' ' && if_code[CURSOR] != ')') {
                    second_term += if_code[CURSOR];
                }

                if(second_term.compare("if") == 0) {
                    CURSOR = RESET_CURSOR;
                    unpack_if(code, CURSOR);
                } else {
                    Lexer::find_bracketed_code(code, '{', CURSOR);
                }

            } else {
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }
    }

}


void Lexer::unpack_if(string code, int& CURSOR) {
    const char* if_code = code.c_str();
    bool opening_term = false;
    string term = "";

    // !TODO create Node data structure to hold the data for the parse tree

    while(if_code[CURSOR] != '\0') {
        term += if_code[CURSOR];

        if(term.compare("if") == 0) {
            // handle token add
            cout<< "If found"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        unpack_condition(condition);
        unpack_block(block_code);
    }

}


void Lexer::unpack_while(string code) {
    const char* while_code = code.c_str();
    int CURSOR = 0;
    string while_token = "";
    bool while_token_found = false;

    while(while_code[CURSOR] != '\0') {
        while_token += while_code[CURSOR];

        if(while_token.compare("while") == 0) {
            cout<< endl<< endl<< "while token found"<< endl;
            while_token_found = true;
            break;
        }

        CURSOR++;
    }

    if(while_token_found) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);

        unpack_condition(condition);
        unpack_block(block_code);
    }

}


void Lexer::unpack_block(string sample_code) {
    const char* block_code = sample_code.c_str();
    int BLOCK_CURSOR = 1;
    string token_found = "";

    while(block_code[BLOCK_CURSOR] != '\0') {

        if(token_found.compare("") == 0 && (block_code[BLOCK_CURSOR] == ' ' || block_code[BLOCK_CURSOR] == '\n' || block_code[BLOCK_CURSOR] == '\t')) {
            
            if(block_code[BLOCK_CURSOR] == '\n') {
                // handle new line
            }

            BLOCK_CURSOR++;
            continue;

        } else {

            if(block_code[BLOCK_CURSOR] == ';') {
                unpack_line(token_found);
                token_found = "";
            } else {
                token_found += block_code[BLOCK_CURSOR];

                if(token_found.compare("if") == 0 || token_found.compare("while") == 0) { // handle conditionals

                    if(token_found.compare("if") == 0) {
                        BLOCK_CURSOR--; 
                        unpack_if(BLOCK_CURSOR, sample_code);
                    } else {
                        BLOCK_CURSOR -= 4;
                        unpack_while(sample_code);
                    }


                    token_found = "";
                }


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
                            unpack_function_call(current);
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

// This does not allow for nested conditions
void Lexer::unpack_condition(string source_code) {
    const char* condition = source_code.c_str();
    Queue<string> condition_queue;
    int CURSOR = 1;
    CFG cfg;

    // split conditions
    string condition_found = "";

    // offload conditions
    while(condition[CURSOR] != '\0') {
        
        if(condition[CURSOR] == '&' || condition[CURSOR] == '|') {

            if(condition[CURSOR] == '&') {
 
                if(condition[CURSOR + 1] == '&') {
                    condition_queue.enqueue(condition_found);
                    condition_queue.enqueue("&&");
                    condition_found = "";
                } else {
                    cout<< "Expected '&&' as a connector after condition: "<< condition<< endl;
                }

            } else {// handle or connector
 
                if(condition[CURSOR + 1] == '|') {
                    condition_queue.enqueue(condition_found);
                    condition_queue.enqueue("||");
                    condition_found = "";
                } else {
                    cout<< "Expected '||' as a connector after condition: "<< condition<< endl;
                }

            }

            CURSOR += 2;
            continue;
        } else {

            if(condition[CURSOR] != '(') {

                if(condition[CURSOR] != ')') {

                    if(condition[CURSOR] != ' ' && condition_found.compare("") == 0) {
                        condition_found += condition[CURSOR];
                    } else if(condition_found.compare("") != 0)
                        condition_found += condition[CURSOR];

                } else {

                    if(condition_found.compare("") != 0) {
                        condition_queue.enqueue(condition_found);
                    }

                }

            } else {
                cout<< "Nested conditions not allowed in this mini java... Skipping over nested condition"<< endl;
                
                while(condition[CURSOR] != ')') {
                    CURSOR++;
                }

                CURSOR++;
                continue;
            }
        }
        
        CURSOR++;
    }

    // verify variables
    for(string conditions: condition_queue.get_init_queue()) {
        
        string cnd = "";

        cout<< "CURRENT TOKEN: "<< conditions<< endl;
        if(conditions.compare("&&") != 0 && conditions.compare("||") != 0) {
            break_down_condition(conditions.c_str());
        }

    }

    // push in token stream

}


// utiltiies
vector<string> Lexer::break_down_condition(const char* condition) {
    cout<< "Breaking down: "<< condition<< endl;
    CFG cfg;
    char COMPARATOR_TOKENS[] = {'>', '<', '=', '!'};

    int CURSOR = 0;

    vector<string> conditions;
    string last_cond = "";
    string last_cond_type = "";
    
    while(condition[CURSOR] != '\0') {
        
        if(condition[CURSOR] != ' ') {
            bool comp_token_found = false;
            
            for(int i=0; i<4; i++) { // searches for a comparisson symbol eg: '>', '<', '!' and their equivalent 'or equal to:' 

                if(!comp_token_found) {
                    comp_token_found = COMPARATOR_TOKENS[i] == condition[CURSOR];
                    if(comp_token_found) {
                        break;
                    }
                }

            }

            if(comp_token_found) {

                if(last_cond.compare("") != 0) {

                    if(is_function_call(last_cond)) {
                        unpack_function_call(last_cond);
                        cout<< "Token added -> "<< last_cond<< endl;
                        last_cond_type = "variable";
                    } else if(cfg.is_word(last_cond.c_str())) {
                        string* param = SYMBOL_TABLE->find(last_cond);

                        if(param[0].compare("undefined") != 0) {
                            cout<< "Token added: "<< last_cond<< endl;
                        } else {
                            cout<< "Token: '"<< last_cond<<"' added as \"undefined_token\""<< endl;
                        }

                        last_cond_type = "variable";

                    } else {

                        if(cfg.is_condition(last_cond.c_str())) {
                            cout<< last_cond<< " token added"<< endl;
                            last_cond_type = "variable";
                        } else {
                            cout<< "INVALID token: "<< last_cond<< " passed as a condition param"<< endl;
                        }

                    }

                    conditions.push_back(last_cond);
                    last_cond = "";
                }

                if(condition[CURSOR + 1] == '=') {
                    string comparator_token = "";
                    comparator_token += condition[CURSOR];
                    comparator_token += condition[CURSOR + 1];

                    if(conditions.size() > 0) { // checks condition progression

                        if(last_cond_type.compare("variable") == 0) {
                            cout<< "Comparator tokken added: "<< comparator_token<< endl;
                            conditions.push_back(comparator_token);
                        } else {
                            cout<< "Invalid progression. Expcted variable or condition before comparisson operator"<< comparator_token<< endl;
                        }

                    } else {
                        cout<< "Invalid progression. Expcted variable or condition before comparisson operator"<< comparator_token<< endl;
                    }

                    CURSOR++;
                } else {

                    if(condition[CURSOR + 1] != ' ') {
                        string comparator_token = "";
                        comparator_token += condition[CURSOR];
                        comparator_token += condition[CURSOR + 1];
                        cout<< "invalid token progression: \""<< comparator_token<< "\""<< endl;
                        CURSOR++;
                    }

                }

            } else {
                last_cond += condition[CURSOR];
            }

        } else {

            while(condition[CURSOR + 1] ==  ' ') {
                CURSOR++;
            }

            // continue;
        }

        CURSOR++;
    }

    // the while loop does not cater for adding of the last condition
    if(last_cond.compare("") != 0) {

        if (!is_function_call(last_cond) && !cfg.is_word(last_cond.c_str())){
            cout<< "Invalid token '"<< last_cond<<"'at end of condition"<< endl;
        } else {
            conditions.push_back(last_cond);
            cout<< "Token added -> "<< last_cond<< endl;
        }

    }

    // for(string con: conditions) {
        // cout<< "COndition"<< con<< endl;
    // }

    return conditions;

}