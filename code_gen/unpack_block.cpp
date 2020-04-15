#include "code_gen.h"

std::string ICG::CodeGenerator::unpack_block(Node block) {
    std::string generate_code = "";
    std::string closing_indent = "";

    for(int i=0; i<(INDENT - 1); i++) {

        for(int x=0; x<4; x++) {
            closing_indent += " ";
        }

    }

    for(Node child: block.get_children()) {

        if(child.is_terminal()) {

            if(child.get_name().compare("{") == 0) {
                generate_code += "{\n";
            } else {
                generate_code += closing_indent;
                generate_code += "}\n";
            }

        } else {

            if(child.get_name().compare("if_else") == 0) {
                generate_code += unpack_if(child);
            } else if(child.get_name().compare("while") == 0) {
                // unpack block goes here
                generate_code += unpack_while(child);
            } else {
                // create a new anonymous function to house the block code
                generate_code += unpack_line(child, false);
            }

        }

    }

    return generate_code;
}


std::string ICG::CodeGenerator::unpack_conditional_block(Node block) {
    std::string generate_code = "";
    std::string closing_indent = "";
    std::string func_name = get_func_id();

    for(int i=0; i<(INDENT - 1); i++) {

        for(int x=0; x<4; x++) {
            closing_indent += " ";
        }

    }

    function_code += func_name;
    function_code += ":\n";

    for(Node child: block.get_children()) {

        if(child.is_terminal()) {

            if(child.get_name().compare("{") == 0) {
                generate_code += "{\n";
            }

        } else {

            if(child.get_name().compare("if_else") == 0) {
                generate_code += unpack_if(child);
            } else if(child.get_name().compare("while") == 0) {
                // unpack block goes here
                generate_code += unpack_while(child);
            } else {
                // create a new anonymous function to house the block code                
                function_code += unpack_line(child, true);
            }

        }

    }

    function_code += "\n";

    generate_code += closing_indent;
    generate_code += "    goto: ";
    generate_code += func_name;
    generate_code += "\n";
    generate_code += closing_indent;
    generate_code += "}";

    return generate_code;
}