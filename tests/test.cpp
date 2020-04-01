#include<iostream>

#include "../lexer/lexer.h"
#include "../lexer/error_stream.h"
#include "../lexer/token_stream.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

#include "line_unpack_tests.cpp"
// #include "function_tests.cpp"
// #include "condition_tests.cpp"
#include "lexer_tests.cpp"

// int line_unpack_tests(PackageTable*, FunctionTable*, SymbolTable*);
// int function_tests(PackageTable*, FunctionTable*, SymbolTable*);
// int condition_tests(PackageTable*, FunctionTable*, SymbolTable*);
int lexer_tests(PackageTable*, FunctionTable*, SymbolTable*, TokenStream*, ErrorStream*);

int main() {
    ErrorStream* ERROR_STREAM = new ErrorStream();
    FunctionTable* FUNCTION_TABLE = new FunctionTable(ERROR_STREAM);
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();
    TokenStream* TOKEN_STREAM = new TokenStream();

    // function_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE);
    // line_unpack_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE);
    // condition_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE);
    cout<< "\033[1;33mthis is a test1\033[0m"<< endl;
    cout<< "End of test"<< endl;
    lexer_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE, TOKEN_STREAM, ERROR_STREAM);

    return 0;
}