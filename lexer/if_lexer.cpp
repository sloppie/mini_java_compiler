#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_if(string code) {
    Node if_else(false, "if_else");
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
        unpack_block(block_code, &if_else);
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
                // ERROR_STREAM->new_line();
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
                CURSOR = RESET_CURSOR;
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }

    }


    //
}


void Lexer::unpack_if(int& CURSOR, string code) {
    Node if_else(false, "if_else");
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
        // cout<< block_code<< endl;
        unpack_condition(condition);
        unpack_block(block_code, &if_else);
    }


    term = ""; // reset term to look for an 'else' 

    int RESET_CURSOR = CURSOR;
    cout<< "This is reset cursor: "<< code[CURSOR]<< endl;
    bool if_body_ended = false;
    //
    while(!if_body_ended) {

        // eliminate white space
        while(if_code[CURSOR] != '\0' && (if_code[CURSOR] == ' ' || if_code[CURSOR] == '\n')) {
            
            if(if_code[CURSOR] == '\n') {
                // handle new line
                // ERROR_STREAM->new_line();
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
                CURSOR = RESET_CURSOR;
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }
    }

}


void Lexer::unpack_if(string code, int& CURSOR) {
    Node if_else(false, "if_else");
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
        cout<< block_code<< endl;
        unpack_condition(condition);
        unpack_block(block_code, &if_else);
    }

}