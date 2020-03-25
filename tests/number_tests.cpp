#include<iostream>

#include "../language_cfg/language_cfg.h"

#define INT "INTEGER"
#define NOT_INT "NOT_INTEGER"
#define FLOAT "FLOAT"
#define NOT_FLOAT "NOT_FLOAT"

using namespace std;

int lexer_tests() {
    CFG mini_java;
    string int_tests[][2] = {{"0", INT}, {"12", INT}, {"0.1", NOT_INT}, {"0230", NOT_INT}, {"230", INT}, {"2000", INT}, {"23e4", NOT_INT}};
    string double_tests[][2] = {{"0.0", FLOAT}, {"1.3456777", FLOAT}, {"1.2.3", NOT_FLOAT}, {"1.", NOT_FLOAT}, {"2344.03", FLOAT}, {"234.e45", NOT_FLOAT}, {"0", NOT_FLOAT}};
    
    cout<< "************** INT TEST ********************"<< endl;

    for(int i=0; i<7; i++) {
        string answer = (mini_java.is_int(int_tests[i][0].c_str()))? INT: NOT_INT;

        bool passed = (answer.compare(int_tests[i][1]) == 0);

        if(passed) {
            cout<< "\""<< int_tests[i][0]<< "\" passed the int test"<< endl;
        } else {
            cout<< "\""<< int_tests[i][0]<< "\" failed the int test"<< endl;
        }
    }

    cout<< endl;
    cout<< "************** FLOAT TEST ******************"<< endl;
    cout<< endl;

    for(int i=0; i<7; i++) {
        string answer = (mini_java.is_decimal(double_tests[i][0].c_str()))? FLOAT: NOT_FLOAT;

        bool passed = (answer.compare(double_tests[i][1]) == 0);

        if(passed) {
            cout<< "\""<< double_tests[i][0]<< "\" passed the DECIMAL test"<< endl;
        } else {
            cout<< "\""<< double_tests[i][0]<< "\" failed the DECIMAL test"<< endl;
        }
    }

    return 0;
}