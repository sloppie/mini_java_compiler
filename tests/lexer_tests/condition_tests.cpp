#include<iostream>

#include "../../types.h"
#include "../../lexer/lexer.h"
#include "../../utilities/function_table.h"
#include "../../utilities/package_table.h"
#include "../../utilities/symbol_table.h"


int condition_tests(PackageTable* PACKAGE_TABLE, FunctionTable* FUNCTION_TABLE, SymbolTable* SYMBOL_TABLE) {
    std::string sample_function = "int main() {}";
    
    Lexer lexical_analyser(sample_function, SYMBOL_TABLE, PACKAGE_TABLE, FUNCTION_TABLE);

    string condition[] = {
        "(kwargs == kwargs && kwargs == myVar)",
        "(my_var >= kwargs || kwargs != myVar)",
        "(kwargs <= kwargs || kwargs >= myVar)",
        "(kwargs != kwargs && kwargs <= myVar)",
        "(kwargs !! kwargs && kwargs <= myVar)",
    };

    for(int i=0; i<5; i++) {
        lexical_analyser.unpack_condition(condition[i]);
    }

    return 0;
}