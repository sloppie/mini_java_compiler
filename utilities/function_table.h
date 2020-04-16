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
        // this method scans a function declared int the class and unpacks it to all the tokens
        // used in the function using the help of: FunctionTable::add_member FunctionTable::add_param_details
        Node scan_function(string, int&);
        // Adds the new function to the FUNCTION_TABLE vector
        // @param1 std:;string value (function_name)
        // @param2 function return type
        // @param3 function acccess method
        // @param4 function Node created by the FunctionTable::scan_function method, this is where the Tokens
        // found are added
        void add_member(string, string, string, string, Node*);
        // This adds the parameter details to the CORRESPONDING_PARAMS vector.
        // The index added to is the same index as the index of the FUNCTION_TABLE index of the corresponding
        // function.
        void add_param_details(string, Node*);
        // This finds the function details from the FUNCTION_TABLE vector and returns std::string array
        // of the function to the user 
        string *find(string);
        // This function returns the details givent the function name by first finding the function index of
        // that function in the FUNCTION_TABLE index.
        // This index found is then used to access the same index in the CORRESPONDING_PARAMS vector as it is
        // the index that contains the function parameter details.
        // @returns a queue of params in the order that they occur.
        // @see "../types.h" for more details on the params_queue type
        params_queue find_param_details(string);
        // Gets the function ID from the function table.
        // The function id is a combination of "f_id_" + index
        string get_function_id(string);
        // Creates a function template based on function details and a list of the params and the order in which
        // they occur
        string create_function_template(string);

    private: 
        // This ERROR_STREAM is passed back and forth in the comilation process to report errors in the 
        // correct line when they are detected.
        ErrorStream* ERROR_STREAM;
        // This contains the function details in a vector of std::string arrays which contains three indexes:
        // index 1: value (function_name).
        // index 2: function return_tyoe.
        // index 3: function access_modifier.
        vector<string *> FUNCTION_TABLE;
        // this contains a queue of function params. This is added to the same index as the function that
        // it corresponds to.
        vector<params_queue> CORRESSPONDING_PARAMS;
        // this is a default boilr plate used to send back to the calling function if the function being asked
        // for is not there.
        string *undefined;
        // this is the boiler plate for a function params if they are undefined.
        // This is in the case of them being NULL or the function not existing.
        params_queue undefined_param;
};

#endif