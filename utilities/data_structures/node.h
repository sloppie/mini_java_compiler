#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>

using namespace std;

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