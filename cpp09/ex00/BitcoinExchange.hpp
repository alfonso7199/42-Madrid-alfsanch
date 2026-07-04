#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_db;

	void	loadDb(const std::string& dbFile);
	bool	isValidDate(const std::string& date) const;
	bool	isValidValue(const std::string& raw, double& out) const;

public:
	BitcoinExchange();
	BitcoinExchange(const std::string& dbFile);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	process(const std::string& inputFile) const;
};

#endif
