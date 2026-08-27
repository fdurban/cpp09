#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : database(other.database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other)
    database = other.database;
  return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::parsePrice(const std::string &priceStr, float &outValue, float min, float max)
{
    std::stringstream ss(priceStr);
    float val;
    if (!(ss >> val)) {
        return false;
    }
    std::string leftover;
    if(ss >> leftover)
	    return false;
    if (val < min || val > max) {
        return false;
    }
    outValue = val;
    return true;
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    
    if (!file.is_open()) throw std::runtime_error("Error: could not open database file.");
    std::getline(file, line); // Saltar header
    
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) continue; // Archivo CSV usa ','
        
        std::string date = line.substr(0, pos);
        std::string price = line.substr(pos + 1);
        float value;
        
        // Validación estricta: Precio debe ser positivo, pero sin límite máximo
        if (parseDate(date) && parsePrice(price, value, 0.0f, 2147483647.0f)) {
            database[date] = value;
        }
    }
}

bool	BitcoinExchange::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool	BitcoinExchange::isValidDate(int year, int month, int day)
{
	if(month > 12 || month < 1 || year < 0 || day < 1)
		return false;
	static const int daysInMonths[12] = {31, 28, 31, 30, 31,30, 31, 31, 30, 31,30,31};
	int maxDays = daysInMonths[month - 1];
	if (month == 2 && isLeapYear(year))
	{
		maxDays = 29;
	}
	return day <=maxDays;
}
bool	BitcoinExchange::parseDate(const std::string & date)
{
	size_t start = date.find_first_not_of(" \t");
	size_t end = date.find_last_not_of(" \t");
	if (start == std::string::npos) return false;
	
	if ((end - start) + 1 != 10)
	{
		std::cout<<end - start<<std::endl;
		return false;
	}
	if (date[start + 4] != '-' || date[start + 7] != '-')
		return false;
	for(size_t i = start; i <= end ; i++)
	{
		if(i == start + 4 || i == start + 7)
			continue;
		if(date[i] < '0' || date[i] > '9')
			return false;
	}
	int year = (date[start] - '0') * 1000 + 
	(date[start +1] - '0') * 100 +
	(date[start + 2] - '0') * 10 +
	date[start + 3] - '0';
	int month = (date[start + 5] - '0') * 10 +
	(date[start + 6] - '0');
	int day = (date[start + 8] - '0') * 10 +
	(date[start + 9] - '0');
	return isValidDate(year, month, day);
}

void	BitcoinExchange::processfile(std::string infile)
{
	std::ifstream inputfile(infile.c_str());
	std::string line;
	if(!inputfile.is_open())
	{
		std::cerr<<"Could not open the file\n";
	}
	std::getline(inputfile, line);
	while(std::getline(inputfile, line))
	{
		size_t pos = line.find(" | ");
		if(pos == std::string::npos)
		{
			std::cout<<"Error: Wrong Format"<<std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		//pos = line.find("|", pos + 1);
		std::string price = line.substr(pos + 3);
		float value;
		//if(pos != std::string::npos)
		//	return false;
		//std::cout<<price<<std::endl;
		if(!parseDate(date))
		{
			std::cout<<"Error: Not the right format"<<std::endl;
			continue;
		}
		if(!parsePrice(price, value, 0.0f, 1000.f))
		{
			std::cout<<"Error, invalid price/value\n";
			continue;
		}
		std::map<std::string, double>::iterator it = this->database.lower_bound(date);
		if(it == this->database.begin() && it->first != date)
		{
			std::cerr<<"Error, Date too early"<<date<<"\n";
			continue;
		}
		if(it == this->database.end() || it->first != date)
			--it;
		std::cout<<date<<" => "<<price<<" "<<value*it->second<<std::endl;
		//std::cout<<it->first<<std::endl;
	}
}
