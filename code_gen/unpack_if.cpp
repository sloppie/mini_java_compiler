#include "code_gen.h"

std::string ICG::CodeGenerator::unpack_if(Node if_else) {
    std::string generated_code = "";
    std::string indent = "";
    Queue<std::string> condition_result_queue;

    for(int i=0; i<INDENT; i++) {

        for(int x=0; x<4; x++) {
            indent += ' ';
        }

    }

    // to accound for the three step process of unpacking conditions
    // all conditions are prior unpacked and their results held in a Queue<string>
    // which will be used to supply all the answers to the equivalent condition in th stack
    // instead of having complications unpacking on the fly which will ruin the aesthetics
    // of the if-else Node representation
    for(Node child: if_else.get_children()) {
        
        if(child.get_name().compare("condition") == 0) {
            generated_code += unpack_condition(child);
            // the last term id is the result of the condition
            std::string term_id = "term_";
            term_id += to_string(TEST_ID);
            condition_result_queue.enqueue(term_id);
        }
    }

    bool opening_terminal = false;

    for(Node child: if_else.get_children()) {
        
        if(child.is_terminal()) {
            
            if(child.get_name().compare("if") == 0) {
                if(!opening_terminal) {
                    generated_code += indent;
                    generated_code += "if";
                } else {
                    generated_code += " if";
                }
            } else if(child.get_name().compare("else") == 0) {
                generated_code += " else";
            } else {
                generated_code += child.get_name();
            }

        } else {

            if(child.get_name().compare("condition") == 0) {
                // the logic is theat it can only dequeue as much as it queued
                // hence there is no overwhelming need for queue size check :)
                generated_code += condition_result_queue.dequeue("#");
            } else if(child.get_name().compare("block_code") == 0) {
                INDENT++;
                // unpack_bloc goes here
                generated_code += unpack_conditional_block(child);
                INDENT--;
            }

        }
    }

}