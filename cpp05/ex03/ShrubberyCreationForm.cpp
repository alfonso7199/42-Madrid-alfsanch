#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm(target + "_shrubbery", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

void ShrubberyCreationForm::executeAction() const
{
	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());
	
	if (!file.is_open())
	{
		std::cerr << "Error: Could not create file " << filename << std::endl;
		return;
	}

	file << "       _-_\n"
		 << "    /~~   ~~\\\n"
		 << " /~~         ~~\\\n"
		 << "{                }\n"
		 << " \\  _-     -_  /\n"
		 << "   ~  \\ //  ~\n"
		 << "       V\n"
		 << "\n"
		 << "       _-_\n"
		 << "    /~~   ~~\\\n"
		 << " /~~         ~~\\\n"
		 << "{                }\n"
		 << " \\  _-     -_  /\n"
		 << "   ~  \\ //  ~\n"
		 << "       V\n"
		 << "\n"
		 << "       _-_\n"
		 << "    /~~   ~~\\\n"
		 << " /~~         ~~\\\n"
		 << "{                }\n"
		 << " \\  _-     -_  /\n"
		 << "   ~  \\ //  ~\n"
		 << "       V\n";

	file.close();
	std::cout << "Shrubbery has been planted at " << filename << std::endl;
}
