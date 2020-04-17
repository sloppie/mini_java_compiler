#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>

using namespace std;

// This data structure is the basic mode of communication between all the parts of the compiler.
// When the lexer identifies a valid token, it creates a Node which contains information such:
// @param1 whether it is a terminal or not (bool)
// @param2 name of the node, this names are based on the names given in the CFG class
// if the Node is supposed to be the end of the parsing of the tree, the Node is given a value:
// @param3 (second constructor overload) hold the value of the Node.
// in most cases the Node is a Non-terminal unless it's a comparator Node which is a terminal Node,
// but requires all three parameters filled. (this is because these terinals are four different ones). 
class Node {

    public:
        Node(
            bool terminal, 
            string node_name
        ): terminal(terminal),
           node_name(node_name) {}

        Node(
            bool terminal, 
            string node_name,
            string value
        ): terminal(terminal),
           node_name(node_name),
           value(value) {}

        //adds children nodes if the Node is NOT a terminal
        void add_children(Node child) {

            if(!terminal)
                children.push_back(child);

        }

        // gets the node name
        string get_name() {
            return node_name;
        }

        bool is_terminal() {
            return terminal;
        }

        vector<Node> get_children() {
            return children;
        }

        string get_value() {
            return value;
        }

    private:
        bool terminal = false;
        string node_name;
        string value = "";

        vector<Node> children;

};

#endif