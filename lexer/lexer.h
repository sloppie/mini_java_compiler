
#ifndef LEXER_H
#define LEXER_H

#include<iostream>

#include "token_stream.h"
#include "error_stream.h"
#include "../utilities/package_table.h"
#include "../utilities/function_table.h"
#include "../utilities/symbol_table.h"
#include "../utilities/data_structures/stack.h"
#include "../utilities/data_structures/queue.h"
#include "../language_cfg/language_cfg.h"

using namespace std;

class Lexer { 

    public:
        Lexer(
            string source_code,
            SymbolTable *SYMBOL_TABLE,
            PackageTable *PACKAGE_TABLE,
            FunctionTable *FUNCTION_TABLE,
            TokenStream *TOKEN_STREAM,
            ErrorStream *ERROR_STREAM) : source_code(source_code),
                                         SYMBOL_TABLE(SYMBOL_TABLE),
                                         PACKAGE_TABLE(PACKAGE_TABLE),
                                         FUNCTION_TABLE(FUNCTION_TABLE),
                                         TOKEN_STREAM(TOKEN_STREAM),
                                         ERROR_STREAM(ERROR_STREAM) {}

        static string find_bracketed_code(string, char, int&);
        void scan_code();

        bool is_function_call(string);
        bool is_equation_token(string);

        void unpack_package(string, string);
        bool package_parser(string);
        void unpack_class(string);
        void unpack_if(string);
        void unpack_if(string, int&);
        void unpack_if(int&, string);
        void unpack_while(string);
        void unpack_condition(string);
        void unpack_block(string, Node*);
        void unpack_line(string, Node*);
        void unpack_arithmetic_eq(Queue<string>, string, Node*);
        void unpack_function_call(string, Node*);

        vector<string> break_down_condition(const char*);

    private:
        string source_code;
        int CURSOR;
        string EQUATION_TOKENS[4] = {"*", "/", "+", "-"};
        int EQ_TOKEN_SIZE = 4;
        int LINE_NUMBER = 0;

        SymbolTable* SYMBOL_TABLE;
        PackageTable* PACKAGE_TABLE;
        FunctionTable* FUNCTION_TABLE;
        TokenStream* TOKEN_STREAM;
        ErrorStream* ERROR_STREAM;
        vector<string> CONTEXT;

};

#endif