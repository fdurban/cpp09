#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

int main(int argc, char **argv)
{
    if(argc != 2) {
        std::cout << "Error: could not open file.\n";
        return 1;
    }
    BitcoinExchange btc;
    try {
        btc.loadDatabase("data.csv");
        btc.processfile(argv[1]);
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}
