#include<iostream>
#include<vector>

#include "../../utilities/data_structures/node.h"
#include "../../utilities/data_structures/queue.h"
#include "../../utilities/data_structures/stack.h"
#include "../../code_gen/code_gen.h"

// returns examples made to test line unpack done by the ICG::CodeGenerator::unpack_line method
std::vector<Node> line_tests() {
    std::vector<Node> example_lines;

    // basic initialisation for a line with type definition and equation definition
    Node line_1(false, "line");
    line_1.add_children(Node(false, "type_defined", "int"));
    line_1.add_children(Node(false, "property_name", "blinding"));
    line_1.add_children(Node(true, "="));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, "+"));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, "*"));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, "/"));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, "-"));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, "*"));
    line_1.add_children(Node(false, "number", "int34"));
    line_1.add_children(Node(true, ";"));

    // a basic reassignment where the variable is assigned back to itself
    Node line_2(false, "line");
    line_2.add_children(Node(false, "property_name", "blinding"));
    line_2.add_children(Node(true, "="));
    line_2.add_children(Node(false, "number", "int3564"));
    line_2.add_children(Node(true, "+"));
    line_2.add_children(Node(false, "property_name", "blinding"));
    line_2.add_children(Node(true, "-"));
    line_2.add_children(Node(false, "number", "int3324"));
    line_2.add_children(Node(true, "/"));
    line_2.add_children(Node(false, "number", "int3454"));
    line_2.add_children(Node(true, "-"));
    line_2.add_children(Node(false, "number", "int344"));
    line_2.add_children(Node(true, "*"));
    line_2.add_children(Node(false, "number", "int304"));
    line_2.add_children(Node(true, ";"));

    Node line_3(false, "line");
    line_3.add_children(Node(false, "type_defined", "float"));
    line_3.add_children(Node(false, "property_name", "newFloat"));
    line_3.add_children(Node(true, ";"));

    // basic math equation with no assignment of variables
    Node line_4(false, "line");
    line_4.add_children(Node(false, "number", "int3564"));
    line_4.add_children(Node(true, "+"));
    line_4.add_children(Node(false, "property_name", "blinding"));
    line_4.add_children(Node(true, "-"));
    line_4.add_children(Node(false, "number", "int3324"));
    line_4.add_children(Node(true, "/"));
    line_4.add_children(Node(false, "number", "int3454"));
    line_4.add_children(Node(true, "-"));
    line_4.add_children(Node(false, "number", "int344"));
    line_4.add_children(Node(true, "*"));
    line_4.add_children(Node(false, "number", "int304"));
    line_4.add_children(Node(true, ";"));

    // adding a new variable to the list
    Node line_5(false, "line");
    line_5.add_children(Node(false, "type_specified", "int"));
    line_5.add_children(Node(false, "property_name", "myVar"));
    line_5.add_children(Node(true, "="));
    line_5.add_children(Node(false, "number", "int2"));
    line_5.add_children(Node(true, "*"));
    line_5.add_children(Node(false, "number", "int2"));
    line_5.add_children(Node(true, "/"));
    line_5.add_children(Node(false, "number", "int2"));
    line_5.add_children(Node(true, "-"));
    line_5.add_children(Node(false, "number", "int2"));
    line_5.add_children(Node(true, "+"));
    line_5.add_children(Node(false, "number", "int8762"));
    line_4.add_children(Node(true, ";"));

    example_lines.push_back(line_1);
    example_lines.push_back(line_2);
    example_lines.push_back(line_3);
    example_lines.push_back(line_4);

    return example_lines;
}
