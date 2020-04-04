#include "parser.h"


void Parser::engine() {
    
}


vector<Queue<term>> Parser::unpack_cfg_node(string NON_TERMINAL) {
    const char* CFG_TERM = LANGUAGE_CFG.fetch_cfg(NON_TERMINAL).c_str();
    vector<Queue<term>> unpacked;
    Queue<term> expanse; // used to store expanded store. Then is pushed to unpacked
    int CURSOR = 0;
    string term_found = "";
    Stack<char> percent_stack;

    while(CFG_TERM[CURSOR] != '\0') {
        
        if(CFG_TERM[CURSOR] == '%') {
            
            if(percent_stack.get_stack().size() == 0) {
                
                if(term_found.compare("") != 0) {
                    term new_term;
                    new_term.name = term_found;
                    new_term.is_terminal = true;
                    term_found = "";
                    expanse.enqueue(new_term);
                }

                percent_stack.push('%');
            } else {
                term new_term;
                new_term.name = term_found;
                new_term.is_terminal = false;
                term_found = "";

                if(CFG_TERM[CURSOR + 1] == '*' && CFG_TERM[CURSOR + 1] == '+') {
                    
                    if(CFG_TERM[CURSOR + 1] == '*') {
                        new_term.closure = CLOSURE;
                    } else {
                        new_term.closure = POSITIVE_CLOSURE;
                    }

                    CURSOR++;
                } else {
                    new_term.closure = NO_CLOSURE;
                }

                expanse.enqueue(new_term);
            }

        } else if(CFG_TERM[CURSOR] == '|') {
            unpacked.push_back(expanse);
            expanse = Queue<term>();
        } else{
            term_found += CFG_TERM[CURSOR];
        }

        CURSOR++;
    }

    unpacked.push_back(expanse); // adds the last Queue that was being worked on

    return unpacked;
}


void Parser::visit_tree(Node tree_node) {

    LEVEL += 4;
    string whitespace = "";

    for(int i=LEVEL; i>0; i--) {
        whitespace += ' ';
    }

    if(tree_node.is_terminal()) {
        // cout<< whitespace<< tree_node.get_name()<< endl;
        cout<< whitespace<< "\033[1;30;42m"<< tree_node.get_name()<< "\033[0m"<< endl;
    } else {
        if(tree_node.get_value().compare("") != 0) {
            cout<< whitespace<< "\033[1;41m"<< tree_node.get_name()<< "\033[0m: \033[1;30;42m"<< tree_node.get_value()<< "\033[0m"<< endl;
        } else {
            cout<< whitespace<< "\033[1;30;46m"<< tree_node.get_name()<< "\033[0m"<< endl;

            for(Node child: tree_node.get_children()) {
                visit_tree(child);
            }
        }

    }
    LEVEL -= 4;

}