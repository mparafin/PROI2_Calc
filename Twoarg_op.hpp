#ifndef __TWOARG_OP__
#define __TWOARG_OP__

#include "Operation.hpp"
#include <string>


class Twoarg_op: public Operation{
    private:
        Node *arg_left, *arg_right;
    public:
        Twoarg_op(std::string type_indicator, std::string left_arg, std::string right_arg);
        ~Twoarg_op();
        void print();
        Node* parse(Calculator*);
        double calculate();
};

#endif