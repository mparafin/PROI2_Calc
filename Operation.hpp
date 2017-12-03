#ifndef __OPERATION_HPP__
#define __OPERATION_HPP__

#include "Node.hpp"

enum operation_type {PLUS, MINUS, MULTIPLY, DIVIDE, POWER, LN, LOG, STRONG, EXP};

class Operation: public Node {
    protected:
    enum operation_type type;
};

#endif