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

        private:
            TokenStream* TOKEN_STREAM;
            SymbolTable* SYMBOL_TABLE;
    };

} // ICG


#endif