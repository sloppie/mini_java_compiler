#include<iostream>

#include "../language_cfg/language_cfg.h"
#include "../utilities/data_structures/queue.h"
#include "../utilities/data_structures/stack.h"

using namespace std;

int main() {
    bool assert_package(string, string);

    cout<< "running tests...\n"<< endl;

    string package_examples[] = {
        "package com.joocy.test;",
        "packagecom.joocy.com;",
        "package joocy;",
        "package ;",
        " com.joocy.com;",
        "package com.joocy",
        "package com.joo)cy;",
        "package com.joocy"
    };

    for(int i=0; i<8; i++) {
        cout<< "TEST "<< i + 1<< endl;

        if(assert_package(package_examples[i], "start")) {
            cout<< "correct -> "<< package_examples[i]<< endl;
        } else {
            cout<< "incorrect -> "<< package_examples[i]<< endl;
        }

        cout<< endl;

    }

    string import_examples[] = {
        "import com.joocy.test;",
        "packagecom.joocy.com;",
        "import joocy;",
        "import ;",
        " com.joocy.com;",
        "import com.joocy",
        "import com.joo)cy;",
        "import com.joocy"
    };

    for(int i=0; i<8; i++) {
        cout<< "TEST "<< i + 1<< endl;

        if(assert_package(import_examples[i], "import_declaration")) {
            cout<< "correct -> "<< import_examples[i]<< endl;
        } else {
            cout<< "incorrect -> "<< import_examples[i]<< endl;
        }

        cout<< endl;

    }

    return 0;
}


bool assert_package(string package_name, string key) {
    bool non_terminal_parser(string, const char*, int*);

    CFG mini_java;
    Queue<string*>* package_map =  mini_java.create_language_map(key);
    bool is_package_name = true;
    string NULL_STR[] = {" ", " ", " "};

    const char* pkg = package_name.c_str();
    int CURSOR = 0;
    bool opening_terminal_found = false;

    for(int i=0; i<package_map->size(); i++) {
        string* pkg_arr = package_map->dequeue(NULL_STR);

        if(pkg_arr[0].compare("s") != 0) {
            if(pkg_arr != NULL_STR) {
                // array = {terminal, terminal_type, plurality}
                if(pkg_arr[1].compare("terminal") == 0) {
                    string test_name = "";
                    bool found = false;                
                    while(pkg[CURSOR] != '\0') {
                        test_name += pkg[CURSOR];

                        if(!opening_terminal_found) {
                            if(test_name.compare(pkg_arr[0]) == 0 && pkg[CURSOR + 1] == ' ') {
                                CURSOR++;
                                found = true;
                                opening_terminal_found = true;
                                break;
                            }
                        } else {
                            if(test_name.compare(pkg_arr[0]) == 0) {
                                CURSOR++;
                                found = true;
                                break;
                            }
                        }

                        CURSOR++;
                    }

                    if(!found) {
                        cout<< pkg_arr[0]<<" not found on line 1"<< endl;
                        is_package_name = false;
                    }

                } else {
                    if(pkg_arr[0].compare("package_declaration") == 0) {
                        is_package_name = mini_java.is_package_name(pkg, &CURSOR);
                    }
                }

            } else {
                is_package_name = false;
                break;
            }
        } else {

            while(pkg[CURSOR] == ' ' || pkg[CURSOR] == '\n' || pkg[CURSOR] == '\t') {
                CURSOR++;
            }

        }
    }

    return is_package_name;
}


bool non_terminal_parser(string non_terminal, const char* package_name, int* CURSOR) {
    bool is_valid = true;

    while(package_name[*CURSOR] != '\0') {

        (*CURSOR)++;
    }

    return is_valid;
}