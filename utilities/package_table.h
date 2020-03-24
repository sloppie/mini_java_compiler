#ifndef PACKAGE_TABLE_H
#define PACKAGE_TABLE_H

#include<iostream>
#include<vector>

using namespace std;

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