#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>

using namespace std;

class Node {

    public:
        Node( // initialisation
            bool is_terminal, 
            string node_name
        ): is_terminal(is_terminal),
           node_name(node_name) {}

        Node( // initialisation
            bool is_terminal, 
            string node_name,
            string value
        ): is_terminal(is_terminal),
           node_name(node_name),
           value(value) {}

        //adds children nodes if the Node is NOT a terminal
        void add_children(Node child) {

            if(!is_terminal)
                children.push_back(child);

        }

    private:
        bool is_terminal = false;
        string node_name;
        string value;

        vector<Node> children;

};

#endif