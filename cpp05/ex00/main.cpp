#include "Bureaucrat.hpp"

int main()
{
	std::cout << "Crete Bureaucrats valids" << std::endl;
	try
	{
		Bureaucrat alfonso("Alfonso", 1);
		std::cout << alfonso << std::endl;

		Bureaucrat rafa("Rafa", 75);
		std::cout << rafa << std::endl;

		Bureaucrat nuria("Nuria", 150);
		std::cout << nuria << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Bureaucrat with grade too high < 1" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid, too high", 0);
		std::cout << invalid << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\nCreate Bureaucrat with grade too low > 150 ===" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid, too Low", 151);
		std::cout << invalid << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Incrementing grades" << std::endl;
	try
	{
		Bureaucrat alfon("Alfon", 5);
		std::cout << "Initial: " << alfon << std::endl;
		alfon.incrementGrade();
		std::cout << "After increment: " << alfon << std::endl;
		alfon.incrementGrade();
		std::cout << "After another increment: " << alfon << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Incrementing to the limit, grade 1" << std::endl;
	try
	{
		Bureaucrat pepita("Pepita", 2);
		std::cout << "Initial: " << pepita << std::endl;
		pepita.incrementGrade();
		std::cout << "After increment (now grade 1): " << pepita << std::endl;
		std::cout << "Trying to increment one more time..." << std::endl;
		pepita.incrementGrade();
		std::cout << pepita << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Decrementing grades" << std::endl;
	try
	{
		Bureaucrat pepito("Pepito", 145);
		std::cout << "Initial: " << pepito << std::endl;
		pepito.decrementGrade();
		std::cout << "After decrement: " << pepito << std::endl;
		pepito.decrementGrade();
		std::cout << "After another decrement: " << pepito << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n Decrementing to the limit, 150" << std::endl;
	try
	{
		Bureaucrat pepito2("Pepito2", 149);
		std::cout << "Initial: " << pepito2 << std::endl;
		pepito2.decrementGrade();
		std::cout << "After decrement (now grade 150): " << pepito2 << std::endl;
		std::cout << "Trying to decrement one more time..." << std::endl;
		pepito2.decrementGrade();
		std::cout << pepito2 << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
