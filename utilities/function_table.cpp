#include "function_table.h"

FunctionTable::FunctionTable() {
    // default undefined function details
    undefined = new string[3];
    undefined[0] = "undefined";
    undefined[1] = "undefined";
    undefined[2] = "undefined";

    // default undefined function param details
    string* up = new string[3];
    up[0] = "undefined";
    up[1] = "undefined";
    up[2] = "undefined";
    undefined_param.enqueue(up);
}

void FunctionTable::add_member(string value, string return_type, string context, string parameter_block, string block_code) {
    string* new_member = new string[3];
    new_member[0] = value;
    new_member[1] = return_type;
    new_member[2] = context;

    cout<< "Function added: "<< endl;
    cout<< "    Name: "<< value<< endl;
    cout<< "    Return Type: "<< return_type<< endl;
    cout<< "    Context: "<< context<< endl;
    FUNCTION_TABLE.push_back(new_member);
    add_param_details(parameter_block);
}

void FunctionTable::add_param_details(string parameter_block) {
    cout<< "Parsing param block: "<< parameter_block<< endl;
    const char* pb = parameter_block.c_str();
    int CURSOR = 1;
    bool params_found = true;
    params_queue new_param;
    string function_name = FUNCTION_TABLE.at(FUNCTION_TABLE.size() - 1)[0];

    while(pb[CURSOR] == ' ') {
        CURSOR++;
    }

    while(pb[CURSOR] != '\0') {
        string parameter_type = "";
        bool type_found = false;
        string parameter_name = "";
        bool name_found = false;

        while(pb[CURSOR] == ' ') {
            CURSOR++;
        }

        while(pb[CURSOR] != ',' && pb[CURSOR] != ')') {

            if(pb[CURSOR] == ' ') {

                if(type_found && name_found) {

                    if(pb[CURSOR + 1] != '\0') {
                        CURSOR++;
                        break;
                    } else {
                        break;
                    }

                } else if(!type_found) {
                    type_found = true;
                } else if(!name_found) {
                    name_found = true;
                }

            } else {

                if(!type_found) {
                    parameter_type += pb[CURSOR];
                } else {
                    parameter_name += pb[CURSOR];
                }

            }

            CURSOR++;
        }

        if(type_found && (parameter_name.compare("") != 0)) {
            string* param_added = new string[3];
            param_added[0] = parameter_type;
            param_added[1] = parameter_name;
            param_added[2] = function_name;

            new_param.enqueue(param_added);
        } else if(type_found){
            params_found = false;
            cout<< "Invalid Paramter definition for function: \""<< function_name<< "\""<< "\n    EXPECTED a name after type: \""<< parameter_type<< "\""<< endl;
        } else {
            params_found = false;
            // cout<< "Invalid Paramter definition for function: \""<< function_name<< "\""<< "\n    EXPECTED a name after type: \""<< parameter_type<< "\""<< endl;
        }

        CURSOR++;
    }

    if(params_found) {
        CORRESSPONDING_PARAMS.push_back(new_param);
    } else {
        CORRESSPONDING_PARAMS.push_back(undefined_param);
    }
}


string* FunctionTable::find(string key) {
    string* answer = undefined;

    for(int i=0; i<FUNCTION_TABLE.size(); i++) {
        if(FUNCTION_TABLE.at(i)[0].compare(key) == 0) {
            answer = FUNCTION_TABLE.at(i);
            break;
        }
    }

    return answer;
}


params_queue FunctionTable::find_param_details(string key) {
    int index = -1;
    bool found = false;

    for(int i=0; i<FUNCTION_TABLE.size(); i++) {
        index++;
        if(FUNCTION_TABLE.at(i)[0].compare(key) == 0) {
            found = true;
            break;
        }
    }

    params_queue answer = (found)? CORRESSPONDING_PARAMS.at(index): undefined_param;

    return answer;
}


void FunctionTable::scan_function(string source_code) {
    string access_modifier = "";
    bool am_found = false;
    string return_type = "";
    bool rt_found = false;
    string function_name = "";
    bool fn_found = false;
    int CURSOR = 0;
    string parameter_code = Lexer::find_bracketed_code(source_code, '(', CURSOR);
    string block_code = Lexer::find_bracketed_code(source_code, '{', CURSOR);

    CURSOR = 0;
    const char* sc = source_code.c_str();

    //access modifier
    while(sc[CURSOR] != ' ') {
        access_modifier += sc[CURSOR];
        CURSOR++;
    }

    if(access_modifier.compare("public") == 0 || access_modifier.compare("private") == 0|| access_modifier.compare("protected") == 0) {
        am_found = true;
    } else {
        cout<< "INVALID access modifier \""<< access_modifier<< "\""<< endl;
    }

    cout<< access_modifier<< endl;

    while(sc[CURSOR] == ' ') {
        CURSOR++;
    }

    // return type
    while(sc[CURSOR] != ' ') {
        return_type += sc[CURSOR];
        CURSOR++;
    }

    rt_found = true;

    while(sc[CURSOR] == ' ') {
        CURSOR++;
    }

    // function name
    while(sc[CURSOR] != ' ' && sc[CURSOR] != '(') {
        function_name += sc[CURSOR];
        CURSOR++;
    }

    if(function_name.compare("") != 0) {
        if(CFG().is_word(function_name.c_str())) {
            fn_found = true;
        }
    }

    if(sc[CURSOR] == ' ') {
        while(sc[CURSOR] == ' ') {
            CURSOR++;
        }
    }

    if(am_found && rt_found && fn_found) {
        add_member(function_name, return_type, access_modifier, parameter_code, block_code);
    } else {
        if(!am_found) {
            cout<< "invalid access modifier for the function: \""<< function_name<< endl;
        } else {
            cout<< "Invalid return type or function name in function: \""<< function_name<< "\""<< endl;
        }
    }

}