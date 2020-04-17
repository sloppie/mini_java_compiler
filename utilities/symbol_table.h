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
        // adds a new member to the symbol table in at the last position
        // @param1 is a string holding the variable name
        // @param2 is a string holding the variable type to help in enforcing type checking
        // @param3 is a string holding the function context, this variable however fgoes majorly
        // unused since we do not employ variable scoping in this project.
        void add_member(string, string, string);
        // This method finds the variable with the string name defined in @param1
        // the returened variable is a std::string array with the following structure:
        // @index1 variable_name
        // @index2 variable_type
        // @index# variable scope
        // if the variable is not defined, it returns SymbolTable::UNDEFINED
        string* find(string value); 
        // gets the index of a defined variable in the symmbl table.
        // if the variable is not defined, it returns index -1.
        int get_index(string key);

    private:
        // The vector storing vvariable details
        vector<string*> SYMBOL_TABLE;
        // Default return in the event a variable is not found
        string* UNDEFINED;
};

#endif