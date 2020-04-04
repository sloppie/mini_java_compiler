#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include<iostream>
#include<vector>

#include "../utilities/data_structures/node.h"

using namespace std;

class TokenStream {

    public:
        TokenStream() {}
        // add tokens that passed lexical verification to the TokenStream 
        // This TokenStream is to be passsed to the lexer
        void operator<<(Node);
        Node next_token();

    private:
        vector<Node> TOKEN_STREAM;
        int POSITION = 0;

};

#endif