#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& file)
{
	loadDatabase(file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& file)
{
	std::ifstream in(file.c_str());
	if (!in.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(in, line);
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;
		std::size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = line.substr(0, comma);
		double rate = std::strtod(line.substr(comma + 1).c_str(), NULL);
		_rates[date] = rate;
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

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (month == 2 && leapYear)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		return false;

	return true;
}

bool BitcoinExchange::isValidValue(const std::string& str, double& value) const
{
	if (str.empty())
		return false;
	char* end;
	value = std::strtod(str.c_str(), &end);
	if (end == str.c_str() || *end != '\0')
		return false;
	return true;
}

void BitcoinExchange::process(const std::string& file) const
{
	std::ifstream in(file.c_str());
	if (!in.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(in, line);
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;

		std::size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, sep);
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

		std::map<std::string, double>::const_iterator it = _rates.upper_bound(date);
		if (it == _rates.begin())
		{
			std::cerr << "Error: no date found for " << date << std::endl;
			continue;
		}
		--it;

		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
	}
}
