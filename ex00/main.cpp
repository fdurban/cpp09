#include <iostream>
#include <string>
#include <fstream>

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
	std::cout<<month<<" "<<day<<" "<<year<<std::endl;
	std::cout<<date<<std::endl;
	if (month < 1 || month > 12)
		return false;
	static const int daysInMonths[12] = {31, 28, 31, 30, 31,30, 31, 31, 30, 31,30,31};
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	int maxDays = daysInMonths[month - 1];
	if (month == 2 && isLeapYear)
	{
		maxDays = 29;
	}
	if (day < 1 || day > maxDays)
	{
		return false;
	}
	return true;
}



bool	parseInput(const std::string &line)
{
	size_t pos;
	std::string	date;
	//std::cout<<line<<std::endl;
	pos = line.find("|");
	if(pos == std::string::npos)
		return false;
	date = line.substr(0, pos);
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
			if(!parseInput(line))
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

}
