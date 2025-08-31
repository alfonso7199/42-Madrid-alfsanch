#include "Zombie.hpp"

int main()
{    
    int nzombies;
    
    std::string brain = "HI THIS IS BRAIN";
    std::string *brainPTR = &brain;
    std::string &brainREF = brain;

    std::cout << "Memory address brain: " << &brain << std::endl;
    std::cout << "Memory address brainPTR: " << brainPTR << std::endl;
    std::cout << "Memory address brainREF: " << &brainREF << std::endl;
    
    std::cout << "Value of brain: " << brain << std::endl;
    std::cout << "Value of brainPTR: " << *brainPTR << std::endl;
    std::cout << "Value of brainREF: " << brainREF << std::endl;

    return 0;
}
