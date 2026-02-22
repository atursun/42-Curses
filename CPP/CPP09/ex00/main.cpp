
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc == 2) {
        try {
            BitcoinExchange btc;
            btc.add_database("data.csv");
            btc.process_input(argv[1]);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return (1);
        }
        return (0);
    }
    else
        std::cerr << "Error: could not open file." << std::endl;
    return (1);
}
