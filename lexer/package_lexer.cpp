#include "lexer.h"



void Lexer::unpack_package(string source_code, string package_type) {
    Node* package_declaration;

    if(package_type.compare("package") == 0) {
        package_declaration = new Node(false, "user_package_declaration");
    } else {
        package_declaration = new Node(false, "import_declaration");
    }

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
                        Node pd(true, "package");
                        package_declaration->add_children(pd);
                        cout<< "\033[1;21mpackage\033[0m token added"<< endl;
                    } else {
                        package_declaration->add_children(Node(true, "import"));
                        cout<< "\033[1;21mimport\033[0m token added"<< endl;
                    }

                    opening_term_parsed = true;
                    CURSOR++;
                    
                    while(code[CURSOR] != ';' && code[CURSOR] != ' ' && code[CURSOR] != '\0' && code[CURSOR] != '\n') {
                        package_name += code[CURSOR];

                        CURSOR++;                        
                    }

                    bool is_package = (mini_java_cfg.is_package_name(package_name.c_str()));

                    if(is_package) {
                        // add token
                        package_declaration->add_children(Node(false, "package_declaration", package_name));
                        cout<< "Package declaration: \"\033[1;21m"<< package_name << "\033[0m token added"<< endl;
                    } else {
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
                        error_message = "Expected \033[1;21m';'\033[0m before skipping ot a new line";
                        (*ERROR_STREAM)<< error_message;
                    } else {
                        // handle token add
                        package_declaration->add_children(Node(true, ";"));
                        cout<< "\033[1;21m;\033[0m token added"<< endl;
                        CURSOR++;
                    }

                    break;
                } else {

                    if(package_type.compare("package") == 0) {
                        error_message = "Error expected \033[1;21mpackage\033[0m to begin the package declaration";
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