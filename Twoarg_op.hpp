#ifndef __TWOARG_OP__
#define __TWOARG_OP__

#include "Operation.hpp"
#include <string>

class Twoarg_op: public Operation{
    private:
        Node *arg_left, *arg_right;
    public:
        Twoarg_op(std::string&, std::string&, std::string&);
        ~Twoarg_op();
        void print();
        double calculate();
};

#endif