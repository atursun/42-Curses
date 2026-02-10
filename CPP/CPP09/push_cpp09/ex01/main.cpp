
#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc == 2) {
        RPN rpn;
        rpn.ctrl_argument(argv[1]);
        rpn.calc_expression(argv[1]);
        return (0);
    }
    else
        std::cerr << "wrong argument number." << std::endl;
    return (1);
}
