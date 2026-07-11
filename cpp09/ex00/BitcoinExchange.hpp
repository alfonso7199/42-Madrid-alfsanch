#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_rates;

	void	loadDatabase(const std::string& file);
	bool	isValidDate(const std::string& date) const;
	bool	isValidValue(const std::string& str, double& value) const;

public:
	BitcoinExchange();
	BitcoinExchange(const std::string& file);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	process(const std::string& file) const;
};

#endif
