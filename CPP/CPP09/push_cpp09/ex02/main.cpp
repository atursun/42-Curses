
#include "PmergeMe.hpp"

int ctrl_aruments(int argc, char **args) {
    for (int i=1; i < argc; i++) {
        std::string str = args[i];
        for (size_t j=0; j < str.size(); j++) {
            if (!std::isdigit(str[j]))
                return (1);
        }
        if (atoi(str.c_str()) <= 0)
            return (1);
    }
    return (0);
}

int main(int argc, char **argv) {

    if (ctrl_aruments(argc, argv) || argc < 2)
        return (std::cerr << "Error" << std::endl, 1);

    PmergeMe me;
    me.add_to_containers(argc, argv);
    me.calculate_duration();
    return (0);
}
