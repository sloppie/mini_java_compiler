#ifndef SYMBOL_ASSOC_H
#define SYMBOL_ASSOC_H

#include<iostream>

#define LEFT_ASSOC "LEFT ASSOC"
#define RIGHT_ASSOC "RIGHT ASSOC"

typedef struct {
    char SYMBOL;
    std::string ASSOC;
    int PRIORITY;
} symbol;

class OP {

    public:
        static symbol PLUS() {
            symbol new_op;
            new_op.SYMBOL = '+';
            new_op.ASSOC = RIGHT_ASSOC;
            new_op.PRIORITY = 1;

            return new_op;
        }

        static symbol MINUS() {
            symbol new_op;
            new_op.SYMBOL = '-';
            new_op.ASSOC = RIGHT_ASSOC;
            new_op.PRIORITY = 1;

            return new_op;
        }

        static symbol MULT() {
            symbol new_op;
            new_op.SYMBOL = '*';
            new_op.ASSOC = RIGHT_ASSOC;
            new_op.PRIORITY = 3;

            return new_op;
        }

        static symbol DIV() {
            symbol new_op;
            new_op.SYMBOL = '/';
            new_op.ASSOC = RIGHT_ASSOC;
            new_op.PRIORITY = 3;

            return new_op;
        }
}; // OP namespace

#endif