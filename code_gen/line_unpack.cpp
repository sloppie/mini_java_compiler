#include "code_gen.h"
#include "symbol_associativity.h"

void ICG::CodeGenerator::unpack_line(Node line) {
    Stack<char> ASSOC_STACK;    
    Node new_tree(false, "new_struct");

    for(Node children: line.get_children()) {
        symbol found_char;


        if(children.is_terminal()) {
            
            if(children.get_name().compare("+") == 0) {
                found_char = OP::PLUS();
            } else if(children.get_name().compare("-") == 0) {
                found_char = OP::MINUS();
            } else if(children.get_name().compare("*") == 0) {
                found_char = OP::MULT();
            } else if(children.get_name().compare("/") == 0) {
                found_char = OP::DIV();
            }

        }

    }

}