#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern::~Intern()
{
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

AForm* Intern::_createShrubberyCreationForm(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::_createRobotomyRequestForm(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::_createPresidentialPardonForm(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	struct FormMap
	{
		std::string name;
		AForm* (Intern::*creator)(const std::string&) const;
		
		FormMap(const std::string& n, AForm* (Intern::*c)(const std::string&) const)
			: name(n), creator(c) {}
	};

	FormMap forms[] = {
		FormMap("shrubbery creation", &Intern::_createShrubberyCreationForm),
		FormMap("robotomy request", &Intern::_createRobotomyRequestForm),
		FormMap("presidential pardon", &Intern::_createPresidentialPardonForm)
	};

	for (int i = 0; i < 3; i++)
	{
		if (forms[i].name == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*forms[i].creator)(target);
		}
	}

	std::cerr << "Error: Form name \"" << formName << "\" does not exist!" << std::endl;
	return NULL;
}
