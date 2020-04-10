#include<iostream>


#ifndef LINE_UNPACK_TESTS
#define LINE_UNPACK_TESTS

using namespace std;

int line_unpack_tests(PackageTable* PACKAGE_TABLE, FunctionTable* FUNCTION_TABLE, SymbolTable* SYMBOL_TABLE, ErrorStream* ERROR_STREAM, TokenStream* TOKEN_STREAM) { 

    string lines[] = {
        "int myVar = 2",
        "double secondVar = 0.234 + 5.6 - 2.5",
        "float secondVar = 0.234 + my_func() - - 2.5",
        "0.234 + 5.6",
        "myVar = 0 + 2",
        "int myVar",
        "myVar",
        "main()",
        "main(myVar, myVar)"
    };

    Lexer lexical_analyser("pacage com.joocy;", SYMBOL_TABLE, PACKAGE_TABLE, FUNCTION_TABLE, TOKEN_STREAM, ERROR_STREAM);

    for(int i=0; i<9; i++) {
        // lexical_analyser.unpack_line(lines[i]);
    }

    // lexical_analyser.unpack_while("while(myVar == myVar) {\n    int i = 0;\n    if(secondVar == secondVar) {\n        int x = 0;\n    }\n}");
    lexical_analyser.unpack_class("public class ClassOne {\n    public int myInt = 0;\n}");
    return 0;

}

#endif