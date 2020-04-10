#ifndef CODE_GEN_H
#define CODE_GEN_H

#include<iostream>

#include "../lexer/token_stream.h"
#include "../utilities/symbol_table.h"
#include "../utilities/data_structures/node.h"
#include "../utilities/data_structures/queue.h"
#include "../utilities/data_structures/stack.h"

namespace ICG {

    class CodeGenerator {
        public:
            CodeGenerator(
                SymbolTable* SYMBOL_TABLE,
                TokenStream* TOKEN_STREAM
            ): SYMBOL_TABLE(SYMBOL_TABLE),
                TOKEN_STREAM(TOKEN_STREAM) {}
            // unpacks a line into its equivalent three step process code.
            // since the function is multipurpose,
            // it is used by CodeGenerator::unpack_block and CodeGenerator::unpack_conditional_block.
            // As such, the boolean passed in as the second parameter is used to distinguish between
            // which parent function is calling them.
            std::string unpack_line(Node, bool);
            // unpacks an equation that has an assignment operator
            std::string unpack_equation(Node, std::string, bool);
            // unpacks an arithmetic equation without an assignment operator
            std::string unpack_equation(Node, bool);
            //unpacks the condition Node passed to it
            std::string unpack_condition(Node);
            // unpacks a chained condition (i.e this condition has a connector inside it)
            std::string unpack_chained_condition(Node);
            // unpacks a basic condition (i.e this condition does not have a connector in it)
            std::string unpack_single_condition(Node);
            // unpacks a basic condition (i.e this condition does not have a connector in it)
            // this is used to help the chained_condition method unpack.
            //  this method takes in a term_id as its second parameter to avoid term 
            //  confusion as it assigns the condition terms to the next term which will
            // most likely be from the last condition
            std::string unpack_single_condition(Node, std::string);
            // this is used to unpaack the if_condition passed to it as a node
            // with the assistance of ICG::CodeGenerator::INDENT it helps know the amount of
            // tabs to indent by
            std::string unpack_if(Node);
            // this is used to handle the back and forth between unpack_line, unpack_if and unpack_while.
            // This function also keeps tab of indentation so as to make sure everything is readable
            // for the user in terms of block scope and what-not. 
            std::string unpack_block(Node);
            // this is used to handle the back and forth between unpack_line, unpack_if and unpack_while.
            // This function also keeps tab of indentation so as to make sure everything is readable
            // for the user in terms of block scope and what-not. 
            std::string unpack_conditional_block(Node);
            // The pack below is used to simplify the while-loop into a simple conditional that will be
            // easier to translate to the equivalent assembly language code
            std::string unpack_while(Node);

        private:
            int TEST_ID = 0;
            int INDENT = 0;
            int FUNC_ID = 0;
            std::string intermediate_code = "";
            std::string function_code = "";
            
            TokenStream* TOKEN_STREAM;
            SymbolTable* SYMBOL_TABLE;
            SymbolTable NEW_VAR_LOOKUP;
            std::string get_term_id();

            // indentation for block labels
            std::string label_indent = "    ";

            // gets an id for an anonymous function created to hous the block code
            std::string get_func_id();

    };

} // ICG


#endif