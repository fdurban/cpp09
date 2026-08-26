#ifndef RPN_HPP
#define RPN_HPP
#include <string>

class RPN
{
  public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	int evaluate(const std::string &expression) const;
  private:
	bool isOperator(std::string &token) const;
	int applyOperation(int a, int b, std::string &myOperator) const;
};
#endif
