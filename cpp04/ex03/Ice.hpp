#ifndef ICE_HPP
#define ICE_HPP

#include <string>
#include <iostream>
#include <ICharacter.hpp>

class Ice
{
	protected:
	
	
	public : 
		Ice(std::string const &type);
		
		std::string const &getType() const;
		virtual Ice *clone() const = 0;
		virtual void use(ICharacter &target);
};

#endif