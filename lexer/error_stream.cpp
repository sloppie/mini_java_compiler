#include "error_stream.h"

void ErrorStream::operator<<(string error) {
    ERRORS.at(ERRORS.size() - 1).push_back(error);
}


void ErrorStream::add_warning(string warning) {
    WARNINGS.at(WARNINGS.size() - 1).push_back(warning);
}


void ErrorStream::new_line() {
    vector<string> next_error_line;
    vector<string> next_warning_line;

    ERRORS.push_back(next_error_line);
    WARNINGS.push_back(next_warning_line);
}


bool ErrorStream::has_messages(string type) {
    bool err_located = false;

    vector<vector<string>> stack = (type.compare("ERRORS") == 0)? ERRORS: WARNINGS;

    for(vector<string> line: stack) {
        err_located = (line.size() > 0);

        if(err_located)
            break;

    }

    return err_located;
}


void ErrorStream::print_errors() {
    int LINE_NUMBER = ERRORS.size();

    for(int i=0; i<LINE_NUMBER; i++) {
        
        if(ERRORS.at(i).size() > 0 || WARNINGS.at(i).size() > 0) {
            cout<< "\033[1;21mline: "<< i + 1<< "\033[0m"<< endl;

            if(ERRORS.at(i).size() > 0) {
                cout<< "\033[1;31mERRORS:\033[0m "<< endl;
                
                for(string error: ERRORS.at(i)) {
                    cout<< "    "<< error<< endl;
                }

            }

            cout<< endl;

            if(WARNINGS.at(i).size() > 0) {
                cout<< "\033[1;36mWARNINGS: \033[0m"<< endl;
                
                for(string error: WARNINGS.at(i)) {
                    cout<< "    "<< error<< endl;
                }

            }

        }

    }

}