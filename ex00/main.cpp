#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
	if(argc != 2)
		std::cout<<"Not the right number of arguments"<<std::endl;
	std::ifstream infile(argv[1]);
	std::string line;
	if(infile.is_open())
	{
		std::getline(infile, line);
		if(line != "date | valu")
		{
			std::cout<<"Error: headder part of the file"<<std::endl;
			return 1;
		}

		
	}
}
