#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_class(string code) {
    cout<< "Unpacking class..."<< endl;

    Node class_declaration(false, "class_declaration");
    string access_modifier = "";
    string class_name = "";
    string class_token = "";

    string term_found = "";
    string error_message = "";

    bool class_closed = false;

    const char* class_code = code.c_str();

    while(class_code[CURSOR] != '\0') {

        if((term_found.compare("") == 0) && (class_code[CURSOR] == ' ' || class_code[CURSOR] == '\n' || class_code[CURSOR] == '\t')) {
            
            if(class_code[CURSOR] == '\n') {
                // handle new line
                ERROR_STREAM->new_line();
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

                    //handle token addition
                    Node axs_mod(false, "access_modifier", "public");
                    class_declaration.add_children(axs_mod);

                    while(code[CURSOR] == ' ') { // white space eliminator
                        CURSOR++;
                    }

                    while(code[CURSOR] != ' ' && code[CURSOR] != '{') {
                        class_token += code[CURSOR];

                        CURSOR++;
                    }

                    if(class_token.compare("class") == 0) {
                        class_declaration.add_children(Node(true, "class"));
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

                    if(CFG().is_word(class_name.c_str())) {
                        // handle class name to package table
                        class_declaration.add_children(Node(false, "class_name", class_name));
                        // cout<< "Class name: "<< class_name<< endl;
                    } else {
                        error_message = "Invalid class name: \033[1;0m";
                        error_message += class_name;
                        error_message += "\033[0m";
                        (*ERROR_STREAM)<< error_message;
                        error_message = "";
                        
                        // cout<< "Invalid class name \""<< class_name<< "\""<< endl;
                    }

                    while(code[CURSOR] == ' ') {
                        CURSOR++;
                    }

                    if(code[CURSOR] == '{') {
                        // handle terminal addition
                        Node open_curly(true, "{");
                        class_declaration.add_children(open_curly);
                        CURSOR++;
                        break;
                    } else {
                        error_message = "Expected \033[1;0m{\033[0m token to open up class body";
                        (*ERROR_STREAM)<< error_message;
                        error_message = "";
                        // cout<< "expected '{' token to open up the class body"<< endl;
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
                ERROR_STREAM->new_line();
            }

            CURSOR++;
            continue;

        } else if(code[CURSOR] == ' ') {

                if(term_found.compare("public") == 0 || term_found.compare("private") == 0 || term_found.compare("protected") == 0) { // handle conditionals
                    int FUNCTION_BRANCH;
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
                            unpack_block(function_block, &function_declaration); // Node memory address passed to allow easy adding of nodes to the parent node
                            is_func = true;
                            CURSOR--; // reset the cursor back by one so that it does not skip over a character in the while loop
                        }

                        // below is the piece of code that will be used to pass function calls 
                        // if they are to be allowed to the class declaration phase
                        // if(is_func) {
                        //     is_func = class_code[CURSOR] == ';';
                        // }

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
                            // cout<< "Error in line Expected ';' at the end of line"<< endl;
                        } else {
                            Node class_var_dec(false, "class_variable_declaration");
                            class_var_dec.add_children(Node(false, "access_modifier", access_modifier));
                            unpack_line(variable_dec, &class_var_dec);
                            class_var_dec.add_children(Node(true, ";"));
                            term_found = "";

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
                    // !TODO add error handling
                    // if(term_found.compare("}") == 0) {
                    //     Node closing_brace(true, "}");
                    //     class_declaration.add_children(closing_brace);
                    //     class_closed = true;
                    //     break;
                    // }
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

}