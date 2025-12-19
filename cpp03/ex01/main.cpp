#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	std::cout << "CLAPTRAP"<< std::endl;

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
	
	std::cout <<"Copy constructor"<< std::endl;
	ClapTrap clap6("Trap");
	ClapTrap clap7(clap6);


	std::cout << "\nSCAVTRAP" << std::endl;

	std::cout <<"ScavTrap creation"<< std::endl;
	ScavTrap scav1("Scav 1");
	
	std::cout <<"ScavTrap attack"<< std::endl;
	scav1.attack("Enemy 2");
	
	std::cout <<"ScavTrap guard Gate"<< std::endl;
	scav1.guardGate();
	
	std::cout <<"ScavTrap taking damage"<< std::endl;
	scav1.takeDamage(30);
	scav1.attack("Enemy 3");
	
	std::cout <<"ScavTrap repair"<< std::endl;
	scav1.beRepaired(20);
	
	std::cout <<"ScavTrap copy constructor"<< std::endl;
	ScavTrap scav2(scav1);
	scav2.guardGate();
	
	std::cout <<"Destructors"<< std::endl;
	return 0;
}