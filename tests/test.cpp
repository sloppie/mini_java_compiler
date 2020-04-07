#include<iostream>

#include "../lexer/lexer.h"
#include "../lexer/error_stream.h"
#include "../lexer/token_stream.h"
#include "../parser/parser.h"
#include "../code_gen/postfix_it.h"
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

    // lexer_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE, TOKEN_STREAM, ERROR_STREAM);

    // if(ERROR_STREAM->has_messages("ERRORS")) {
    //     ERROR_STREAM->print_errors();
    // } else {
    //     ERROR_STREAM->print_errors();
    //     Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
    //     Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
    //     Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
    // }

    Node line(false, "line");
    line.add_children(Node(false, "int2"));
    line.add_children(Node(true, "*"));
    line.add_children(Node(false, "int2"));
    line.add_children(Node(true, "/"));
    line.add_children(Node(false, "int2"));
    line.add_children(Node(true, "-"));
    line.add_children(Node(false, "int2"));
    line.add_children(Node(true, "+"));
    line.add_children(Node(false, "int2"));

    Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(ICG::postfix_it(line));
    return 0;
}