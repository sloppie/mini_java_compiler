#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include<iostream>
#include<vector>

#include "../utilities/data_structures/node.h"

using namespace std;

class TokenStream {

    public:
        TokenStream() {}
        // treats the TOKEN_STREAM like a data stream where << operator passes data to it.
        // This method add tokens that passed lexical verification to the TokenStream 
        // This TokenStream is to be passsed to the lexer
        void operator<<(Node);
        // this is used to pass on the next token that was added to the token stream in
        // queue format (FIFO basis) to the Parser and ICG::CodeGenerator.
        Node next_token();
        // this is resets the position of the queue of resending tokens through the
        // TOKENSTREAM back to 0. This helps in instances like the CodeGenerator wanting to access
        // the TOKEN_STREAM using TokenStream::next_token after the Parser is done with it.
        void reset_position();
        // returns the size of the the TOKENS_TREAM so as to enable accurate picking of all the tokens
        int size();

    private:
        vector<Node> TOKEN_STREAM;
        int POSITION = 0;

};

#endif