#ifndef __NODE_HPP__
#define __NODE_HPP__

struct Calculator;

class Node{
    public:
        virtual void print() = 0;
        virtual double calculate() = 0;
        virtual Node* parse(Calculator*) = 0;
};

#endif