
#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) {*this = other;}
RPN &RPN::operator=(const RPN& other) {
    if (this != &other)
        this->my_stack = other.my_stack;
    return (*this);
}
RPN::~RPN() {}


bool RPN::operations(char ops) {
    return (ops == '+' || ops == '-' || ops == '*' || ops == '/');
}

void RPN::ctrl_argument(std::string expression) {
    for (size_t i=0; i < expression.length(); i++) {
        if ((expression[i] >= '0' && expression[i] <= '9') || operations(expression[i]))
            i++;
        else
            (std::cerr << "Error" << std::endl, exit(1));
    }
}

void    RPN::calc_expression(std::string expression) {
    for (size_t i=0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;
        if (isdigit(expression[i])) {
            int val = expression[i] - '0';
            my_stack.push(val);
        }
        else if (operations(expression[i])) {
            if (my_stack.size() >= 1) {
                int b = my_stack.top();
                my_stack.pop();
                int a = my_stack.top();
                my_stack.pop();

                int res = 0;
                if (expression[i] == '+')
                    res = a + b;
                else if (expression[i] == '-')
                    res = a - b;
                else if (expression[i] == '*')
                    res = a * b;
                else if (expression[i] == '/') {
                    if (b == 0) {
                        std::cout << "Error: ZeroDivision" << std::endl;
                        return ;
                    }
                    res = a / b;
                }
                my_stack.push(res);
            }
        }
        else {
            std::cout << "Error" << std::endl;
            return ;
        }
    }
    std::cout << my_stack.top() << std::endl;
}
