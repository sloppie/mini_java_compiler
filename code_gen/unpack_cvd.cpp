#include "code_gen.h"

std::string ICG::CodeGenerator::unpack_cvd(Node cvd) {
    std::string generated_code = "";

    Node new_line(false, "line"); // thi is the variable to store the restructure Node

    for(Node child: cvd.get_children()) {

        if(child.get_name().compare("access_modifier") != 0) {
            new_line.add_children(child);
        }

    }

    generated_code += unpack_line(new_line, false);

    return generated_code;
}