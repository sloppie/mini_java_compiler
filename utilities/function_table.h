#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H

#include<iostream>
#include<vector>

#include "../types.h"
#include "data_structures/queue.h"
#include "../lexer/lexer.h"
#include "../language_cfg/language_cfg.h"

using namespace std;

class FunctionTable {
    public:
        FunctionTable();
        void add_member(string, string, string, string, string);
        void add_param_details(string);
        void scan_function(string);
        string *find(string);
        params_queue find_param_details(string);

    private:
        vector<string *> FUNCTION_TABLE;
        vector<params_queue> CORRESSPONDING_PARAMS;
        string *undefined;
        params_queue undefined_param;
};

#endif