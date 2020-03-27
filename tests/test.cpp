#include<iostream>

#include "../lexer/lexer.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

#include "line_unpack_tests.cpp"
#include "function_tests.cpp"

int line_unpack_tests(PackageTable*, FunctionTable*, SymbolTable*);
int function_tests(PackageTable*, FunctionTable*, SymbolTable*);

int main() {

    FunctionTable* FUNCTION_TABLE = new FunctionTable();
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();

    function_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE);
    line_unpack_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE);
}