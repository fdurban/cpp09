#include <iostream>
#include <string>
#include <fstream>



std::string	trim(const std::string &line)
{
	size_t	beginning;
	size_t	end;
	beginning = line.find_first_not_of(" \t");
	end = line.find_last_not_of(" \t");
	return (line.substr(beginning, end + 1));
}

bool	parseDate(const std::string & date)
{
	std::string	trimmedate;
	trimmedate = trim(date);
	//std::cout<<trimmedate<<std::endl;
	if (trimmedate.size() != 10)
	{
		std::cout<<trimmedate.size()<<std::endl;
		return false;
	}
	if (trimmedate[4] != '-' || trimmedate[7] != '-')
		return false;
	for(size_t i = 0; i < trimmedate.size(); i++)
	{
		if(i == 4 || i == 7)
			continue;
		if(trimmedate[i] < '0' || trimmedate[i] > '9')
			return false;
	}
	int year = std::atoi(trimmedate.substr(0, 4).c_str());
	int month = std::atoi(trimmedate.substr(5, 2).c_str());
	int day = std::atoi(trimmedate.substr(8, 2).c_str());
	std::cout<<month<<" "<<day<<" "<<year<<std::endl;
	std::cout<<trimmedate<<std::endl;
	if (year < 0 || year > 12)
		return false;
	bool	isLeapYear = false;
	if(year % 4 == 0)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
			{
				isLeapYear = true;
			}
			else
				isLeapYear = false;
		}
		else
			isLeapYear = true;
	}
	else
		isLeapYear = false;
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
	parseDate(date);
	return true;
}


int main(int argc, char **argv)
{
	if(argc != 2)
		std::cout<<"Not the right number of arguments"<<std::endl;
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
