#include "Form.hpp"
#include "Bureaucrat.hpp"

const char* Form::GradeTooHighException::what() const throw()
{
	return "Form Exception: Grade too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form Exception: Grade too low!";
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) 
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other) 
	: _name(other._name), _isSigned(other._isSigned), 
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

Form::~Form()
{
}

Form& Form::operator=(const Form& other)
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

const std::string& Form::getName() const
{
	return _name;
}

bool Form::isSigned() const
{
	return _isSigned;
}

int Form::getGradeToSign() const
{
	return _gradeToSign;
}

int Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form \"" << form.getName() << "\", signed: " 
	   << (form.isSigned() ? "yes" : "no") 
	   << ", grade to sign: " << form.getGradeToSign() 
	   << ", grade to execute: " << form.getGradeToExecute() << ".";
	return os;
}
