#include "Zombie.hpp"

int main()
{    
    int nzombies;
    
    nzombies= 5;
    Zombie* horde = zombieHorde(nzombies, "ZombieHorde");
    for (int i = 0; i < nzombies; i++)
    {
        horde[i].announce();
    }
    delete[] horde;
    return 0;
}
