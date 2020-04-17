#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_while(int& CURSOR, string code, Node* RESPECTIVE_NODE) {
    // Node to hold all the while tokens
    Node whle(false, "while");
    const char* while_code = code.c_str();
    string while_token = "";
    bool while_token_found = false;

    // looking for the "while" terminal
    while(while_code[CURSOR] != '\0') {
        while_token += while_code[CURSOR];

        if(while_token.compare("while") == 0) {
            whle.add_children(Node(true, "while")); // token 1
            cout<< endl<< endl<< "while token found"<< endl;
            while_token_found = true;
            break;
        }

        CURSOR++;
    }

    if(while_token_found) {
        // find the condition param node
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        // find the block code
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);

        unpack_condition(condition, &whle); // token 2
        Node while_block_node(false, "block_code"); // token 3
        unpack_block(block_code, &while_block_node);
        whle.add_children(while_block_node);
    }

    RESPECTIVE_NODE->add_children(whle);
}