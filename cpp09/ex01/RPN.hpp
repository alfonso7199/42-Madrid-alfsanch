#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

class RPN
{
private:
	std::stack<int>	_stack;

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	int	evaluate(const std::string& expr);
};

#endif
