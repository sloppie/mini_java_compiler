#include "language_cfg.h"

string anything_string = "~a~b~c~d~e~f~g~h~i~j~k~l~m~n~o~p~q~r~s~t~u~v~w~x~y~z~A~B~C~D~E~F~G~H~I~J~K~L~M~N~O~P~Q~R~S~T~U~V~W~X~Y~Z~1~2~3~4~5~6~7~8~9~0~-~=~+~-~(~)~&~^~%~$~#~@~1";

// we try to define the language cfg in the constructor
CFG::CFG() {
    MINI_JAVA.insert(pair<string, string>("start", "package%s%+%package_declaration%;%s%+%import_declaration%*%class_declaration%"));
    // space
    MINI_JAVA.insert(pair<string, string>("s", " ")); 
    // package declaration cfg
    MINI_JAVA.insert(pair<string, string>("package_declaration", "%package_name%"));
        MINI_JAVA.insert(pair<string, string>("package_name", ".%word%|%word%"));
            MINI_JAVA.insert(pair<string, string>("word", "%letter%+"));
                    MINI_JAVA.insert(pair<string, string>("letter", "~a~b~c~d~e~f~g~h~i~j~k~l~m~n~o~p~q~r~s~t~u~v~w~x~y~z~A~B~C~D~E~F~G~H~I~J~K~L~M~N~O~P~Q~R~S~T~U~V~W~X~Y~Z"));
    //import declaration cfg
    MINI_JAVA.insert(pair<string, string>("import_declaration", "~import%s%%package_declaration%;"));
    // class declaration
    MINI_JAVA.insert(pair<string, string>("class_declaration", "%access_modifier%%s%class%s%{%property_declarations%}"));
        // access modifier
        MINI_JAVA.insert(pair<string, string>("access_modifier", "~private~public~protected"));
        // propertty declarations
        MINI_JAVA.insert(pair<string, string>("property_declaration", "%access_modifier%%function_declaration%|%access_modifier%%class_variable_declaration%"));
            MINI_JAVA.insert(pair<string, string>("function_declaration", "%type_defined%%s%%property_name%%s%(%parameter_definition%)%%s%*%block_code%"));
                // type defined
                MINI_JAVA.insert(pair<string, string>("type_defined", "~int~double~float~String~boolean~long%word%"));
                MINI_JAVA.insert(pair<string, string>("property_name", "%word%"));
                MINI_JAVA.insert(pair<string, string>("parameter_definition", ",%parameter%|%parameter%"));
                    MINI_JAVA.insert(pair<string, string>("parameter", "%type_defined%%s%%word%"));
                MINI_JAVA.insert(pair<string, string>("block_code", "%statements%*"));
                    MINI_JAVA.insert(pair<string, string>("statements", "%class_variable_declaration%;|%function_call%;|%if_else%|%while%"));
                        MINI_JAVA.insert(pair<string, string>("function_call", "%property_name%%s%*(%arguments%*)"));
                            MINI_JAVA.insert(pair<string, string>("arguments", ",%property_name%|%property_name%"));
                        MINI_JAVA.insert(pair<string, string>("if_else", "~if%s%%condition%%s%{%block_code%}"));
                            MINI_JAVA.insert(pair<string, string>("condition", "~(%tested_condition%)"));
                                MINI_JAVA.insert(pair<string, string>("tested_condition", "%condition_parameter%%s%*%comparator%%s%*%condition_parameter%"));
                                    MINI_JAVA.insert(pair<string, string>("condition_parameter", "%property_name%"));
                        MINI_JAVA.insert(pair<string, string>("while", "~while%s%*%condition%%s%*{%block_code%}"));
            MINI_JAVA.insert(pair<string, string>("class_variable_declaration", "%type_defined%%s%%%property_name%%s%*=%s%*%value%"));
                MINI_JAVA.insert(pair<string, string>("value", "%property_name%|%string_definition%|%equation_definition%"));
                    MINI_JAVA.insert(pair<string, string>("string_definition", "~\"%anything%\""));
                        MINI_JAVA.insert(pair<string, string>("anything", anything_string));
                    MINI_JAVA.insert(pair<string, string>("equation_definition", "%number%+%s%+%equation_sign%%s%+%number%+"));
                        MINI_JAVA.insert(pair<string, string>("number", "~1~2~3~4~5~6~7~8~9~0"));
                    
    create_language_map();
                    
}


void CFG::create_language_map() {
    string non_terminal = "";
    Queue<string> TS;
    Queue<string> NTS;
    Queue<char> perc_tracker;
    string lang = MINI_JAVA.find("start")->second;
    const char* start = lang.c_str();
    int i = 0;

    while(start[i] != '\0') {
        if(start[i] == '%' && perc_tracker.size() == 0) {
            perc_tracker.enqueue('%');
            if(non_terminal.compare("") != 0) {
                TS.enqueue(non_terminal);
                // cout<< "Terminal added: "<< non_terminal<< endl;
                non_terminal = "";
            }
        } else if(start[i] == '%' && perc_tracker.size() > 0) {
            if(start[i + 1] == '+') {
                non_terminal += " (positive closure)";
                i++;
            } else if(start[i + 1] == '*') {
                non_terminal += " (closure)";
                i++;
            }
            NTS.enqueue(non_terminal); 
            // cout<< "NON-TERMINAL ADDED: "<< non_terminal<< endl;
            non_terminal = "";
            perc_tracker.dequeue('%');
        } else {
            non_terminal += start[i];
        }
        i++;
    }

}