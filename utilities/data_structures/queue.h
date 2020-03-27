#ifndef QUEUE_H
#define QUEUE_H

#include<vector>

using namespace std;

template <typename T>
class Queue {
    public:
        Queue() {
            lock = 0;
        }

        int size() {
            return (stack.size() - lock);
        }

        T dequeue(T default_value) {
            T value = default_value;
            if(lock<stack.size()) {
                value = stack.at(lock);
                lock++;
            }

            return value;
        }

        vector<T> get_queue() {
            vector<T> new_queue;

            for(int i=lock; i<stack.size(); i++) {
                new_queue.push_back(stack.at(i));
            }

            return new_queue;
        }

        vector<T> get_init_queue() {
            return stack;
        }

        void enqueue(T value) {
            stack.push_back(value);
        }

    private:
        vector<T> stack;
        int lock;

};

#endif