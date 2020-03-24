#ifndef LEXER_H
#define LEXER_H

#include<iostream>

#include "../utilities/data_structures/stack.h"
#include "../utilities/function_table.h"
#include "../utilities/symbol_table.h"
#include "../utilities/package_table.h"

using namespace std;

class Lexer {
    public:
        Lexer(string, SymbolTable*, FunctionTable*, PackageTable*);
        string find_bracketed_code(char);

    private:
        string source_code;
        int CURSOR;

        SymbolTable* SYMBOL_TABLE;
        FunctionTable* FUNCTION_TABLE;
        PackageTable* PACKAGE_TABLE;
};

#endif