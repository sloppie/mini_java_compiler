#include "code_gen.h"

std::string ICG::CodeGenerator::unpack_parameters(Node parameter_definition) {
    std::string generated_code = "";

    for(Node child: parameter_definition.get_children()) {
        
        if(child.is_terminal()) {
        // !TODO: restructure the adding of the last terminal to be handed back to parameter_definition Node
            if(child.get_name().compare(",") == 0) {
                generated_code += ", ";
            } else if(child.get_name().compare(")")) {
                generated_code += ") ";
            } else {
                generated_code += child.get_name();
            }

        } else {
            // since the only child being expected is the parameter Node.
            // This is the structure of the parameter Node:
            // parameter:
            //     > type_defined (has a value)
            //     > word (has a value)
            // hence we can just directly access the node value be getting the second child of each node
            std::string param_id = get_term_id();
            NEW_VAR_LOOKUP.add_member(
                child.get_children().at(1).get_value(), // get the value of the word Node, whic has the parameter name
                "parameter", // figure ot a way to handle this
                param_id
            );
            generated_code += param_id;
        }

    }

    return generated_code;
}