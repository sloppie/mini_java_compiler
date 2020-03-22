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
        
    private:
        map<string, string> MINI_JAVA;
        void create_language_map(string key="start");

};

#endif