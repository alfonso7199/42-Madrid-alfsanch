#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include <string>

class AForm;

class Intern
{
private:
	AForm*	_createShrubberyCreationForm(const std::string& target) const;
	AForm*	_createRobotomyRequestForm(const std::string& target) const;
	AForm*	_createPresidentialPardonForm(const std::string& target) const;

public:
	Intern();
	Intern(const Intern& other);
	~Intern();

	Intern&	operator=(const Intern& other);

	AForm*	makeForm(const std::string& formName, const std::string& target) const;
};

#endif
