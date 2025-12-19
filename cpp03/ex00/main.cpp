#include "ClapTrap.hpp"

int main()
{
	std::cout << "Basic attack"<< std::endl;
	ClapTrap clap1("ClapTrap");
	clap1.attack("Enemy 1");
	
	std::cout << "Damag"<< std::endl;
	ClapTrap clap2("TrapClap");
	clap2.takeDamage(5);
	clap2.attack("Enemy 2");
	
	std::cout << "Repair"<< std::endl;
	ClapTrap clap3("Pepito");
	clap3.takeDamage(8);
	clap3.beRepaired(3);
	clap3.attack("Enemy 3");
	
	std::cout << "No energy"<< std::endl;
	ClapTrap clap4("Pepita");
	for (int i = 0; i < 11; i++)
		clap4.attack("Enemy 4");
	
	std::cout << "No hit points"<< std::endl;
	ClapTrap clap5("Clap");
	clap5.takeDamage(15);
	clap5.attack("Enemy 5");
	clap5.beRepaired(5);
	
	std::cout << "Copy constructor"<< std::endl;
	ClapTrap clap6("Trap");
	ClapTrap clap7(clap6);
	
	std::cout << "Destructors"<< std::endl;
	return 0;
}