#include <iostream>
#include <string>
#include <fstream>


bool	isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool	isValidDate(int year, int month, int day)
{
	static const int daysInMonths[12] = {31, 28, 31, 30, 31,30, 31, 31, 30, 31,30,31};
	int maxDays = daysInMonths[month - 1];
	if (day < 1 || day > maxDays || month > 12 || month < 1 )
	{
		return false;
	}
	if (month == 2 && isLeapYear(year))
	{
		maxDays = 29;
	}
	return day <=maxDays;
}
bool	parseDate(const std::string & date)
{
	//std::cout<<trimmedate<<std::endl;
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
	//std::cout<<month<<" "<<day<<" "<<year<<std::endl;
	//std::cout<<date<<std::endl;
	return isValidDate(year, month, day);
}

bool	parsePrice(const std::string &price)
{
	std::map<std::string,  int> database;
//	size_t start = price.find_first_not_of(" \t");
//	size_t end = price.find_last_not_of(" \t");
	float result;
	std::stringstream ss(price)
	std::cout<<result<<std::endl;
	if(!(ss >> result)|| result < 0)
		std::cout<<"Error: invalid price"<<std::endl;
}

bool	parseInput(const std::string &line, char divider)
{
	size_t pos;
	std::string	date;
	std::string	price;
	//std::cout<<line<<std::endl;
	pos = line.find(divider);
	if(pos == std::string::npos)
		return false;
	date = line.substr(0, pos);
	//pos = line.find("|", pos + 1);
	price = line.substr(pos + 1 , '\n');
	//if(pos != std::string::npos)
	//	return false;
	std::cout<<price<<std::endl;
	if(!parseDate(date))
		return false;
	return true;
}


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout<<"Not the right number of arguments"<<std::endl;
		return 1;
	}
	std::ifstream infile(argv[1]);
	std::string line;
	if(infile.is_open())
	{
		std::getline(infile, line);
		if(line != "date | value")
		{
			std::cout<<"Error: header part of the file"<<std::endl;
			return 1;
		}
		while(std::getline(infile, line))
		{
			if(!parseInput(line, '|'))
			{
				std::cout<<"Error: Not the right input";
				return 1;
			}
		}
		
	}
	else
	{
		std::cout<<"Something went wrong"<<std::endl;
	}
	std::ifstream data("data.csv");
	std::string dataline;
	if(infile.is_open())
	{
		std::getline(data, dataline);
		if(dataline  != "date,exchange_rate")
		{
			std::cout<<"Error: header part of the data file"<<std::endl;
			return 1;
			while(std::getline(data, dataline))
			{
				if(!parseInput(dataline, ','))
				{
					std::cout<<"Error, not the right data input";
					return 1;
				}
			}
		}
	}
	else
	{
		std::cout<<"Something went wrong in the datafile"<<std::endl;
		return 1;
	}
}
