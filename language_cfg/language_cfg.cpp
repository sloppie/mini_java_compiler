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
    MINI_JAVA.insert(pair<string, string>("import_declaration", "import%s%+%package_declaration%;%s%"));
    // class declaration
    MINI_JAVA.insert(pair<string, string>("class_declaration", "%access_modifier%%s%class%s%{%property_declaration%}"));
        // access modifier
        MINI_JAVA.insert(pair<string, string>("access_modifier", "~private~public~protected"));
        // propertty declarations
        MINI_JAVA.insert(pair<string, string>("property_declaration", "%access_modifier%%function_declaration%|%access_modifier%%class_variable_declaration%"));
            MINI_JAVA.insert(pair<string, string>("function_declaration", "%type_defined%%s%%property_name%%s%(%parameter_definition%)%s%%block_code%"));
                // type defined
                MINI_JAVA.insert(pair<string, string>("type_defined", "~int~double~float~String~boolean~long%word%"));
                MINI_JAVA.insert(pair<string, string>("property_name", "%word%"));
                MINI_JAVA.insert(pair<string, string>("parameter_definition", ",%parameter%|%parameter%"));
                    MINI_JAVA.insert(pair<string, string>("parameter", "%type_defined%%s%%word%"));
                MINI_JAVA.insert(pair<string, string>("block_code", "%statements%*"));
                    MINI_JAVA.insert(pair<string, string>("statements", "%class_variable_declaration%;|%function_call%;|%if_else%|%while%"));
                        MINI_JAVA.insert(pair<string, string>("function_call", "%property_name%%s%*(%arguments%*)"));
                            MINI_JAVA.insert(pair<string, string>("arguments", ",%property_name%|%property_name%"));
                        MINI_JAVA.insert(pair<string, string>("if_else", "if%s%%condition%%s%{%block_code%}"));
                            MINI_JAVA.insert(pair<string, string>("condition", "(%tested_condition%)"));
                                MINI_JAVA.insert(pair<string, string>("tested_condition", "%condition_parameter%%s%*%comparator%%s%*%condition_parameter%"));
                                    MINI_JAVA.insert(pair<string, string>("condition_parameter", "%property_name%"));
                                    MINI_JAVA.insert(pair<string, string>("comparator", "~!~==~>~<~>=~<=~!="));
                        MINI_JAVA.insert(pair<string, string>("while", "~while%s%*%condition%%s%*{%block_code%}"));
            MINI_JAVA.insert(pair<string, string>("class_variable_declaration", "%type_defined%%s%%property_name%%s%*=%s%*%value%"));
                MINI_JAVA.insert(pair<string, string>("value", "%property_name%|%string_definition%|%equation_definition%"));
                    MINI_JAVA.insert(pair<string, string>("string_definition", "~\"%anything%\""));
                        MINI_JAVA.insert(pair<string, string>("anything", anything_string));
                    MINI_JAVA.insert(pair<string, string>("equation_definition", "%number%+%s%+%equation_sign%%s%+%number%+"));
                        MINI_JAVA.insert(pair<string, string>("number", "~1~2~3~4~5~6~7~8~9~0"));
                        MINI_JAVA.insert(pair<string, string>("equation_sign", "~+~-~*~/"));
                    
    create_language_map();
                    
}


Queue<string*>* CFG::create_language_map(string key) {
    string non_terminal = "";
    Queue<string*>* order_queue = new Queue<string*>;
    Queue<string> TS;
    Queue<string> NTS;
    Queue<char> perc_tracker;
    string lang = MINI_JAVA.find(key)->second;

    const char* start = lang.c_str();
    int i = 0;

    while(start[i] != '\0') {

        if(start[i] == '%' && perc_tracker.size() == 0) {
            perc_tracker.enqueue('%');

            if(non_terminal.compare("") != 0) {
                TS.enqueue(non_terminal);
                string* new_terminal = new string[3];
                new_terminal[0] = non_terminal;
                new_terminal[1] = "terminal";
                new_terminal[2] = "NONE"; // defines the closure
                order_queue->enqueue(new_terminal);
                // cout<< "Terminal added: "<< non_terminal<< endl;
                non_terminal = "";
            }

        } else if(start[i] == '%' && perc_tracker.size() > 0) {
            NTS.enqueue(non_terminal); 
            string* new_terminal = new string[3];
            new_terminal[0] = non_terminal;
            new_terminal[1] = "non terminal";
            new_terminal[2] = "NONE"; // defines the closure

            if(start[i + 1] == '+') {
                new_terminal[2] = "POSITIVE";
                i++;
            } else if(start[i + 1] == '*') {
                new_terminal[2] = "CLOSURE";
                i++;
            }

            order_queue->enqueue(new_terminal);
            // cout<< "NON-TERMINAL ADDED: "<< non_terminal<< endl;
            non_terminal = "";
            perc_tracker.dequeue('%');
        } else {
            non_terminal += start[i];
        }

        i++;
    }

    return order_queue;
}


string CFG::fetch_cfg(string key) {
    return MINI_JAVA.find(key)->second;
}


bool CFG::is_word(const char* source_code) {
    char letters[52] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z'};
    bool is_word = true;
    bool toggle = true;
    string word = "";
    int CURSOR = 0;
    // while(toggle) { // game loop
    while(source_code[CURSOR] != '\0') {
        bool found = false;
        for(int i=0; i<52; i++) {
            if(source_code[CURSOR] == letters[i]) {
                found = true;
                break;
            }
        }

        if(!found) {
            is_word = false;
            cout<< "Unexpected symbol: '"<< source_code[CURSOR]<< "' in word: \""<< source_code<< endl;
            break;
        }

        CURSOR++;
    }
    // }

    return is_word;
}


bool CFG::is_package_name(const char* source_code, int *CURSOR) {
    bool is_pkg = true;

    if(source_code[*CURSOR] != '.' && source_code[*CURSOR] != ' ' && source_code[*CURSOR] != ';') {
        string package_name = "";
        string word = "";
        while(source_code[*CURSOR] != ' ' && source_code[*CURSOR] != ';') {
            package_name += source_code[*CURSOR];

            if(source_code[*CURSOR] == '.') {
                if(is_pkg) {
                    is_pkg = is_word(word.c_str());
                    word = "";
                    if(source_code[*CURSOR + 1] == '.') {
                        is_pkg = false;
                        cout<< "Two dots should not follow each other in a package declaration: \""<< source_code<< endl;
                    }
                }
            } else {
                word += source_code[*CURSOR];
            }

            (*CURSOR)++;
        }

        is_pkg = is_word(word.c_str());

    } else if(source_code[*CURSOR] == '.'){
        cout<< "Package name cannot begin with '.'"<< endl;
        is_pkg = false;
    } else {
        cout<< "Package name cannot be empty"<< endl;
        is_pkg = false;
    }

    return is_pkg;
}