#ifndef TERM_H
#define TERM_H

#include<iostream>

#define POSITIVE_CLOSURE "POSITIVE_CLOSURE"
#define CLOSURE "CLOSURE"
#define NO_CLOSURE "NO_CLOSURE"

typedef struct {
    std::string name;
    bool is_terminal;
    std::string closure;
} term;

#endif