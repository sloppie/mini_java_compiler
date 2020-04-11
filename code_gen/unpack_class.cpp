#include "code_gen.h"

void ICG::CodeGenerator::unpack_class() {
    TOKEN_STREAM->reset_position(); // resets the position since the Parser had already set the poition to the last Node in the TokenStream
    Node current_node = TOKEN_STREAM->next_token();

    // unpack from the token stream until we find the class definition
    // This is necessary as we cannot predict the amount of import statements the user will declare.
    while(current_node.get_name().compare("class_declaration") != 0) {
        current_node = TOKEN_STREAM->next_token();
    }

    // The assumption is that the current node is obviously class_declaration
    for(Node child: current_node.get_children()) {

        if(!child.is_terminal()) {

            if(child.get_name().compare("function_declaration") == 0) {
                intermediate_code += unpack_function(child);
            } else if(child.get_name().compare("class_varaible_declaration") == 0) {
                intermediate_code += unpack_cvd(child);
            }

        }

    }
}