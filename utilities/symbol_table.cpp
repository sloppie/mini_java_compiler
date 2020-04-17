#include "./symbol_table.h"

SymbolTable::SymbolTable() {
    UNDEFINED = new string[3];

    UNDEFINED[0] = "undefined";
    UNDEFINED[1] = "undefined";
    UNDEFINED[2] = "undefined";
}


void SymbolTable::add_member(string value, string type, string context) {
    string* new_member = new string[3];
    new_member[0] = value;
    new_member[1] = type;
    new_member[2] = context;

    SYMBOL_TABLE.push_back(new_member);
}

string* SymbolTable::find(string key) {
    string* answer = UNDEFINED;

    for(string* token: SYMBOL_TABLE) {

        if(token[0].compare(key) == 0) {
            answer = token;
            break;
        }

    }

    return answer;
}


int SymbolTable::get_index(string key) {
    int index = -1;

    for(int i=0; i<SYMBOL_TABLE.size(); i++) {

        if(SYMBOL_TABLE.at(i)[0].compare(key) == 0) {
            index = i;
            break;
        }

    }

    return index;
}