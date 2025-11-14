/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iostream>

Phonebook::Phonebook(void) : size(0), nextIndex(0)
{
}

void Phonebook::addContact(const Contact &contact)
{
	contacts[nextIndex] = contact;
	if (size < maxContacts)
		size++;
	nextIndex = (nextIndex + 1) % maxContacts;
}

std::string Phonebook::toColumn10(const std::string &s)
{
	if (s.size() <= 10)
		return std::string(10 - s.size(), ' ') + s;
	return s.substr(0, 9) + ".";
}

void Phonebook::printTable() const
{
	std::cout << std::string(4 * 10 + 4, '_') << " " << std::endl;
	std::cout << "|" 
		      << Phonebook::toColumn10("index") << "|"
		      << Phonebook::toColumn10("first name") << "|"
		      << Phonebook::toColumn10("last name") << "|"
		      << Phonebook::toColumn10("nickname") << "|" << std::endl;
	std::cout << "|" << std::string(10, '-') << "|"
		      << std::string(10, '-') << "|"
		      << std::string(10, '-') << "|"
		      << std::string(10, '-') << "|" << std::endl;
	for (int i = 0; i < size; ++i)
	{
		const Contact &c = contacts[i];
		if (c.isEmpty())
			continue;
		std::cout << "|"
			      << Phonebook::toColumn10(std::string(1, '0' + i)) << "|"
			      << Phonebook::toColumn10(c.getFirstName()) << "|"
			      << Phonebook::toColumn10(c.getLastName()) << "|"
			      << Phonebook::toColumn10(c.getNickname()) << "|" << std::endl;
	}
}

bool Phonebook::isValidIndex(int index) const
{
	return index >= 0 && index < size && !contacts[index].isEmpty();
}

void Phonebook::printContactByIndex(int index) const
{
	if (!isValidIndex(index))
	{
		std::cout << "Invalid index" << std::endl;
		return;
	}
	const Contact &c = contacts[index];
	std::cout << "First name: " << c.getFirstName() << std::endl;
	std::cout << "Last name: " << c.getLastName() << std::endl;
	std::cout << "Nickname: " << c.getNickname() << std::endl;
	std::cout << "Phone number: " << c.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret: " << c.getDarkestSecret() << std::endl;
}
