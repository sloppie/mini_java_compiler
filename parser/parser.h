#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>

#include "../lexer/token_stream.h"
#include "../language_cfg/language_cfg.h"
#include "../utilities/symbol_table.h"
#include "../utilities/data_structures/queue.h"
#include "../utilities/data_structures/stack.h"
#include "../utilities/data_structures/node.h"
#include "term.h"

using namespace std;

// This class is used to compare the tokens passed through the TOKEN_STREAM,
// which  is the communication mode betweeen the Lexer and the Parser,
// with allowed token progression stated in the CFG_MAP.
// The SYMBOL_TABLE is also passed on to the lexer to help verify unique ids passed in the 
// and later on used to make the PARSE_TREE, which will then become the mode of communication betweeen
// the Lexer and the CodeGenerator class
class Parser {

    public:
        Parser(
            TokenStream* TOKEN_STREAM, 
            SymbolTable* SYMBOL_TABLE
        ): TOKEN_STREAM(TOKEN_STREAM),
            SYMBOL_TABLE(SYMBOL_TABLE) {}
        
        // This coordinates the unpacking of the cfg using the TOKEN_STREAM
        void engine();
        // used to pack the cfg node with the name passed in as a parameter.
        // In the case of multiple definitions of a node the vector returned is of size > 1
        // else it has a size of just one node
        vector<Queue<term>> unpack_cfg_node(string);
        // visit tree
        void visit_tree(Node);

    private:
        CFG LANGUAGE_CFG;
        TokenStream* TOKEN_STREAM;
        SymbolTable* SYMBOL_TABLE;
        Node* PARSE_TREE;
        int LEVEL = 0;
        int TEST_ID_NUMBER = 0;

};

#endif