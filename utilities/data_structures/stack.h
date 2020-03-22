#ifndef QUEUE_H
#define QUEUE_H

#include<vector>


template <typename T>
class Stack {
    public:
        Stack() {}

        void pop() {
            stack.pop_back();
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