#include "AForm.hpp"
#include "Bureaucrat.hpp"

// Exception implementations
const char* AForm::GradeTooHighException::what() const throw()
{
	return "AForm Exception: Grade too high!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "AForm Exception: Grade too low!";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "AForm Exception: Form is not signed!";
}

// AForm implementation
AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute) 
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other) 
	: _name(other._name), _isSigned(other._isSigned), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm::~AForm()
{
}

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
	{
		const_cast<std::string&>(_name) = other._name;
		_isSigned = other._isSigned;
		const_cast<int&>(_gradeToSign) = other._gradeToSign;
		const_cast<int&>(_gradeToExecute) = other._gradeToExecute;
	}
	return *this;
}

const std::string& AForm::getName() const
{
	return _name;
}

bool AForm::isSigned() const
{
	return _isSigned;
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const
{
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooLowException();
	executeAction();
}

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << "AForm \"" << form.getName() << "\", signed: " 
	   << (form.isSigned() ? "yes" : "no") 
	   << ", grade to sign: " << form.getGradeToSign() 
	   << ", grade to execute: " << form.getGradeToExecute() << ".";
	return os;
}
