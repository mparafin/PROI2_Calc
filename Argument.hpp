#ifndef __ARGUMENT_HPP__
#define __ARGUMENT_HPP__

#include "Node.hpp"

class Argument: public Node{
    private:
        double value;
    public:
        Argument(double);
        void print();
        double calculate();
};

#endif