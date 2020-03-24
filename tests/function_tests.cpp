#include<iostream>

#include "../lexer/lexer.h"
#include "../utilities/function_table.h"
#include "../utilities/symbol_table.h"

using namespace std;


int main() {
    string sample_function = "public int main (int kwargs, string legs, Dread dread) {\n    int i = 0;\n}";
    FunctionTable* FUNCTION_TABLE = new FunctionTable();
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    Lexer lexical_analyser(sample_function, SYMBOL_TABLE, FUNCTION_TABLE);

    string paramter_code = lexical_analyser.find_bracketed_code('(');
    string block_code = lexical_analyser.find_bracketed_code('{');

    FunctionTable().scan_function(sample_function);

    return 0;
}