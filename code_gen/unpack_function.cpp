#include "code_gen.h"

std::string ICG::CodeGenerator::unpack_function(Node function_declaration) {
    std::string generated_code = "";

    // iterate through the whole Node's children
    for(Node child: function_declaration.get_children()) {
        
        if(child.is_terminal()) {
            generated_code += child.get_name();
        } else {

            if(child.get_name().compare("parameter_definition") == 0) {
                generated_code += unpack_parameters(child);
            } else if(child.get_name().compare("block_code") == 0) {
                INDENT++;
                generated_code += unpack_block(child);
                INDENT--;
            } else if(child.get_name().compare("property_name") == 0) {
                generated_code += child.get_value();
            }

        }
            
    }

    return generated_code;
}