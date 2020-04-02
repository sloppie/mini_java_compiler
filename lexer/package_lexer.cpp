#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_package(string source_code, string package_type) {
    Node* package_declaration;

    if(package_type.compare("package") == 0) {
        package_declaration = new Node(false, "user_package_declaration");
        cout<< "Unpacking package declaration..."<< endl;
    } else {
        package_declaration = new Node(false, "import_declaration");
        cout<< "Unpacking import declaration..."<< endl;
    }

    // int CURSOR = 0;
    const char* code = source_code.c_str();
    string term_found = "";
    bool opening_term_parsed = false;
    string package_name = "";
    int BRANCH;
    CFG mini_java_cfg;

    string error_message;

    while(code[CURSOR] == '\n') {
        // handle new line
        ERROR_STREAM->new_line();
        CURSOR++;
    }

    while(code[CURSOR] != '\n') {

        if(!(term_found.compare("") == 0 && (code[CURSOR] == ' ' || code[CURSOR] == '\t'))) {
            
            if(code[CURSOR] == ' ') {

                if(term_found.compare(package_type) == 0) {

                    if(package_type.compare("package") == 0) {
                        Node package_node(true, "package");
                        package_declaration->add_children(package_node);
                    } else {
                        Node package_node(true, "import");
                        package_declaration->add_children(package_node);
                    }

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
                        // add token
                        Node package_dec(false, "package_declaration", package_name);
                        package_declaration->add_children(package_dec);
                        cout<< "Valid package name identified: \""<< package_name<< "\""<< endl;
                    } else {
                        cout<< "Invalide package name: \""<< package_name<< "\""<< endl;
                        // generating error message below
                        error_message = "Package Name: \033[1;0m";
                        error_message += package_name;
                        error_message += "\033[0m is invalid";

                        (*ERROR_STREAM)<< error_message;
                    }

                    if(code[CURSOR] == ' ') { // whitespace remover

                        while(code[CURSOR] == ' ') {
                            CURSOR++;
                        }

                    }

                    if(code[CURSOR] == '\n') {
                        cout<< "expected ';' before moving on to a new line"<< endl;
                        error_message = "Expected \033[1;0m';'\033[0m before skipping ot a new line";
                        (*ERROR_STREAM)<< error_message;
                    } else {
                        // handle token add
                        Node semi_colon_token(true, ";");
                        package_declaration->add_children(semi_colon_token);
                        CURSOR++;
                    }

                    break;
                } else {

                    if(package_type.compare("package") == 0) {
                        // cout<< "Expected the token \"package\""<< endl;
                        error_message = "Error expected \033[1;0mpackage\033[0m to begin the package declaration";
                        (*ERROR_STREAM)<< error_message;
                    } else {
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
        // cout<< "Invalid package structure: expected: <import_keyword> | <package_keyword> <package_name>;"<< endl;
        error_message = "Invalid package structure: expected: <import_keyword> | <package_keyword> <package_name>;";
        (*ERROR_STREAM)<< error_message;
    }

    (*TOKEN_STREAM)<< (*package_declaration);

}


bool Lexer::package_parser(string code) {
    const char* package_code = code.c_str();
    int CURSOR = 0;

    return false;
}

