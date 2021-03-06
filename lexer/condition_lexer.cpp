#include "lexer.h"

#include "../utilities/data_structures/node.h"


void Lexer::unpack_condition(string source_code, Node* CONDITION_CARRIER) {
    Node CONDITION(false, "condition");
    const char* condition = source_code.c_str();
    Queue<string> condition_queue;
    CONDITION.add_children(Node(true, "("));
    int CURSOR = 1;
    CFG cfg;

    string error_message;
    // split conditions
    string condition_found = "";

    // offload conditions
    while(condition[CURSOR] != '\0') {
        
        // ensure the coreect progression of the symbols, to avoid mix up in the case of a symbol such as: &| or |&
        if(condition[CURSOR] == '&' || condition[CURSOR] == '|') {

            if(condition[CURSOR] == '&') {
 
                if(condition[CURSOR + 1] == '&') {
                    condition_queue.enqueue(condition_found);
                    condition_queue.enqueue("&&");
                    condition_found = "";
                } else {
                    error_message = "Expected \033[1;0m&&\033[0m as a connector after condition: \"\033[1;0m";
                    error_message += condition;
                    error_message += "\033[0m\"";

                    (*ERROR_STREAM)<< error_message;
                }

            } else { // handle or connector
 
                if(condition[CURSOR + 1] == '|') {
                    condition_queue.enqueue(condition_found);
                    condition_queue.enqueue("||");
                    condition_found = "";
                } else {
                    error_message = "Expected \033[1;0m||\033[0m as a connector after condition: \"\033[1;0m";
                    error_message += condition;
                    error_message += "\033[0m\"";

                    (*ERROR_STREAM)<< error_message;
                    // cout<< "Expected '||' as a connector after condition: "<< condition<< endl;
                }

            }

            CURSOR += 2;
            continue;
        } else { // block handlin creating of term nodes and skipping over nested conditions

            if(condition[CURSOR] != '(') {

                if(condition[CURSOR] != ')') {

                    if(condition[CURSOR] != ' ' && condition_found.compare("") == 0) {
                        condition_found += condition[CURSOR];
                    } else if(condition_found.compare("") != 0)
                        condition_found += condition[CURSOR];

                } else {

                    if(condition_found.compare("") != 0) {
                        condition_queue.enqueue(condition_found);
                    }

                }

            } else {
                error_message = "Nested conditions are not allowed. Attempting to skip over the condition";

                // (*ERROR_STREAM)<< error_message;
                ERROR_STREAM->add_warning(error_message);
                // cout<< "Nested conditions not allowed in this mini java... Skipping over nested condition"<< endl;
                
                while(condition[CURSOR] != ')') {
                    CURSOR++;
                }

                CURSOR++;
                continue;
            }
        }
        
        CURSOR++;
    }

    // verify variables
    for(string conditions: condition_queue.get_init_queue()) {
        
        string cnd = "";
        
        if(conditions.compare("&&") != 0 && conditions.compare("||") != 0) {
            break_down_condition(conditions.c_str(), &CONDITION);
        } else {
            CONDITION.add_children(Node(true, "connector", conditions));
        }

    }

    CONDITION.add_children(Node(true, ")"));
    // push in token stream
    CONDITION_CARRIER->add_children(CONDITION);
}


