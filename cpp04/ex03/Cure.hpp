#ifndef CURE_HPP
#define CURE_HPP

#include <string>
#include <iostream>
#include <ICharacter.hpp>

class Cure
{
	protected:
	
	
	public : 
		Cure(std::string const &type);
		
		std::string const &getType() const;
		virtual Cure *clone() const = 0;
		virtual void use(ICharacter &target);
};

#endif