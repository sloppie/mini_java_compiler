#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<vector>
#include<iostream>

using namespace std;

/**
 * STRUCTURE OF THE SYMBOL_TABLE
 *  ________________________________
 * | VALUE | TYPE | SCOPE (CONTEXT) |
 * |________________________________| 
 * 
 */
class SymbolTable {
    public:
        SymbolTable();
        void add_member(string, string, string);
        string* find(string value); 
        int get_index(string key);

    private:
        vector<string*> SYMBOL_TABLE;
        string* UNDEFINED;
};

#endif