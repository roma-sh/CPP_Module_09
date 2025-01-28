#include "RPN.hpp"

RPN::RPN() : _expression("") {}
RPN::RPN(std::string expression) : _expression(expression) {}
RPN::RPN(const RPN &other) : _expression(other._expression) {}
RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_expression = other._expression;
	return *this;
}
RPN::~RPN() {}

void RPN::fillStacks()
{
	if (!isValidExpression())
	{
		std::cerr << "Error: invalid expression" << std::endl;
		exit(1);
	}
	std::istringstream iss(_expression);
	std::string token;
/*
>> Operator
	*-The >> operator is overloaded for std::istringstream to extract words or tokens
		(delimited by whitespace) from the input stream (iss) one at a time.
	*-Each time >> is used, it reads the next "token" (a substring separated by spaces)
		from the stream and stores it in the variable token.
*/

	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
			_stackSign.push(token[0]);
		else
			_stackNum.push(std::stoi(token));
	}
	std::stack<short> tmpNum;
	std::stack<char> tmpSign;
	while (!_stackNum.empty())
	{
		tmpNum.push(_stackNum.top());
		_stackNum.pop();
	}
	while (!_stackSign.empty())
	{
		tmpSign.push(_stackSign.top());
		_stackSign.pop();
	}
	_stackNum = tmpNum;
	_stackSign = tmpSign;
}

double RPN::calculate()
{
	double result = 0;
	short a, b;
	while (!_stackSign.empty())
	{
		a = _stackNum.top();
		_stackNum.pop();
		b = _stackNum.top();
		_stackNum.pop();
		char sign = _stackSign.top();
		_stackSign.pop();
		switch (sign)
		{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			if (b == 0)
			{
				std::cerr << "Error: division by zero" << std::endl;
				exit(1);
			}
			result = a / b;
			break;
		}
		_stackNum.push(result);
	}
	return result;
}


bool RPN::isValidExpression() const
{
	std::istringstream iss(_expression);
	std::string token;
	int operandCount = 0;
	int operatorCount = 0;

	while (iss >> token)
	{
		if (isdigit(token[0])) {
			operandCount++;
		} else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
			operatorCount++;
			if (operatorCount >= operandCount) {
				return false;
			}
		} else {
			return false;
		}
	}
	return operandCount > 1 && operandCount == operatorCount + 1;
}
