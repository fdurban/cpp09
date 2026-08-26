#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <sstream>

RPN::RPN()
{}

RPN::RPN(const RPN &other)
{
	(void)other;
}

RPN  &RPN::operator=(const RPN &other)
{
	(void) other;
	return *this;
}
RPN::~RPN()
{}


bool	RPN::isOperator(std::string	&token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int	RPN::applyOperation(int a, int b, std::string &myOperator) const
{
	if(myOperator == "+")
		return a + b;
	else if (myOperator == "-")
		return a - b;
	else if (myOperator == "*")
		return a * b;
	else if (myOperator == "/")
		if(b == 0)
		{
			std::cout<<"Error: Can not divide by 0"<<std::endl;
			return 0;
		}
		else return a/b;
	else
		return 0;
}


int RPN::evaluate(const std::string &expr) const
{
	std::stringstream ss(expr);
	std::stack<int> s;
	std::string	token;
	while(ss >> token)
	{
		std::cout<<"token : "<<token<<" ";
		if(token.size() == 1 && std::isdigit(token[0]))
		{
			s.push(token[0] - '0');
		}
		else if(isOperator(token))
		{
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();
			int c;
			c = applyOperation(a, b, token);
			s.push(c);
			std::cout<<c<<std::endl;
		}
		else
			throw std::runtime_error("invalid token");
	}
	if(s.size() != 1)
	{
		std::cout<<"Calculation error"<<std::endl;
		return 1;
	}
	return s.top();
}
