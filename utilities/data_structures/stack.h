#ifndef STACK_H
#define STACK_H

#include<vector>

using namespace std;

template <typename T>
class Stack {
    public:
        Stack() {}

        void pop() {
            stack.pop_back();
        }

        T pop_val() {
            T data = stack.at(stack.size() - 1);
            stack.pop_back();

            return data;
        }

        void push(T new_val) {
            stack.push_back(new_val);
        }

        vector<T> get_stack() {
            return stack;
        }

    private:
        vector<T> stack;

};

#endif