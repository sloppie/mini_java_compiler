
#ifndef LEXER_H
#define LEXER_H

#include<iostream>

#include "../utilities/function_table.h"
#include "../utilities/data_structures/stack.h"
#include "../utilities/data_structures/queue.h"
#include "../utilities/symbol_table.h"
#include "../utilities/package_table.h"
#include "../language_cfg/language_cfg.h"

using namespace std;

class Lexer { 
    public:
        Lexer(string, SymbolTable*, PackageTable*, FunctionTable*);
        static string find_bracketed_code(string, char, int&);
        void unpack_block(string);
        // void unpack_if(int&);
        // void unpack_while(int&);
        void unpack_line(string);
        // void unpack_variable_dec(int&);
        void unpack_arithmetic_eq(Queue<string>, string);
        void unpack_function_call(string);
        bool is_function_call(string);

        bool is_equation_token(string);

    private:
        string source_code;
        int CURSOR;
        string EQUATION_TOKENS[4] = {"*", "/", "+", "-"};
        int EQ_TOKEN_SIZE = 4;

        SymbolTable* SYMBOL_TABLE;
        PackageTable* PACKAGE_TABLE;
        FunctionTable* FUNCTION_TABLE;
};

#endif