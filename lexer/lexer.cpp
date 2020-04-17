// main engine and class utilities are located in this file
// all other lexer components are distributed to the individual files
#include "lexer.h"

#include "../utilities/data_structures/node.h"

void Lexer::scan_code() {
    unpack_package(source_code, "package");
    
    // this while-loop helps for the accounting for the closure of imports
    // if the term found is not an import key word,
    // it resets the CURSOR the branch that was made, and then breaks the gameloop
    // else it resets the CURSOR to the BRANCH made and then breaks out of the gameloop
    while(true) { // gameloop
        int BRANCH = CURSOR;

        // skip all the new lines
        while(source_code[CURSOR] == ' ' || source_code[CURSOR] == '\n') {
            CURSOR++;
        }

        std::string term_found = "";
        
        while(source_code[CURSOR] != ' ' && source_code[CURSOR] != '\t' && source_code[CURSOR] != '\n') {
            term_found += source_code[CURSOR];
            CURSOR++;
        }

        if(term_found.compare("import") == 0) {
            CURSOR = BRANCH;
            unpack_package(source_code, "import");
        } else {
            CURSOR = BRANCH;
            break;
        }

    }

    unpack_class(source_code);
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


bool Lexer::is_function_call(string current) {
    bool is_func = true;
    const char* function_call = current.c_str();
    int CURSOR_TRACK = 0;
    bool opening_bracket = false;
    bool closing_bracket = false;
    string function_name = "";

    // basically checks for opening and closing brackets and the lack of the equals sign
    while(function_call[CURSOR_TRACK] != '\0') {

        if(!opening_bracket) {
            // the below control dtructure chucks out code that may be mistaken for function calls just by
            // the presence of brackets
            if(function_call[CURSOR_TRACK] == '=')
                break;

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