#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <climits>

static std::vector<int> insertOrder(int count)
{
	if (count <= 0)
		return std::vector<int>();

	std::vector<int> jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	while (jacobsthal.back() <= count)
	{
		std::size_t last = jacobsthal.size() - 1;
		jacobsthal.push_back(jacobsthal[last] + 2 * jacobsthal[last - 1]);
	}

	std::vector<bool>	used(count, false);
	std::vector<int>	order;

	for (std::size_t i = 0; i + 1 < jacobsthal.size(); ++i)
	{
		int high = std::min(jacobsthal[i + 1] - 1, count);
		int low  = jacobsthal[i];

		for (int n = high; n >= low; --n)
		{
			int idx = n - 1;
			if (idx >= 0 && idx < count && !used[idx])
			{
				used[idx] = true;
				order.push_back(idx);
			}
		}
	}
	return order;
}

static void insertSorted(std::vector<int>& chain, int value, std::vector<int>::iterator bound)
{
	std::vector<int>::iterator low  = chain.begin();
	std::vector<int>::iterator high = bound;

	while (low < high)
	{
		std::vector<int>::iterator mid = low + std::distance(low, high) / 2;
		if (*mid < value)
			low = mid + 1;
		else
			high = mid;
	}
	chain.insert(low, value);
}

static void fordJohnson(std::vector<int>& values)
{
	int size = (int)values.size();
	if (size <= 1)
		return;
	if (size == 2)
	{
		if (values[0] > values[1])
			std::swap(values[0], values[1]);
		return;
	}

	bool	hasExtra  = (size % 2) != 0;
	int		extra     = hasExtra ? values[size - 1] : 0;
	int		pairCount = size / 2;

	std::vector<std::pair<int, int> > pairs(pairCount);
	for (int i = 0; i < pairCount; ++i)
	{
		int a = values[2 * i];
		int b = values[2 * i + 1];
		pairs[i] = (a >= b) ? std::make_pair(a, b) : std::make_pair(b, a);
	}

	std::vector<int> bigger(pairCount);
	for (int i = 0; i < pairCount; ++i)
		bigger[i] = pairs[i].first;
	fordJohnson(bigger);

	std::vector<std::pair<int, int> >	sorted(pairCount);
	std::vector<bool>					matched(pairCount, false);
	for (int i = 0; i < pairCount; ++i)
	{
		for (int j = 0; j < pairCount; ++j)
		{
			if (!matched[j] && pairs[j].first == bigger[i])
			{
				sorted[i] = pairs[j];
				matched[j] = true;
				break;
			}
		}
	}

	std::vector<int> chain;
	chain.push_back(sorted[0].second);
	for (int i = 0; i < pairCount; ++i)
		chain.push_back(sorted[i].first);

	std::vector<int> rest;
	for (int i = 1; i < pairCount; ++i)
		rest.push_back(sorted[i].second);
	if (hasExtra)
		rest.push_back(extra);

	std::vector<int> order = insertOrder((int)rest.size());

	for (std::size_t i = 0; i < order.size(); ++i)
	{
		int idx   = order[i];
		int value = rest[idx];

		std::vector<int>::iterator bound = chain.end();
		if (idx + 1 < pairCount)
			bound = std::lower_bound(chain.begin(), chain.end(), sorted[idx + 1].first);

		insertSorted(chain, value, bound);
	}

	values = chain;
}

static void insertSorted(std::deque<int>& chain, int value, std::deque<int>::iterator bound)
{
	std::deque<int>::iterator low  = chain.begin();
	std::deque<int>::iterator high = bound;

	while (low < high)
	{
		std::deque<int>::iterator mid = low + std::distance(low, high) / 2;
		if (*mid < value)
			low = mid + 1;
		else
			high = mid;
	}
	chain.insert(low, value);
}

static void fordJohnson(std::deque<int>& values)
{
	int size = (int)values.size();
	if (size <= 1)
		return;
	if (size == 2)
	{
		if (values[0] > values[1])
			std::swap(values[0], values[1]);
		return;
	}

	bool	hasExtra  = (size % 2) != 0;
	int		extra     = hasExtra ? values[size - 1] : 0;
	int		pairCount = size / 2;

	std::vector<std::pair<int, int> > pairs(pairCount);
	for (int i = 0; i < pairCount; ++i)
	{
		int a = values[2 * i];
		int b = values[2 * i + 1];
		pairs[i] = (a >= b) ? std::make_pair(a, b) : std::make_pair(b, a);
	}

	std::deque<int> bigger(pairCount);
	for (int i = 0; i < pairCount; ++i)
		bigger[i] = pairs[i].first;
	fordJohnson(bigger);

	std::vector<std::pair<int, int> >	sorted(pairCount);
	std::vector<bool>					matched(pairCount, false);
	for (int i = 0; i < pairCount; ++i)
	{
		for (int j = 0; j < pairCount; ++j)
		{
			if (!matched[j] && pairs[j].first == bigger[i])
			{
				sorted[i] = pairs[j];
				matched[j] = true;
				break;
			}
		}
	}

	std::deque<int> chain;
	chain.push_back(sorted[0].second);
	for (int i = 0; i < pairCount; ++i)
		chain.push_back(sorted[i].first);

	std::vector<int> rest;
	for (int i = 1; i < pairCount; ++i)
		rest.push_back(sorted[i].second);
	if (hasExtra)
		rest.push_back(extra);

	std::vector<int> order = insertOrder((int)rest.size());

	for (std::size_t i = 0; i < order.size(); ++i)
	{
		int idx   = order[i];
		int value = rest[idx];

		std::deque<int>::iterator bound = chain.end();
		if (idx + 1 < pairCount)
			bound = std::lower_bound(chain.begin(), chain.end(), sorted[idx + 1].first);

		insertSorted(chain, value, bound);
	}

	values = chain;
}

PmergeMe::PmergeMe() : _vectorTime(0.0), _dequeTime(0.0) {}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _vector(other._vector), _deque(other._deque),
	  _vectorTime(other._vectorTime), _dequeTime(other._dequeTime) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector     = other._vector;
		_deque      = other._deque;
		_vectorTime = other._vectorTime;
		_dequeTime  = other._dequeTime;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		long				n;
		if (!(iss >> n) || n <= 0 || n > INT_MAX)
			throw std::runtime_error("Error");

		std::string leftover;
		if (iss >> leftover)
			throw std::runtime_error("Error");

		_vector.push_back((int)n);
		_deque.push_back((int)n);
	}
}

void PmergeMe::sortVector()
{
	clock_t start = clock();
	fordJohnson(_vector);
	clock_t end = clock();
	_vectorTime = (double)(end - start) / CLOCKS_PER_SEC * 1e6;
}

void PmergeMe::sortDeque()
{
	clock_t start = clock();
	fordJohnson(_deque);
	clock_t end = clock();
	_dequeTime = (double)(end - start) / CLOCKS_PER_SEC * 1e6;
}

void PmergeMe::sort()
{
	sortVector();
	sortDeque();
}

void PmergeMe::display(bool after) const
{
	std::cout << (after ? "After:  " : "Before: ");
	for (std::size_t i = 0; i < _vector.size(); ++i)
	{
		if (i)
			std::cout << " ";
		std::cout << _vector[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printTimes() const
{
	std::cout << "Time to process a range of " << _vector.size()
		<< " elements with std::vector : " << _vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size()
		<< " elements with std::deque  : " << _dequeTime << " us" << std::endl;
}
