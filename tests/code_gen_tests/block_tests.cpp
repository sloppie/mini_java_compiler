#include<iostream>
#include<vector>

#include "../../utilities/data_structures/node.h"
#include "../../utilities/data_structures/queue.h"
#include "../../utilities/data_structures/stack.h"
#include "../../code_gen/code_gen.h"

#include "line_tests.cpp"

std::vector<Node> line_tests();

Node block_tests() {
    Node block_code_tests(false, "block_code");
    block_code_tests.add_children(Node(true, "{"));
    
    for(Node line: line_tests()) {
        block_code_tests.add_children(line);
    }

    block_code_tests.add_children(Node(true, "}"));

    return block_code_tests;
}
