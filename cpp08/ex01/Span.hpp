#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>
# include <iterator>

class Span
{
private:
	unsigned int		_max;
	std::vector<int>	_data;

public:
	Span();
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void	addNumber(int n);

	template <typename Iterator>
	void	addRange(Iterator begin, Iterator end)
	{
		std::size_t count = static_cast<std::size_t>(std::distance(begin, end));
		if (_data.size() + count > _max)
			throw std::overflow_error("Span: not enough capacity");
		_data.insert(_data.end(), begin, end);
	}

	int	shortestSpan() const;
	int	longestSpan() const;
};

#endif
