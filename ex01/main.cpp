#include <iostream>
#include <stack>
#include <sstream>

bool	isOperator(std::string	token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int	applyOperation(int a, int b, std::string myOperator)
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
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout<<"Error: Not the right "<<std::endl;
		return 1;
	}
	std::stringstream ss(argv[1]);
	std::stack<int> s;
	std::string	token;
	while(ss >> token)
	{
		std::cout<<token<<" ";
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
	}
	if(s.size() != 1)
	{
		std::cout<<"Calculation error"<<std::endl;
		return 1;
	}
	 
}
