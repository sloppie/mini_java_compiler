#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H

#include<iostream>
#include<vector>

#include "../types.h"
#include "data_structures/queue.h"
#include "data_structures/node.h"
#include "../language_cfg/language_cfg.h"
#include "../lexer/error_stream.h"

using namespace std;

class FunctionTable {
    public:
        FunctionTable(ErrorStream*);
        Node scan_function(string, int&);
        void add_member(string, string, string, string, Node*);
        void add_param_details(string, Node*);
        string *find(string);
        params_queue find_param_details(string);
        string get_function_id(string);
        string create_function_template(string);

    private: 
        ErrorStream* ERROR_STREAM;
        vector<string *> FUNCTION_TABLE;
        vector<params_queue> CORRESSPONDING_PARAMS;
        string *undefined;
        params_queue undefined_param;
};

#endif