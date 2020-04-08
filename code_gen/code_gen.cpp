#include "code_gen.h" 
#include <string>

std::string ICG::CodeGenerator::get_term_id() {
    std::string term_id = "term_";
    term_id += to_string(TEST_ID);
    TEST_ID++;

    return term_id;
}