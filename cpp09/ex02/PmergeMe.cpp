#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <climits>

static std::vector<int> jacOrder(int n)
{
	if (n <= 0)
		return std::vector<int>();

	std::vector<int> lo;
	lo.push_back(1);
	lo.push_back(3);
	while (lo.back() <= n)
		lo.push_back(lo[lo.size() - 1] + 2 * lo[lo.size() - 2]);

	std::vector<bool>	done(n, false);
	std::vector<int>	order;

	for (std::size_t k = 0; k + 1 < lo.size(); ++k)
	{
		int hi = std::min(lo[k + 1] - 1, n);
		int lb = lo[k];
		for (int p = hi; p >= lb; --p)
		{
			int idx = p - 1;
			if (idx >= 0 && idx < n && !done[idx])
			{
				done[idx] = true;
				order.push_back(idx);
			}
		}
	}
	return order;
}

static void vecBinInsert(std::vector<int>& chain, int val,
	std::vector<int>::iterator bound)
{
	std::vector<int>::iterator lo = chain.begin();
	std::vector<int>::iterator hi = bound;
	while (lo < hi)
	{
		std::vector<int>::iterator mid = lo + std::distance(lo, hi) / 2;
		if (*mid < val)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(lo, val);
}

static void fordJohnsonVec(std::vector<int>& v)
{
	int n = (int)v.size();
	if (n <= 1)
		return;
	if (n == 2)
	{
		if (v[0] > v[1])
			std::swap(v[0], v[1]);
		return;
	}

	bool	hasOdd  = (n % 2) != 0;
	int		oddVal  = hasOdd ? v[n - 1] : 0;
	int		pairCnt = n / 2;

	std::vector<std::pair<int, int> > pairs(pairCnt);
	for (int i = 0; i < pairCnt; ++i)
	{
		int a = v[2 * i];
		int b = v[2 * i + 1];
		pairs[i] = (a >= b) ? std::make_pair(a, b) : std::make_pair(b, a);
	}

	std::vector<int> largers(pairCnt);
	for (int i = 0; i < pairCnt; ++i)
		largers[i] = pairs[i].first;
	fordJohnsonVec(largers);

	std::vector<std::pair<int, int> >	sorted(pairCnt);
	std::vector<bool>					used(pairCnt, false);
	for (int i = 0; i < pairCnt; ++i)
	{
		for (int j = 0; j < pairCnt; ++j)
		{
			if (!used[j] && pairs[j].first == largers[i])
			{
				sorted[i] = pairs[j];
				used[j]   = true;
				break;
			}
		}
	}

	std::vector<int> chain;
	chain.push_back(sorted[0].second);
	for (int i = 0; i < pairCnt; ++i)
		chain.push_back(sorted[i].first);

	std::vector<int> pend;
	for (int i = 1; i < pairCnt; ++i)
		pend.push_back(sorted[i].second);
	if (hasOdd)
		pend.push_back(oddVal);

	int					pendN = (int)pend.size();
	std::vector<int>	order = jacOrder(pendN);

	for (int k = 0; k < (int)order.size(); ++k)
	{
		int idx = order[k];
		int val = pend[idx];

		std::vector<int>::iterator bound = chain.end();
		if (idx + 1 < pairCnt)
			bound = std::lower_bound(chain.begin(), chain.end(), sorted[idx + 1].first);

		vecBinInsert(chain, val, bound);
	}

	v = chain;
}

static void deqBinInsert(std::deque<int>& chain, int val,
	std::deque<int>::iterator bound)
{
	std::deque<int>::iterator lo = chain.begin();
	std::deque<int>::iterator hi = bound;
	while (lo < hi)
	{
		std::deque<int>::iterator mid = lo + std::distance(lo, hi) / 2;
		if (*mid < val)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(lo, val);
}

static void fordJohnsonDeq(std::deque<int>& v)
{
	int n = (int)v.size();
	if (n <= 1)
		return;
	if (n == 2)
	{
		if (v[0] > v[1])
			std::swap(v[0], v[1]);
		return;
	}

	bool	hasOdd  = (n % 2) != 0;
	int		oddVal  = hasOdd ? v[n - 1] : 0;
	int		pairCnt = n / 2;

	std::vector<std::pair<int, int> > pairs(pairCnt);
	for (int i = 0; i < pairCnt; ++i)
	{
		int a = v[2 * i];
		int b = v[2 * i + 1];
		pairs[i] = (a >= b) ? std::make_pair(a, b) : std::make_pair(b, a);
	}

	std::vector<int> largers(pairCnt);
	for (int i = 0; i < pairCnt; ++i)
		largers[i] = pairs[i].first;

	std::vector<int> tmp(largers.begin(), largers.end());
	fordJohnsonVec(tmp);
	for (int i = 0; i < pairCnt; ++i)
		largers[i] = tmp[i];

	std::vector<std::pair<int, int> >	sorted(pairCnt);
	std::vector<bool>					used(pairCnt, false);
	for (int i = 0; i < pairCnt; ++i)
	{
		for (int j = 0; j < pairCnt; ++j)
		{
			if (!used[j] && pairs[j].first == largers[i])
			{
				sorted[i] = pairs[j];
				used[j]   = true;
				break;
			}
		}
	}

	std::deque<int> chain;
	chain.push_back(sorted[0].second);
	for (int i = 0; i < pairCnt; ++i)
		chain.push_back(sorted[i].first);

	std::vector<int> pend;
	for (int i = 1; i < pairCnt; ++i)
		pend.push_back(sorted[i].second);
	if (hasOdd)
		pend.push_back(oddVal);

	int					pendN = (int)pend.size();
	std::vector<int>	order = jacOrder(pendN);

	for (int k = 0; k < (int)order.size(); ++k)
	{
		int idx = order[k];
		int val = pend[idx];

		std::deque<int>::iterator bound = chain.end();
		if (idx + 1 < pairCnt)
			bound = std::lower_bound(chain.begin(), chain.end(), sorted[idx + 1].first);

		deqBinInsert(chain, val, bound);
	}

	for (int i = 0; i < (int)chain.size(); ++i)
		v[i] = chain[i];
}

PmergeMe::PmergeMe() : _vecTime(0.0), _deqTime(0.0) {}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _vec(other._vec), _deq(other._deq),
	  _vecTime(other._vecTime), _deqTime(other._deqTime) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec     = other._vec;
		_deq     = other._deq;
		_vecTime = other._vecTime;
		_deqTime = other._deqTime;
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
		_vec.push_back((int)n);
		_deq.push_back((int)n);
	}
}

void PmergeMe::sortVector()
{
	clock_t start = clock();
	fordJohnsonVec(_vec);
	clock_t end   = clock();
	_vecTime = (double)(end - start) / CLOCKS_PER_SEC * 1e6;
}

void PmergeMe::sortDeque()
{
	clock_t start = clock();
	fordJohnsonDeq(_deq);
	clock_t end   = clock();
	_deqTime = (double)(end - start) / CLOCKS_PER_SEC * 1e6;
}

void PmergeMe::sort()
{
	sortVector();
	sortDeque();
}

void PmergeMe::display(bool after) const
{
	const std::vector<int>& seq = _vec;
	std::cout << (after ? "After:  " : "Before: ");
	for (std::size_t i = 0; i < seq.size(); ++i)
	{
		if (i)
			std::cout << " ";
		std::cout << seq[i];
	}
	std::cout << std::endl;
}

void PmergeMe::printTimes() const
{
	std::cout << "Time to process a range of " << _vec.size()
		<< " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
		<< " elements with std::deque  : " << _deqTime << " us" << std::endl;
}
