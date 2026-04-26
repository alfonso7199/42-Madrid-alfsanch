#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0));

	std::cout << "\n Intern creates ShrubberyCreationForm" << std::endl;
	try
	{
		Intern someIntern;
		AForm* form;
		form = someIntern.makeForm("shrubbery creation", "garden");
		if (form)
		{
			std::cout << *form << std::endl;
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates RobotomyRequestForm" << std::endl;
	try
	{
		Intern someIntern;
		AForm* form;
		form = someIntern.makeForm("robotomy request", "Bender");
		if (form)
		{
			std::cout << *form << std::endl;
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates PresidentialPardonForm" << std::endl;
	try
	{
		Intern someIntern;
		AForm* form;
		form = someIntern.makeForm("presidential pardon", "Criminal");
		if (form)
		{
			std::cout << *form << std::endl;
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates invalid form" << std::endl;
	try
	{
		Intern someIntern;
		AForm* form;
		form = someIntern.makeForm("invalid form", "target");
		if (form)
		{
			std::cout << *form << std::endl;
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates form and bureaucrat uses it" << std::endl;
	try
	{
		Intern someIntern;
		Bureaucrat alfon("Alfon", 140);
		AForm* form;
		
		form = someIntern.makeForm("shrubbery creation", "park");
		if (form)
		{
			alfon.signForm(*form);
			alfon.executeForm(*form);
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates robotomy form and bureaucrat uses it" << std::endl;
	try
	{
		Intern someIntern;
		Bureaucrat pepita("Pepita", 40);
		AForm* form;
		
		form = someIntern.makeForm("robotomy request", "John");
		if (form)
		{
			pepita.signForm(*form);
			pepita.executeForm(*form);
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Intern creates pardon form and bureaucrat uses it" << std::endl;
	try
	{
		Intern someIntern;
		Bureaucrat presidente("Presidente", 5);
		AForm* form;
		
		form = someIntern.makeForm("presidential pardon", "Prisoner");
		if (form)
		{
			presidente.signForm(*form);
			presidente.executeForm(*form);
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Multiple forms created by intern" << std::endl;
	try
	{
		Intern someIntern;
		Bureaucrat admin("Admin", 1);
		AForm* form1;
		AForm* form2;
		AForm* form3;
		
		form1 = someIntern.makeForm("shrubbery creation", "home");
		form2 = someIntern.makeForm("robotomy request", "Robot");
		form3 = someIntern.makeForm("presidential pardon", "Villain");
		
		if (form1 && form2 && form3)
		{
			admin.signForm(*form1);
			admin.signForm(*form2);
			admin.signForm(*form3);
			
			admin.executeForm(*form1);
			admin.executeForm(*form2);
			admin.executeForm(*form3);
			
			delete form1;
			delete form2;
			delete form3;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Case sensitivity test - wrong form name" << std::endl;
	try
	{
		Intern someIntern;
		AForm* form;
		form = someIntern.makeForm("Shrubbery Creation", "test");
		if (form)
		{
			delete form;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
