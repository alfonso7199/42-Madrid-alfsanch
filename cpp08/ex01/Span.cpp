#include "Span.hpp"
#include <climits>

Span::Span() : _max(0) {}

Span::Span(unsigned int n) : _max(n) {}

Span::Span(const Span& other) : _max(other._max), _data(other._data) {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_max  = other._max;
		_data = other._data;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
	if (_data.size() >= _max)
		throw std::overflow_error("Span: already full");
	_data.push_back(n);
}

long Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw std::logic_error("Span: need at least 2 numbers");

	std::vector<int> sorted(_data);
	std::sort(sorted.begin(), sorted.end());

	long shortest = static_cast<long>(INT_MAX) - static_cast<long>(INT_MIN);
	for (std::size_t i = 1; i < sorted.size(); ++i)
	{
		long diff = static_cast<long>(sorted[i]) - static_cast<long>(sorted[i - 1]);
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

long Span::longestSpan() const
{
	if (_data.size() < 2)
		throw std::logic_error("Span: need at least 2 numbers");

	int minVal = *std::min_element(_data.begin(), _data.end());
	int maxVal = *std::max_element(_data.begin(), _data.end());
	return static_cast<long>(maxVal) - static_cast<long>(minVal);
}
