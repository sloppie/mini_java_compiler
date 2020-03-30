#include<iostream>

#include "../types.h"
#include "../lexer/lexer.h"
#include "../utilities/function_table.h"
#include "../utilities/package_table.h"
#include "../utilities/symbol_table.h"

using namespace std;


int function_tests(PackageTable* PACKAGE_TABLE, FunctionTable* FUNCTION_TABLE, SymbolTable* SYMBOL_TABLE) {
    string sample_function = "public int main (int kwargs, int legs) {\n    int i = 0;\n}";
    Lexer lexical_analyser(sample_function, SYMBOL_TABLE, PACKAGE_TABLE, FUNCTION_TABLE);
    int CURSOR = 0;

    string paramter_code = Lexer::find_bracketed_code(sample_function, '(', CURSOR);
    string block_code = Lexer::find_bracketed_code(sample_function, '{', CURSOR);

    CURSOR = 0;
    FUNCTION_TABLE->scan_function(sample_function, CURSOR);

    params_queue function_param = FUNCTION_TABLE->find_param_details("main");

    cout<< "The function main, has the following params: "<< endl;
    
    for(int i=0; i<function_param.get_init_queue().size(); i++) {
        string* param = function_param.get_init_queue().at(i);
        cout<< "Param"<< i+ 1<< endl;
        cout<< "    Type: "<< param[1] << endl;
        cout<< "    Arg Name: "<< param[0] << endl;
        cout<< "    Context: "<< param[2] << endl;
    }

    return 0;
}