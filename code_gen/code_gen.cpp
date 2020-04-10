#include "code_gen.h" 
#include <string>

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