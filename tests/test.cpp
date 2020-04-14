#include<iostream>

#include "../lexer/lexer.h"
#include "../lexer/error_stream.h"
#include "../lexer/token_stream.h"
#include "../parser/parser.h"
#include "../code_gen/code_gen.h"
#include "../code_gen/postfix_it.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

#include "lexer_tests/line_unpack_tests.cpp"
// #include "function_tests.cpp"
// #include "condition_tests.cpp"
#include "lexer_tests/lexer_tests.cpp"

// #include "code_gen_tests/if_else_tests.cpp"
#include "code_gen_tests/while_tests.cpp"

// #include "../code_gen/unpack_equation_2.cpp"


// int line_unpack_tests(PackageTable*, FunctionTable*, SymbolTable*);
// int function_tests(PackageTable*, FunctionTable*, SymbolTable*);
// int condition_tests(PackageTable*, FunctionTable*, SymbolTable*);
int lexer_tests(PackageTable*, FunctionTable*, SymbolTable*, TokenStream*, ErrorStream*);
std::string unpack_equation(Node, bool);
std::string unpack_equation(Node, std::string, bool);

int main() {
    ErrorStream* ERROR_STREAM = new ErrorStream();
    FunctionTable* FUNCTION_TABLE = new FunctionTable(ERROR_STREAM);
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();
    TokenStream* TOKEN_STREAM = new TokenStream();

    cout<< "\033[1;21;33mLexer Process\033[0m"<< endl<< endl;
    lexer_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE, TOKEN_STREAM, ERROR_STREAM);

    if(ERROR_STREAM->has_messages("ERRORS")) {
        ERROR_STREAM->print_errors();

        std::cout<< "\033[1;21;31mStopping\033[0m compilation process..."<< std::endl;
        std::cout<< "Please handle errors to continue to other processes"<< std::endl;
    } else {
        ERROR_STREAM->print_errors();
        cout<< endl<< "\033[1;21;33mRespective ParseTree\033[0m"<< endl<< endl;
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
        cout<< endl<< "\033[1;21;33mIntermediate Code\033[0m"<< endl<< endl;

        ICG::CodeGenerator code_gen(SYMBOL_TABLE, TOKEN_STREAM);
        code_gen.run();
    }


    return 0;
}