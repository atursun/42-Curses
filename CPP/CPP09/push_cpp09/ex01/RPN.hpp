
#pragma once

#include <iostream>
#include <cstdlib>
#include <stack>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    RPN &operator=(const RPN& other);
    ~RPN();

    bool    operations(char chr);
    void    ctrl_argument(std::string expression);
    void    calc_expression(std::string expression);

private:
    std::stack<int> my_stack;
};
