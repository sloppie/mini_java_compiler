#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_block(string sample_code, Node* RESPECTIVE_NODE) {
    const char* block_code = sample_code.c_str();
    int BLOCK_CURSOR = 1;
    string token_found = "";

    while(block_code[BLOCK_CURSOR] != '\0') {

        if(token_found.compare("") == 0 && (block_code[BLOCK_CURSOR] == ' ' || block_code[BLOCK_CURSOR] == '\n' || block_code[BLOCK_CURSOR] == '\t')) {
            
            if(block_code[BLOCK_CURSOR] == '\n') {
                // handle new line
                ERROR_STREAM->new_line();
            }

            BLOCK_CURSOR++;
            continue;

        } else {

            if(block_code[BLOCK_CURSOR] == ';') {
                cout<< "\033[1;21m"<< token_found<< "\033[0m"<< endl;
                Node new_line(false, "statements", "line");
                unpack_line(token_found, &new_line);
                new_line.add_children(Node(true, ";"));
                RESPECTIVE_NODE->add_children(new_line);
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
                    continue;
                }


            }
        }

        BLOCK_CURSOR++;
    }


}
