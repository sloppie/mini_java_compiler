#ifndef LANG_CFG
#define LANG_CFG

#include<iostream>
#include<vector>
#include<map>

#include "../utilities/data_structures/queue.h"
#include "../utilities/data_structures/stack.h"

using namespace std;


// global


class CFG {
    public:
        CFG();
        string fetch_cfg(string key);
        Queue<string*>* create_language_map(string key="start");

        bool is_package_name(const char*, int*);

        bool is_word(const char*);
        bool is_int(const char*);
        bool is_decimal(const char*);
        // bool is_anything(const char*, int*, string);
        
    private:
        map<string, string> MINI_JAVA;

};

#endif