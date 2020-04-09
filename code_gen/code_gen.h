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
            ) {}
            // unpacks a line into its equivalent three step process code
            void unpack_line(Node);
            // unpacks an equation that has an assignment operator
            std::string unpack_equation(Node, std::string);
            // unpacks an arithmetic equation without an assignment operator
            std::string unpack_equation(Node);
            //unpacks the condition Node passed to it
            void unpack_condition(Node);
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

        private:
            std::string intermediate_code = "";
            int TEST_ID = 0;
            TokenStream* TOKEN_STREAM;
            SymbolTable* SYMBOL_TABLE;
            SymbolTable NEW_VAR_LOOKUP;

            std::string get_term_id();

    };

} // ICG


#endif