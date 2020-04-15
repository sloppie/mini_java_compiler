#include "lexer.h"

#include "../utilities/data_structures/node.h"

// this was used during tests and is not meant for use during production code
void Lexer::unpack_if(string code, Node* RESPECTIVE_NODE) {
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
            RESPECTIVE_NODE->add_children(Node(true, "if"));
            cout<< "\033[1;21mif\033[0m] token added"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        unpack_condition(condition, &if_else);
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
                    unpack_if(code, CURSOR, &if_else);
                } else {
                    string else_block = Lexer::find_bracketed_code(code, '{', CURSOR);
                    if_else.add_children(Node(true, "else"));
                    Node else_block_node(false, "block_code");
                    unpack_block(else_block, &else_block_node);
                    if_else.add_children(else_block_node);
                }

            } else {
                CURSOR = RESET_CURSOR;
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }

    }

    RESPECTIVE_NODE->add_children(if_else);
}


void Lexer::unpack_if(int& CURSOR, string code, Node* RESPECTIVE_NODE) {
    Node if_else(false, "if_else");
    const char* if_code = code.c_str();
    bool opening_term = false;
    string term = "";

    // create Node data structure to hold the data for the parse tree

    while(if_code[CURSOR] != '\0') {
        term += if_code[CURSOR];

        if(term.compare("if") == 0) {
            // handle adde=ing to Node tree
            if_else.add_children(Node(true, "if"));
            cout<< "\033[1;21mif\033[0m token added"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        // cout<< block_code<< endl;
        unpack_condition(condition, &if_else);
        Node if_block_node(false, "block_code");
        unpack_block(block_code, &if_block_node);
        if_else.add_children(if_block_node);
    }


    term = ""; // reset term to look for an 'else' 

    int RESET_CURSOR = CURSOR;
    // cout<< "This is reset cursor: "<< code[CURSOR]<< endl;
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
                term += if_code[CURSOR];
                CURSOR++;
            }

            if(term.compare("else") == 0) {
                // eliminate white space
                string second_term = "";

                while(if_code[CURSOR] == ' ') {
                    CURSOR++;
                }

                RESET_CURSOR = CURSOR;

                while(if_code[CURSOR] != ' ' && if_code[CURSOR] != '(') {
                    second_term += if_code[CURSOR];
                    CURSOR++;
                }

                if(second_term.compare("if") == 0) {
                    if_else.add_children(Node(true, "else"));
                    CURSOR = RESET_CURSOR;
                    unpack_if(code, CURSOR, &if_else);
                    // this branch will be used ince the while recurses and does not find another if or else
                    RESET_CURSOR = CURSOR;
                    term = ""; // have to reset the term string to enable recursing again
                } else {
                    CURSOR = RESET_CURSOR;
                    string else_block = Lexer::find_bracketed_code(code, '{', CURSOR);
                    std::cout<< else_block<< std::endl;
                    if_else.add_children(Node(true, "else"));
                    Node else_block_node(false, "block_code");
                    unpack_block(else_block, &else_block_node);
                    if_else.add_children(else_block_node);
                    // this branch will be used ince the while recurses and does not find another if or else
                    RESET_CURSOR = CURSOR; 
                }

            } else {
                CURSOR = RESET_CURSOR;
                if_body_ended = true;
            }

        } else {
            if_body_ended = true;
        }
    }

    RESPECTIVE_NODE->add_children(if_else);
}


void Lexer::unpack_if(string code, int& CURSOR, Node* RESPECTIVE_NODE) {
    const char* if_code = code.c_str();
    bool opening_term = false;
    string term = "";

    while(if_code[CURSOR] != '\0') {
        term += if_code[CURSOR];

        if(term.compare("if") == 0) {
            RESPECTIVE_NODE->add_children(Node(true, "if")); // token 1
            cout<< "\033[1;21mif\033[0m token added"<< endl;
            opening_term = true;
            break;
        }

        CURSOR++;
    }

    if(opening_term) {
        string condition = Lexer::find_bracketed_code(code, '(', CURSOR);
        string block_code = Lexer::find_bracketed_code(code, '{', CURSOR);        
        cout<< block_code<< endl;
        unpack_condition(condition, RESPECTIVE_NODE);
        Node if_block_node(false, "block_code");
        unpack_block(block_code, &if_block_node);
        RESPECTIVE_NODE->add_children(if_block_node);
    }

}