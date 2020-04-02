#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_while(string code) {
    Node whle(false, "while");
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
        unpack_block(block_code, &whle);
    }

}