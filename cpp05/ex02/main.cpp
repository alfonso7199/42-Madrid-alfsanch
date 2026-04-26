#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0));

	std::cout << "\n ShrubberyCreationForm - Success case" << std::endl;
	try
	{
		Bureaucrat alfon("Alfon", 140);
		ShrubberyCreationForm shrubbery("garden");

		std::cout << shrubbery << std::endl;
		alfon.signForm(shrubbery);
		alfon.executeForm(shrubbery);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n ShrubberyCreationForm - Grade too low to sign" << std::endl;
	try
	{
		Bureaucrat rafa("Rafa", 150);
		ShrubberyCreationForm shrubbery("park");

		std::cout << shrubbery << std::endl;
		rafa.signForm(shrubbery);
		rafa.executeForm(shrubbery);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n ShrubberyCreationForm - Grade too low to execute" << std::endl;
	try
	{
		Bureaucrat carlos("Carlos", 145);
		ShrubberyCreationForm shrubbery("backyard");

		std::cout << shrubbery << std::endl;
		carlos.signForm(shrubbery);
		carlos.executeForm(shrubbery);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n RobotomyRequestForm - Success case" << std::endl;
	try
	{
		Bureaucrat pepita("Pepita", 40);
		RobotomyRequestForm robotomy("John");

		std::cout << robotomy << std::endl;
		pepita.signForm(robotomy);
		pepita.executeForm(robotomy);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n RobotomyRequestForm - Multiple executions (50/50 chance)" << std::endl;
	try
	{
		Bureaucrat pepito("Pepito", 45);
		RobotomyRequestForm robotomy("Jane");

		pepito.signForm(robotomy);
		std::cout << "First execution:" << std::endl;
		pepito.executeForm(robotomy);
		std::cout << "Second execution:" << std::endl;
		pepito.executeForm(robotomy);
		std::cout << "Third execution:" << std::endl;
		pepito.executeForm(robotomy);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n RobotomyRequestForm - Grade too low to execute" << std::endl;
	try
	{
		Bureaucrat nuria("Nuria", 72);
		RobotomyRequestForm robotomy("Bob");

		std::cout << robotomy << std::endl;
		nuria.signForm(robotomy);
		nuria.executeForm(robotomy);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n PresidentialPardonForm - Success case" << std::endl;
	try
	{
		Bureaucrat presidente("Presidente", 5);
		PresidentialPardonForm pardon("Criminal");

		std::cout << pardon << std::endl;
		presidente.signForm(pardon);
		presidente.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n PresidentialPardonForm - Grade too low to sign" << std::endl;
	try
	{
		Bureaucrat funcionario("Funcionario", 30);
		PresidentialPardonForm pardon("Another Criminal");

		std::cout << pardon << std::endl;
		funcionario.signForm(pardon);
		funcionario.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Execute unsigned form" << std::endl;
	try
	{
		Bureaucrat admin("Admin", 1);
		ShrubberyCreationForm shrubbery("unsigned_garden");

		std::cout << shrubbery << std::endl;
		std::cout << "Trying to execute without signing:" << std::endl;
		admin.executeForm(shrubbery);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n President (grade 1) executes all forms" << std::endl;
	try
	{
		Bureaucrat aslan("Aslan", 1);
		ShrubberyCreationForm shrubbery("presidential_garden");
		RobotomyRequestForm robotomy("Political enemy");
		PresidentialPardonForm pardon("Ex-president");

		std::cout << "\nSigning all forms:" << std::endl;
		aslan.signForm(shrubbery);
		aslan.signForm(robotomy);
		aslan.signForm(pardon);

		std::cout << "\nExecuting all forms:" << std::endl;
		aslan.executeForm(shrubbery);
		aslan.executeForm(robotomy);
		aslan.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
