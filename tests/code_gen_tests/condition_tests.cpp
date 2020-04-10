#include<iostream>
#include<vector>

#include "../../utilities/data_structures/node.h"
#include "../../utilities/data_structures/queue.h"
#include "../../utilities/data_structures/stack.h"
#include "../../code_gen/code_gen.h"

Node condition_tests() {
    Node CONDITION(false, "condition");
    CONDITION.add_children(Node(true, "("));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "comparator", ">="));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "connector", "&&"));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "comparator", "<="));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "connector", "||"));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "comparator", "<="));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "connector", "&&"));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "comparator", "<="));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "connector", "||"));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(false, "comparator", "<="));
    CONDITION.add_children(Node(false, "condition_parameter", "myVar"));
    CONDITION.add_children(Node(true, ")"));

    return CONDITION;
}