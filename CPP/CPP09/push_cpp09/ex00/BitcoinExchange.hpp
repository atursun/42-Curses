
#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <cstdlib>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange &operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void    add_database(std::string filename);
    void    process_input(std::string input_file);

private:
    std::map<std::string, double> my_map;
};
