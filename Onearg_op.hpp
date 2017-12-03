#ifndef __ONEARG_OP_HPP__
#define __ONEARG_OP_HPP__

#include "Operation.hpp"
#include <string>

class Onearg_op: public Operation{
    private:
        Node *arg;
    public:
        Onearg_op(std::string&, std::string&);
        ~Onearg_op();
        void print();
        double calculate();
};

#endif