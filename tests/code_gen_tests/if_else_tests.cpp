#include<iostream>
#include<vector>

#include "../../utilities/data_structures/node.h"
#include "../../utilities/data_structures/queue.h"
#include "../../utilities/data_structures/stack.h"
#include "../../code_gen/code_gen.h"

#include "condition_tests.cpp"
#include "block_tests.cpp"

// function_prototypes
Node condition_tests();

std::vector<Node> if_else_tests() {
    std::vector<Node> example_ifs;

    Node if_else(false, "if_else");
    if_else.add_children(Node(true, "if"));
    if_else.add_children(condition_tests()); // adds condition defined in "condition_tests.cpp"
    if_else.add_children(block_tests());

    example_ifs.push_back(if_else);

    return example_ifs;
}