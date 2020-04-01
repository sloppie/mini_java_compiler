#ifndef ERROR_STREAM_H
#define ERROR_STREAM_H

#include<iostream>
#include<vector>

using namespace std;

class ErrorStream {

    public:
        ErrorStream() {
            new_line(); // account for line 1
        }
        // adds a string sream into the error class later to be printed all together
        // at the end of lexical analysis
        void operator<< (string);
        // adds warning, these do not stop parsing, but are worthwile giving 'warning' to the programmer
        void add_warning(string);
        // used to add vectors for each new line to allow correct tracking of lines
        void new_line();
        // checks for the presence of error/warnings returning a bool
        // if errors are present it will terminate
        // else it will move on to the parsing process
        bool has_messages(string);
        // print all the errors and warnings (if any) present in the source code
        void print_errors();

    private:
        vector<vector<string>> ERRORS;
        vector<vector<string>> WARNINGS;

};

#endif