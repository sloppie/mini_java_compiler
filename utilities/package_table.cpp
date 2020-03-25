#include "package_table.h"

PackageTable::PackageTable() {
    UNDEFINED = new string[3];

    UNDEFINED[0] = "undefined";
    UNDEFINED[1] = "undefined";
    UNDEFINED[2] = "undefined";
}

void PackageTable::add_member(string value, string type, string context) {
    string* new_member = new string[3];
    new_member[0] = value;
    new_member[1] = type;
    new_member[2] = context;

    PACKAGE_TABLE.push_back(new_member);
}

string* PackageTable::find(string key) {
    string* answer = UNDEFINED;
    bool found = true;

    for(string* value: PACKAGE_TABLE) {
        if(value[0].compare(key) == 0) {
            found = true;
            answer = value;
            break;
        }
    }

    return answer;
}


int PackageTable::get_index(string key) {
    int index = -1;

    for(int i=0; i<PACKAGE_TABLE.size(); i++) {

        if(PACKAGE_TABLE.at(i)[0].compare(key) == 0) {
            index = i;
            break;
        }

    }

    return index;
}