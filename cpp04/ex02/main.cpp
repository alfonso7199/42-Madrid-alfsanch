
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "TEST ABSTRACT CLASS" << std::endl;
	// Si creamos Animal de cualquiera de estas formas falla
	// Animal animal1;
	// Animal* animal1 = new Animal();
	
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << ": ";
	j->makeSound();
	std::cout << i->getType() << ": ";
	i->makeSound();
	delete j;
	delete i;

	std::cout << "ARRAY OF ANIMALS" << std::endl;
	const Animal* animals[10];
	
	for (int i = 0; i < 5; i++)
		animals[i] = new Dog();
	
	for (int i = 5; i < 10; i++)
		animals[i] = new Cat();
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
	}
	
	std::cout << "DELETE" << std::endl;
	for (int i = 0; i < 10; i++)
		delete animals[i];

	std::cout << "DEEP COPY WITH CATS" << std::endl;
	Cat cat1;
	Cat cat2;
	cat2 = cat1;
	std::cout << "Both cats exist, diferent brains" << std::endl;

	return 0;
}
