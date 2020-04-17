#ifndef PACKAGE_TABLE_H
#define PACKAGE_TABLE_H

#include<iostream>
#include<vector>

using namespace std;

// This class is extremely similar to the SymbolTable class
// refer to the comments made on the @SymbolTable class for more information on
// how they work
class PackageTable {
    public:
        PackageTable();
        void add_member(string, string, string);
        string* find(string);
        int get_index(string);

    private:
        vector<string*> PACKAGE_TABLE;
        string* UNDEFINED;
};

#endif