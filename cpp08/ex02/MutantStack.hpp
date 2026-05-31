#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack() {}

	MutantStack(const MutantStack& other) : std::stack<T>(other) {}

	MutantStack& operator=(const MutantStack& other)
	{
		if (this != &other)
			std::stack<T>::operator=(other);
		return *this;
	}

	~MutantStack() {}

	typedef typename std::stack<T>::container_type::iterator		iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	iterator		begin()			{ return this->c.begin(); }
	iterator		end()			{ return this->c.end(); }
	const_iterator	begin() const	{ return this->c.begin(); }
	const_iterator	end()   const	{ return this->c.end(); }
};

#endif
