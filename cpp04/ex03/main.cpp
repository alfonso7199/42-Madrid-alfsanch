#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include <iostream>

int main()
{
    std::cout << "SUBJECT TEST" << std::endl;
    {
        IMateriaSource *src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        
        ICharacter *me = new Character("pepito");
        AMateria *tmp;
        tmp = src->createMateria("ice");
        me->equip(tmp);
        tmp = src->createMateria("cure");
        me->equip(tmp);
        
        ICharacter *bob = new Character("pepita");
        
        me->use(0, *bob);
        me->use(1, *bob);
        
        delete bob;
        delete me;
        delete src;
    }
    
    std::cout << "iNVENTARIO" << std::endl;
    {
        IMateriaSource *src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        
        ICharacter *hero = new Character("heroe");
        AMateria *tmp;
        
        for (int i = 0; i < 4; i++)
        {
            tmp = src->createMateria("ice");
            hero->equip(tmp);
            std::cout << "Equipped slot " << i << std::endl;
        }
        
        tmp = src->createMateria("cure");
        hero->equip(tmp);
        std::cout << "Tried to equip 5th materia" << std::endl;
        delete tmp;
        
        delete hero;
        delete src;
    }
    
    std::cout << "DESEQUIPAR INVENTARIO" << std::endl;
    {
        IMateriaSource *src = new MateriaSource();
        src->learnMateria(new Ice());
        
        ICharacter *hero = new Character("heroe");
        ICharacter *target = new Character("enemigp");
        
        AMateria *tmp = src->createMateria("ice");
        hero->equip(tmp);
        
        hero->use(0, *target);
        
        AMateria *floor = tmp;
        hero->unequip(0);
        
        hero->use(0, *target);
        
        delete floor;
        delete target;
        delete hero;
        delete src;
    }
    
    std::cout << "COPIA" << std::endl;
    {
        IMateriaSource *src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        
        Character *original = new Character("original");
        AMateria *tmp;
        tmp = src->createMateria("ice");
        original->equip(tmp);
        tmp = src->createMateria("cure");
        original->equip(tmp);
        
        Character *copy = new Character(*original);
        
        ICharacter *target = new Character("target");
        
        std::cout << "Original uses:" << std::endl;
        original->use(0, *target);
        original->use(1, *target);
        
        std::cout << "Copy uses:" << std::endl;
        copy->use(0, *target);
        copy->use(1, *target);
        
        delete target;
        delete copy;
        delete original;
        delete src;
    }
    
    return 0;
}
