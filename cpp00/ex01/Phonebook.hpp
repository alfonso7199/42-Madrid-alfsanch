#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <string>

class Phonebook {
public:
	Phonebook();
	void addContact(const Contact &contact);
	void printTable() const;
	bool isValidIndex(int index) const;
	void printContactByIndex(int index) const;
private:
	static const int maxContacts = 8;
	Contact contacts[maxContacts];
	int size;
	int nextIndex;
	static std::string toColumn10(const std::string &s);
};

#endif