vector<string> Lexer::break_down_condition(const char* condition, Node* CONDITION) {
    Node condn(false, "tested_condition");
    CFG cfg;
    char COMPARATOR_TOKENS[] = {'>', '<', '=', '!'};

    int CURSOR = 0;

    vector<string> conditions;
    string last_cond = "";
    string last_cond_type = "";

    string error_message;
    
    while(condition[CURSOR] != '\0') {
        
        if(condition[CURSOR] != ' ') {
            bool comp_token_found = false;
            
            for(int i=0; i<4; i++) { // searches for a comparisson symbol eg: '>', '<', '!' and their equivalent 'or equal to:' 

                if(!comp_token_found) {
                    comp_token_found = COMPARATOR_TOKENS[i] == condition[CURSOR];
                    if(comp_token_found) {
                        break;
                    }
                }

            }

            if(comp_token_found) {

                if(last_cond.compare("") != 0) {

                    if(is_function_call(last_cond)) {
                        unpack_function_call(last_cond, &condn);

                        cout<< "\033[1;21mTested_condition\033[0m oken added -> "<< last_cond<< endl;
                        last_cond_type = "variable";
                    } else if(cfg.is_word(last_cond.c_str())) {
                        string* param = SYMBOL_TABLE->find(last_cond);

                        if(param[0].compare("undefined") != 0) {
                            condn.add_children(Node(false, "condition_parameter", last_cond));
                            // CONDITION->add_children(Node(false, "condition_parameter", last_cond));
                            cout<< "\033[1;21mcondition_parameter\033[0m token added: \033[1;21m"<< last_cond<< "\033[0m"<< endl;
                        } else {
                            //warning
                            error_message = "Token: \033[1;0m";
                            error_message += last_cond;
                            error_message += "\033[0m added as \033[1;0mundefined\033[0m token";

                            ERROR_STREAM->add_warning(error_message);
                            condn.add_children(Node(false, "condition_parameter", "undefined"));
                            // CONDITION->add_children(Node(false, "condition_parameter", "undefined"));
                        }

                        last_cond_type = "variable";

                    } else {

                        if(cfg.is_condition(last_cond.c_str())) {
                            condn.add_children(Node(false, "condition_parameter", last_cond));
                            cout<< last_cond<< "\033[1;21mcomparator_token\033[0m token added"<< endl;
                            last_cond_type = "variable";
                        } else {
                            error_message = "Invalid token: \033[1;0m";
                            error_message += last_cond;
                            error_message += "\033[0m passed as a condition param";

                            (*ERROR_STREAM)<< error_message;
                        }

                    }

                    conditions.push_back(last_cond);
                    last_cond = "";
                }

                if(condition[CURSOR + 1] == '=') {
                    string comparator_token = "";
                    comparator_token += condition[CURSOR];
                    comparator_token += condition[CURSOR + 1];

                    if(conditions.size() > 0) { // checks condition progression

                        if(last_cond_type.compare("variable") == 0) {
                            condn.add_children(Node(true, "comparator", comparator_token));
                            cout<< "\033[1;21mcomparator\033[0m token added: \033[1;21m"<< comparator_token<< "\033[0m"<< endl;
                            conditions.push_back(comparator_token);
                        } else {
                            error_message = "\033[1;21m Invalid progression\033[0m. Expectedd variable or condition before the comparission operator \"\033[1;21m";
                            error_message += comparator_token;
                            error_message += "\033[0m";

                            (*ERROR_STREAM)<< error_message;
                        }

                    } else {
                        error_message = "\033[1;0m Invalid progression\033[0m. Expectedd variable or condition before the comparission operator \"\033[1;0m";
                        error_message += comparator_token;
                        error_message += "\033[0m";

                        (*ERROR_STREAM)<< error_message;
                    }

                    CURSOR++;
                } else {

                    std::string next_word = "";
                    next_word += condition[CURSOR + 1];
                    std::string compar = "";
                    compar += condition[CURSOR]; 

                    if(condition[CURSOR + 1] != ' ') {
                        string comparator_token = "";
                        comparator_token += condition[CURSOR];
                        comparator_token += condition[CURSOR + 1];

                        error_message = "\033[1;21mInvalid token progression\033[0m]: \033[1;21m";
                        error_message += comparator_token;
                        error_message += "\033[0m";

                        (*ERROR_STREAM)<< error_message;
                        CURSOR++;
                    } else {
                        condn.add_children(Node(true, "comparator", compar));
                    }

                }

            } else {
                last_cond += condition[CURSOR];
            }

        } else {

            while(condition[CURSOR + 1] ==  ' ') {
                CURSOR++;
            }

            // continue;
        }

        CURSOR++;
    }

    // the while loop does not cater for adding of the last condition
    if(last_cond.compare("") != 0) {

        if (!is_function_call(last_cond) && !cfg.is_word(last_cond.c_str())){
            error_message = "\033[1;0mInvalid\033[0m token\033[1;0m ";
            error_message += last_cond;
            error_message += "\033[0m at the end of condition";

            (*ERROR_STREAM)<< error_message;
        } else {
            conditions.push_back(last_cond);
            condn.add_children(Node(false, "condition_parameter", last_cond));
            cout<< "\033[1;21mcondition_parameter\033[0m token added: \033[1;21m"<< last_cond<< "\033[0m"<< endl;
        }

    }

    CONDITION->add_children(condn);
    return conditions;

}