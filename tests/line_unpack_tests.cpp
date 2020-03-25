#include<iostream>

#include "../lexer/lexer.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

#ifndef LINE_UNPACK_TESTS
#define LINE_UNPACK_TESTS

using namespace std;
int line_unpack_tests();

int line_unpack_tests() {
    FunctionTable* FUNCTION_TABLE = new FunctionTable();
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();
    Lexer lexical_analyser("pacage com.joocy;", SYMBOL_TABLE, PACKAGE_TABLE);

    string lines[] = {
        "int myVar = 2",
        "double secondVar = 0.234 + 5.6 - + 2.5",
        "int secondVar = 0.234 + 5.6 - - 2.5",
        "0.234 + 5.6",
        "0 + 2"
    };

    for(int i=0; i<5; i++) {
        lexical_analyser.unpack_line(lines[i]);
    }

    return 0;

}

#endif