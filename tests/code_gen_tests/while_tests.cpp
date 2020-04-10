#include<iostream>
#include<vector>

#include "../../utilities/data_structures/node.h"
#include "../../utilities/data_structures/queue.h"
#include "../../utilities/data_structures/stack.h"
#include "../../code_gen/code_gen.h"

#include "condition_tests.cpp"
#include "block_tests.cpp"


Node while_tests() {
    Node while_body(false, "while");
    while_body.add_children(Node(true, "while"));
    while_body.add_children(condition_tests());
    while_body.add_children(block_tests());

    return while_body;
}