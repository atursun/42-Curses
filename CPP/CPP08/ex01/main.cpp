
#include "Span.hpp"

int main(int, char **)
{
    {
        Span sp(5);
    
        try {
            sp.addNumber(74);
            sp.addNumber(4);
            sp.addNumber(50);
            sp.addNumber(2);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        try {
            int shn = sp.shortestSpan();
            std::cout << "Shortest span value is: " << shn << std::endl;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    
        try {
            int lng = sp.longestSpan();
            std::cout << "Longest span value is: " << lng << std::endl;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    {
        std::cout << "<<<Testing with 10.000 numbers>>>" << std::endl;

        Span sp2(10000);
        try {
            for (int i=0; i < 10000; i++)
                sp2.addNumber(std::rand());
            std::cout << "Longest span for 10.000 numbers: " << sp2.longestSpan() << std::endl;
            std::cout << "Shortest span for 10.000 numbers: " << sp2.shortestSpan() << std::endl;
        }
        catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    return 0;
}

