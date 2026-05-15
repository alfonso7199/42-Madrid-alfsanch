#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cmath>
#include <limits>

static bool isCharLiteral(const std::string& s)
{
	return s.length() == 1 && !std::isdigit(s[0]);
}

static bool isPseudoFloat(const std::string& s)
{
	return s == "nanf" || s == "+inff" || s == "-inff";
}

static bool isPseudoDouble(const std::string& s)
{
	return s == "nan" || s == "+inf" || s == "-inf";
}

static bool isFloat(const std::string& s)
{
	if (s.empty()) return false;
	std::size_t start = 0;
	if (s[0] == '+' || s[0] == '-') ++start;
	bool hasDot   = false;
	bool hasDigit = false;
	for (std::size_t i = start; i < s.length() - 1; ++i)
	{
		if (s[i] == '.')      { if (hasDot) return false; hasDot = true; }
		else if (std::isdigit(s[i])) hasDigit = true;
		else return false;
	}
	return hasDot && hasDigit && s[s.length() - 1] == 'f';
}

static bool isDouble(const std::string& s)
{
	if (s.empty()) return false;
	std::size_t start = 0;
	if (s[0] == '+' || s[0] == '-') ++start;
	bool hasDot   = false;
	bool hasDigit = false;
	for (std::size_t i = start; i < s.length(); ++i)
	{
		if (s[i] == '.')      { if (hasDot) return false; hasDot = true; }
		else if (std::isdigit(s[i])) hasDigit = true;
		else return false;
	}
	return hasDot && hasDigit;
}

static bool isInt(const std::string& s)
{
	if (s.empty()) return false;
	std::size_t start = 0;
	if (s[0] == '+' || s[0] == '-') ++start;
	if (start == s.length()) return false;
	for (std::size_t i = start; i < s.length(); ++i)
		if (!std::isdigit(s[i])) return false;
	return true;
}

static void printChar(double d)
{
	if (std::isnan(d) || std::isinf(d))
		std::cout << "char: impossible" << std::endl;
	else if (d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(d)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d)
{
	if (std::isnan(d) || std::isinf(d))
		std::cout << "int: impossible" << std::endl;
	else if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
}

static void printFloat(double d)
{
	if (std::isnan(d))       std::cout << "float: nanf" << std::endl;
	else if (std::isinf(d))  std::cout << "float: " << (d > 0 ? "+inff" : "-inff") << std::endl;
	else
	{
		float f = static_cast<float>(d);
		std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;
	}
}

static void printDouble(double d)
{
	if (std::isnan(d))       std::cout << "double: nan" << std::endl;
	else if (std::isinf(d))  std::cout << "double: " << (d > 0 ? "+inf" : "-inf") << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
	double d = 0.0;

	if (isCharLiteral(literal))
	{
		d = static_cast<double>(literal[0]);
	}
	else if (isPseudoFloat(literal) || isPseudoDouble(literal))
	{
		if (literal == "nanf"  || literal == "nan")   d = std::numeric_limits<double>::quiet_NaN();
		else if (literal == "+inff" || literal == "+inf") d =  std::numeric_limits<double>::infinity();
		else                                               d = -std::numeric_limits<double>::infinity();
	}
	else if (isFloat(literal))
	{
		d = static_cast<double>(std::strtof(literal.c_str(), NULL));
	}
	else if (isDouble(literal))
	{
		d = std::strtod(literal.c_str(), NULL);
	}
	else if (isInt(literal))
	{
		errno = 0;
		long l = std::strtol(literal.c_str(), NULL, 10);
		if (errno == ERANGE || l > INT_MAX || l < INT_MIN)
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		d = static_cast<double>(l);
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
