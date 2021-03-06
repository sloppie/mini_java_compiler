#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_class(string code) {
    Node class_declaration(false, "class_declaration");
    string access_modifier = "";
    string class_name = "";
    string class_token = "";

    string term_found = "";
    string error_message = "";

    bool class_closed = false;

    const char* class_code = code.c_str();

    // this is loop is used to find: access mmodifier, class_name, opening_brace, cvd, function_declarations and closing brace
    while(class_code[CURSOR] != '\0') {

        if((term_found.compare("") == 0) && (class_code[CURSOR] == ' ' || class_code[CURSOR] == '\n' || class_code[CURSOR] == '\t')) {
            
            if(class_code[CURSOR] == '\n') {
                // handle new line
                ERROR_STREAM->new_line();
            }

            CURSOR++;
            continue;

        } else if(code[CURSOR] == ' ') {
                // class access modifier
                if(term_found.compare("public") == 0 || term_found.compare("private") == 0 || term_found.compare("protected") == 0) { // handle conditionals
                    int FUNCTION_BRANCH;
                    int VARIABLE_DEC_BRANCH;
                    access_modifier = term_found;
                    bool is_func = false;

                    class_declaration.add_children(Node(false, "access_modifier", access_modifier));
                    cout<< "Access modifier for a \033[1;21m"<< access_modifier<< "\033[0m class added"<< endl;

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    while(code[CURSOR] != ' ' && code[CURSOR] != '{') {
                        class_token += code[CURSOR];

                        CURSOR++;
                    }

                    // verify the finding of the class token
                    if(class_token.compare("class") == 0) {
                        class_declaration.add_children(Node(true, "class"));
                        cout<< "\033[1;21mclass\033[0m token added"<< endl;
                    } else {
                        error_message = "Expected \033[1;21mclass\033[0m token";
                        
                        (*ERROR_STREAM)<< error_message;
                    }

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    while(code[CURSOR] != ' ' && code[CURSOR] != '{') {
                        class_name += code[CURSOR];

                        CURSOR++;
                    }

                    // verify the class name
                    if(CFG().is_word(class_name.c_str())) {
                        // handle class name to package table
                        class_declaration.add_children(Node(false, "class_name", class_name));
                        cout<< "Class name\033[1;21m"<< class_name<< "\033[0m token added"<< endl;
                    } else {
                        error_message = "Invalid class name: \033[1;0m";
                        error_message += class_name;
                        error_message += "\033[0m";
                        (*ERROR_STREAM)<< error_message;
                        error_message = "";
                    }

                    while(code[CURSOR] == ' ') {
                        CURSOR++;
                    }

                    // class opening curly brace
                    if(code[CURSOR] == '{') {
                        // handle terminal addition
                        cout<< "\033[1;21m{\033[0m token added"<< endl;
                        class_declaration.add_children(Node(true, "{"));

                        CURSOR++;
                        break;
                    } else {
                        error_message = "Expected \033[1;21m{\033[0m token to open up class body";
                        (*ERROR_STREAM)<< error_message;
                        error_message = "";
                    }

                }

            } else {
                term_found += code[CURSOR];
            }

        CURSOR++;
    }

    term_found = "";

    // finds the class variable definitions and function_declarations
    while(class_code[CURSOR] != '\0') {

        if(term_found.compare("") == 0 && (class_code[CURSOR] == ' ' || class_code[CURSOR] == '\n' || class_code[CURSOR] == '\t')) {
            
            if(class_code[CURSOR] == '\n') {
                // handle new line
                ERROR_STREAM->new_line();
            }

            CURSOR++;
            continue;

        } else if(code[CURSOR] == ' ') {
                
                // finds the access_modifier of the class_variable_declaration or function_declaration 
                if(term_found.compare("public") == 0 || term_found.compare("private") == 0 || term_found.compare("protected") == 0) { // handle conditionals
                    // scanning calls for the creation of two branches:
                    // The function branch helps reset to the initial position so that if it is a function it is handed over
                    // to the FunctionTable::scan_function method
                    int FUNCTION_BRANCH;
                    // This branch recodrs the current position right after the access modifier so that if it is a cvd,
                    // it is passes as a line to Lexer::unpack_line method.
                    int VARIABLE_DEC_BRANCH;
                    bool is_func = false;

                    if(term_found.compare("public") == 0) {
                        FUNCTION_BRANCH = CURSOR - 6;
                    } else if(term_found.compare("private") == 0) {
                        FUNCTION_BRANCH = CURSOR - 7;
                    } else {
                        FUNCTION_BRANCH = CURSOR - 9;
                    }

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    VARIABLE_DEC_BRANCH = CURSOR;

                    term_found = "";

                    while(class_code[CURSOR] != '\n') {

                        if(class_code[CURSOR] == '(') { // enforce opening curly brace check to avoid sending function calls as fnction definitions
                            CURSOR = FUNCTION_BRANCH;
                            cout<< class_code[CURSOR]<< endl;
                            Node function_declaration = FUNCTION_TABLE->scan_function(code, CURSOR);
                            string function_block = Lexer::find_bracketed_code(code, '{', CURSOR);
                            Node blc_code(false, "block_code");
                            unpack_block(function_block, &blc_code); // Node memory address passed to allow easy adding of nodes to the parent node
                            function_declaration.add_children(blc_code);
                            is_func = true;
                            CURSOR--; // reset the cursor back by one so that it does not skip over a character in the while loop
                            class_declaration.add_children(function_declaration);
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
                            error_message = "Expected \033[1;21m';'\033[0m before skipping to a new line";
                            (*ERROR_STREAM)<< error_message;
                        } else {
                            Node class_var_dec(false, "class_variable_declaration");
                            class_var_dec.add_children(Node(false, "access_modifier", access_modifier));
                            unpack_line(variable_dec, &class_var_dec);
                            class_var_dec.add_children(Node(true, ";"));
                            term_found = "";

                            class_declaration.add_children(class_var_dec);
                            // since the line has already been added,
                            // we need to skip over to the first new line that we find
                            while(code[CURSOR] != '\n') {
                                CURSOR++;
                            }

                            ERROR_STREAM->new_line();
                            CURSOR++;
                            continue;

                        }

                    } else {
                        term_found = "";
                        ERROR_STREAM->new_line();
                        CURSOR++;
                        continue;
                    }

                } else {
                }


        } else {
            term_found += class_code[CURSOR];

            if(term_found.compare("}") == 0) {
                class_declaration.add_children(Node(true, "}"));
                class_closed = true;
                break;
            }
        }

        CURSOR++;
    }

    if(!class_closed) {
        error_message = "Expected \033[1;21m}\033[0m to close class declaration";
        (*ERROR_STREAM)<< error_message;
        error_message = "";
    }

    (*TOKEN_STREAM)<< class_declaration;
}