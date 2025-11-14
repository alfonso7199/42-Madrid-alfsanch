/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iostream>
#include <string>

static std::string readNonEmptyLine(const std::string &prompt)
{
	std::string line;
	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, line))
			return std::string();
		if (!line.empty())
			return line;
		std::cout << "Write something" << std::endl;
	}
}

static bool parseIndex(const std::string &s, int &out)
{
	if (s.empty()) return false;
	for (size_t i = 0; i < s.size(); ++i)
		if (s[i] < '0' || s[i] > '9') return false;
	long val = 0;
	for (size_t i = 0; i < s.size(); ++i)
		val = val * 10 + (s[i] - '0');
	out = static_cast<int>(val);
	return true;
}

int main()
{
	Phonebook phonebook;
	std::string cmd;

	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, cmd))
			break;
		if (cmd == "EXIT")
			break;
		else if (cmd == "ADD")
		{
			Contact c;
			c.setFirstName(readNonEmptyLine("First name: "));
			c.setLastName(readNonEmptyLine("Last name: "));
			c.setNickname(readNonEmptyLine("Nickname: "));
			c.setPhoneNumber(readNonEmptyLine("Phone number: "));
			c.setDarkestSecret(readNonEmptyLine("Darkest secret: "));
			if (!c.getFirstName().empty() && !c.getLastName().empty() && !c.getNickname().empty()
				&& !c.getPhoneNumber().empty() && !c.getDarkestSecret().empty())
				phonebook.addContact(c);
			else
				std::cout << "No empty fields allowed" << std::endl;
		}
		else if (cmd == "SEARCH")
		{
			phonebook.printTable();
			std::string sidx;
			std::cout << "Index to display: ";
			if (!std::getline(std::cin, sidx)) break;
			int idx = -1;
			if (!parseIndex(sidx, idx) || !phonebook.isValidIndex(idx))
				std::cout << "Invalid index." << std::endl;
			else
				phonebook.printContactByIndex(idx);
		}
		else
		{
			std::cout << "Unrecognized command." << std::endl;
		}
	}
	return 0;
}
