#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

int RPN::evaluate(const std::string& expr)
{
	while (!_stack.empty())
		_stack.pop();

	std::istringstream	iss(expr);
	std::string			token;

	while (iss >> token)
	{
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
		{
			_stack.push(token[0] - '0');
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error");
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			if (token == "+")
				_stack.push(a + b);
			else if (token == "-")
				_stack.push(a - b);
			else if (token == "*")
				_stack.push(a * b);
			else
			{
				if (b == 0)
					throw std::runtime_error("Error: division by zero");
				_stack.push(a / b);
			}
		}
		else
		{
			throw std::runtime_error("Error");
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	return _stack.top();
}
