#ifndef POSTFIX_IT_H
#define POSTFIX_IT_H

#include "symbol_associativity.h"
#include "../lexer/token_stream.h"
#include "../utilities/symbol_table.h"
#include "../utilities/data_structures/node.h"
#include "../utilities/data_structures/queue.h"
#include "../utilities/data_structures/stack.h"

namespace ICG {

    inline Node postfix_it(Node line) {
        Stack<Node> equation_stack;
        Stack<symbol> operand_stack;

        for(Node child: line.get_children()) {
            symbol CURRENT_OP;

            if(child.is_terminal()) {

                if(child.get_name().compare("+") == 0) {
                    CURRENT_OP = OP::PLUS();
                } else if(child.get_name().compare("-") == 0) {
                    CURRENT_OP = OP::MINUS();
                } else if(child.get_name().compare("*") == 0) {
                    CURRENT_OP = OP::MULT();
                } else if(child.get_name().compare("/") == 0) {
                    CURRENT_OP = OP::DIV();
                }

                // if(operand_stack.get_stack().size() == 0) {
                //     operand_stack.push(CURRENT_OP);
                // } else {
                    Stack<symbol> popper;
                    symbol last_op;
                    last_op.PRIORITY = 0;

                    if(operand_stack.get_stack().size() > 0)
                        last_op = operand_stack.get_stack().at(operand_stack.get_stack().size() - 1);

                    if(CURRENT_OP.PRIORITY > last_op.PRIORITY) {
                        operand_stack.push(CURRENT_OP);
                    } else {

                        while(operand_stack.get_stack().size() != 0 && operand_stack.get_stack().at(operand_stack.get_stack().size() - 1).PRIORITY >= CURRENT_OP.PRIORITY) {
                            symbol popped = operand_stack.pop_val();

                            switch(popped.SYMBOL) {
                                case '+':
                                    equation_stack.push(Node(true, "+"));
                                    break;
                                case '*':
                                    equation_stack.push(Node(true, "*"));
                                    break;
                                case '-':
                                    equation_stack.push(Node(true, "-"));
                                    break;
                                case '/':
                                    equation_stack.push(Node(true, "/"));
                                    break;
                            }

                        }

                        operand_stack.push(CURRENT_OP);

                    }

                // }


            } else {
                equation_stack.push(child);
            }
        }

        while(operand_stack.get_stack().size() > 0) {

            switch(operand_stack.pop_val().SYMBOL) {
                case '+':
                    equation_stack.push(Node(true, "+"));
                    break;
                case '*':
                    equation_stack.push(Node(true, "*"));
                    break;
                case '-':
                    equation_stack.push(Node(true, "-"));
                    break;
                case '/':
                    equation_stack.push(Node(true, "/"));
                    break;
            }
            
        }

        Node postfix_equation(false, "line");

        for(int i=0; i<equation_stack.get_stack().size(); i++) {
            postfix_equation.add_children(equation_stack.get_stack().at(i));
        }

        return postfix_equation;
    }


}

#endif