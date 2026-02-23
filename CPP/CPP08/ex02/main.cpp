
#include "MutantStack.hpp"

int main(int, char**) {
    MutantStack<int> mstack;

    mstack.push(6);
    mstack.push(3);
    mstack.push(5);
    mstack.pop();
    mstack.push(2);

    std::cout << "Size: " << mstack.size() << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); it++)
        std::cout << *it << std::endl;
    return (0);
}
