#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
	double				_vecTime;
	double				_deqTime;

	void	sortVector();
	void	sortDeque();

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void	parseInput(int argc, char** argv);
	void	sort();
	void	display(bool after) const;
	void	printTimes() const;
};

#endif
