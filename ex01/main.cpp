#include <iostream>
#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout<<"Error: Not the right number of arguments"<<std::endl;
		return 1;
	}
	try
	{
		RPN rpn;
		std::cout<<rpn.evaluate(argv[1])<<std::endl;
	}
	catch(const std::exception &e)
	{
		std::cerr<<"Error"<<e.what()<<"\n";
		return 1;
	}
	return 0;
}
