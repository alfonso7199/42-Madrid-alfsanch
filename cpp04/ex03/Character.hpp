#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
#include <ICharacter.hpp>

class Character
{
	protected:
	
	
	public : 
		Character(std::string const &type);
		
		std::string const &getType() const;
		virtual Character *clone() const = 0;
		virtual void use(ICharacter &target);
};

#endif