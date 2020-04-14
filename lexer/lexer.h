
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
#include "../utilities/data_structures/node.h"
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

        // unpacks packed code with regard to the bracket passed in arg_2
        // the source code is passed to the function and also the the CURSOR
        // is passed by reference to the function as psuedo-control-pass method
        static string find_bracketed_code(string, char, int&);
        // Lexer engine, controls running of the individual components on the source code
        void scan_code();

        // self explanatory method
        bool is_function_call(string);
        // checks id the string passed is an allowed arithmetic token
        bool is_equation_token(string);

        // parses import and user package declarations
        void unpack_package(string, string);
        bool package_parser(string);

        // unpacks the class while passing control to other components to handle parsing
        // i.e functions are parsed using FUNCTION_TABLE->scan_function method and Lexer::unpack_block
        // the class variable declrations are parsed by 
        void unpack_class(string);
        // Unpacks individual lines, checks for if, and while statements and passses
        // control to the respective component parser in the event that they are found
        // else the line is forwaded to Lexer::unpack_line
        void unpack_block(string, Node*);
        // Unpacks lines, adds new variables to the SYMBOL_TABLE,
        // passes control over to Lexer::unpack_arithmetic_eq to handle them
        // It also unpacks function calls using Lexer::unpack_function_call
        void unpack_line(string, Node*);
        // Checks for the validity of equations passed to it
        void unpack_arithmetic_eq(Queue<string>, string, Node*);
        // unpacks function calls with regard to argument type passed to it
        void unpack_function_call(string, Node*);

        // unpacks 'if' passed after the 'else' token
        // This function was added because i got too lazy to implement recursiveness
        void unpack_if(string, Node*);
        // unpacks 'if' statements keeping track of outside passed CURSORS
        void unpack_if(string, int&, Node*);
        // unpacks 'if' statements keeping track of outside passed CURSORS
        void unpack_if(int&, string, Node*);
        // unpacks 'while' with the help of Lexer::unpack_condition to unpack condition
        // the block code is parsed sing Lexer::unpack_block
        void unpack_while(int&, string, Node*);
        // unpacks condition statements and refuses implementation of nested conditions
        // this is done with the help of Lexer::break_down_condition
        void unpack_condition(string, Node*);
        vector<string> break_down_condition(const char*, Node*);


    private:
        string source_code;
        int CURSOR = 0;
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