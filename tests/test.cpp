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

    cout<< endl<< "\033[1;21;33mLexer Process\033[0m"<< endl<< endl;
    lexer_tests(PACKAGE_TABLE, FUNCTION_TABLE, SYMBOL_TABLE, TOKEN_STREAM, ERROR_STREAM);

    if(ERROR_STREAM->has_messages("ERRORS")) {
        ERROR_STREAM->print_errors();
    } else {
        ERROR_STREAM->print_errors();
        cout<< endl<< "\033[1;21;33mRespective ParseTree\033[0m"<< endl<< endl;
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
        Parser(TOKEN_STREAM, SYMBOL_TABLE).visit_tree(TOKEN_STREAM->next_token());
    }

    Node line(false, "line");
    line.add_children(Node(false, "type_specified", "int"));
    line.add_children(Node(false, "property_name", "myVar"));
    line.add_children(Node(true, "="));
    line.add_children(Node(false, "number", "int2"));
    line.add_children(Node(true, "*"));
    line.add_children(Node(false, "number", "int2"));
    line.add_children(Node(true, "/"));
    line.add_children(Node(false, "number", "int2"));
    line.add_children(Node(true, "-"));
    line.add_children(Node(false, "number", "int2"));
    line.add_children(Node(true, "+"));
    line.add_children(Node(false, "number", "int8762"));

    Node line_2(false, "line");
    line_2.add_children(Node(false, "property_name", "myVar"));
    line_2.add_children(Node(true, "="));
    line_2.add_children(Node(false, "property_name", "myVar"));
    line_2.add_children(Node(true, "*"));
    line_2.add_children(Node(false, "number", "int2"));
    line_2.add_children(Node(true, "/"));
    line_2.add_children(Node(false, "number", "int2"));
    line_2.add_children(Node(true, "-"));
    line_2.add_children(Node(false, "number", "int2"));
    line_2.add_children(Node(true, "+"));
    line_2.add_children(Node(false, "number", "int8762"));
    cout<< endl<< "\033[1;21;33mIntermediate Code\033[0m"<< endl<< endl;
    // cout<< ICG::CodeGenerator(SYMBOL_TABLE, TOKEN_STREAM).unpack_equation(ICG::postfix_it(line));
    ICG::CodeGenerator code_gen(SYMBOL_TABLE, TOKEN_STREAM);
    code_gen.unpack_line(line);
    code_gen.unpack_line(line_2);

    return 0;
}