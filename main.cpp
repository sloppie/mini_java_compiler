#include<iostream>

#include "utilities/fs.h"

#include "utilities/symbol_table.h"
#include "utilities/package_table.h"
#include "utilities/function_table.h"

#include "lexer/lexer.h"
#include "lexer/error_stream.h"
#include "lexer/token_stream.h"

#include "parser/parser.h"

#include "code_gen/code_gen.h"

int main()
{
    // read file
    std::string source_code = fs::read_file("/root/gitau/compiler_construction/sample_code/FindAverage.java");

    // utilities
    ErrorStream* ERROR_STREAM = new ErrorStream();
    TokenStream* TOKEN_STREAM = new TokenStream();
    SymbolTable* SYMBOL_TABLE = new SymbolTable();
    PackageTable* PACKAGE_TABLE = new PackageTable();
    FunctionTable* FUNCTION_TABLE = new FunctionTable(ERROR_STREAM);

    // compiler components
    Lexer lexer(
        source_code,
        SYMBOL_TABLE,
        PACKAGE_TABLE,
        FUNCTION_TABLE,
        TOKEN_STREAM,
        ERROR_STREAM
    );

    Parser parser(
        TOKEN_STREAM,
        SYMBOL_TABLE
    );

    ICG::CodeGenerator code_gen(
        SYMBOL_TABLE,
        TOKEN_STREAM
    );

    // running compiler
    lexer.scan_code();
    parser.engine();
    code_gen.run();

    return 0;
}