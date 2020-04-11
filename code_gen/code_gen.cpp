#include "code_gen.h" 
#include <string>

void ICG::CodeGenerator::run() {
    unpack_class(); // unacks all the code

    std::string generated_code = intermediate_code;
    generated_code += function_code;

    cout<< generated_code<< endl;
}

std::string ICG::CodeGenerator::get_term_id() {
    std::string term_id = "term_";
    term_id += to_string(TEST_ID);
    TEST_ID++;

    return term_id;
}


std::string ICG::CodeGenerator::get_func_id() {
    std::string term_id = "func_";
    term_id += to_string(FUNC_ID);
    FUNC_ID++;

    return term_id;
}