#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Food;

/*
The Animal class is a pure virtual base class for all Animal classes. It defines the interface
which Animals must implement, and provides some basic functionality all Animal classes will need.
*/
class Animal {
public:
    /*
    An enum to help identify different types of animals. Each animal subclass must have a unique
    enum value which it uses to identify itself.
    */
    enum AnimalType {
        AT_MONKEY = 0,
        AT_LION,
        AT_ELEPHANT,
        AT_SNAKE,
        AT_OTTER,
        // Add any new custom Animal types here
        
        // The invalid animal type, no animal should have this type
        AT_INVALID
    };
    
    /*
    The destructor for any polymorphic base class *must* be declared virtual, otherwise when you
    delete an object through a polymorphic pointer the base class destructor will be called instead
    of the one in the derived class.
    */
    virtual ~Animal();
    
    /*
    Get the name of the type of Animal referred to by each subtype of Animal.

    So for example, the Monkey subclass of Animal would return AT_MONKEY. See the AnimalType enum
    declaration for more information.
    */
    virtual AnimalType type() const;

    /*
	Returns the current hunger level of the animal, measured in the number of kiloJoules (kJ) the animal animal needs to
	eat in the current day. This will be equal to the animal's daily food intake requirement, less the energy value of
	the food the animal has already eaten.
	*/
    virtual unsigned int hungerLevel() const;
    
    /*
    Resets the hunger level of the animal back to its original value, e.g. when a new day starts
    and the animals need to be fed all over again.
    */
    virtual void resetToHungry();
    
    /*
    Indicates whether or not this animal likes the given food. A return value of true means the
    animal will eat the food, but a return value of false means the animal will not eat the food.
    */
    virtual bool likesFood(const Food& food) const;
    
    /*
    Feed some food to an Animal. The animal consumes as many units of the food as it can until the
    food is exhausted or the animal is full. Returns the quantity of food eaten. If the animal
    doesn't like the food provided, none will be eaten.
    */
    virtual unsigned int feed(Food& food);

	unsigned int hunger;
	unsigned int defaultHunger;
	AnimalType animalType;
	std::string foodsEaten[3];
};

#endif /* end of include guard: ANIMAL_HPP */