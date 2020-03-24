#include "lexer.h"

Lexer::Lexer(string source_code, SymbolTable* SYMBOL_TABLE, FunctionTable* FUNCTION_TABLE, PackageTable* PACKAGE_TABLE): source_code(source_code), SYMBOL_TABLE(SYMBOL_TABLE), FUNCTION_TABLE(FUNCTION_TABLE), PACKAGE_TABLE(PACKAGE_TABLE) {
    this->source_code = source_code;
    CURSOR = 0;
}

string Lexer::find_bracketed_code(char bracket_type) {
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