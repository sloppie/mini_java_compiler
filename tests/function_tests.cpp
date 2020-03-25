#include<iostream>

#include "../lexer/lexer.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

using namespace std;


int function_tests() {
    string sample_function = "public int main (int kwargs, string legs, Dread dread) {\n    int i = 0;\n}";
    FunctionTable* FUNCTION_TABLE = new FunctionTable();
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();
    Lexer lexical_analyser(sample_function, SYMBOL_TABLE, PACKAGE_TABLE);
    int CURSOR = 0;

    string paramter_code = Lexer::find_bracketed_code(sample_function, '(', CURSOR);
    string block_code = Lexer::find_bracketed_code(sample_function, '{', CURSOR);

    FUNCTION_TABLE->scan_function(sample_function);

    return 0;
}