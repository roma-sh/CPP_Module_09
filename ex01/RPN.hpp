#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include	<stack>
#include	<sstream>
#include	<string>
#include	<cmath>

class RPN
{
public:
	RPN();
	RPN(std::string expression);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	void fillStacks();
	double calculate();
	bool isValidExpression() const;

private:
	std::stack<short>	_stackNum;
	std::stack <char>	_stackSign;
	std::string			_expression;

};

#endif
