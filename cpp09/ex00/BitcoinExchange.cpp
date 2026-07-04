#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
	loadDb(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDb(const std::string& dbFile)
{
	std::ifstream f(dbFile.c_str());
	if (!f.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(f, line);
	while (std::getline(f, line))
	{
		if (line.empty())
			continue;
		std::size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = line.substr(0, comma);
		std::string rateStr = line.substr(comma + 1);
		double rate = std::strtod(rateStr.c_str(), NULL);
		_db[date] = rate;
	}
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& raw, double& out) const
{
	if (raw.empty())
		return false;
	char* end;
	double val = std::strtod(raw.c_str(), &end);
	if (end == raw.c_str() || *end != '\0')
		return false;
	out = val;
	return true;
}

void BitcoinExchange::process(const std::string& inputFile) const
{
	std::ifstream f(inputFile.c_str());
	if (!f.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(f, line);
	while (std::getline(f, line))
	{
		if (line.empty())
			continue;

		std::size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date     = line.substr(0, sep);
		std::string valueStr = line.substr(sep + 3);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		double value = 0.0;
		if (!isValidValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0.0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000.0)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		std::map<std::string, double>::const_iterator it = _db.upper_bound(date);
		if (it == _db.begin())
		{
			std::cerr << "Error: no date found for " << date << std::endl;
			continue;
		}
		--it;

		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	}
}
