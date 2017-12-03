#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__

class Expression: public Node{
    private:
        std::string value;
    public:
        Expression(std::string&);
        void print();
        double calculate();
};

#endif