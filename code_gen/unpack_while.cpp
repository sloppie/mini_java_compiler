#include "code_gen.h"

#include<string>

std::string ICG::CodeGenerator::unpack_while(Node while_body) {
    std::string generated_code = "";
    std::string indent = "";
    
    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    // the assumption taken here is that by rule, the second index of the Node::children of the
    // while Node is the conditon Node, hence it can just be accessed using the index 1
    generated_code += unpack_condition(while_body.get_children().at(1));

    for(Node child : while_body.get_children()) {
        
        if(child.is_terminal()) {

            if(child.get_name().compare("while") == 0) {
                generated_code += indent;
                generated_code += "while(";
            } else {
                generated_code += child.get_name();
            }

        } else {

            if(child.get_name().compare("condition") == 0) {
                std::string t_id = "term_";
                t_id += to_string(TEST_ID - 1);
                generated_code += t_id;
                generated_code += ") ";
            } else {
                INDENT++;
                generated_code += unpack_conditional_block(child);
                INDENT--;
            }

        }

    }

    return generated_code;
}