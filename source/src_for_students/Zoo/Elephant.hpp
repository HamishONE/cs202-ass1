#ifndef ELEPHANT_HPP
#define ELEPHANT_HPP

#include "Animal.hpp"

class Elephant : public Animal {
public:
    Elephant();

    // Overridden  so we can return AT_ELEPHANT
    virtual AnimalType type() const;
    // Overridden to implement the elephant's hunger level
    virtual unsigned int hungerLevel() const;
    // Overridden to allow resetting of the elephant's hunger at the end of the day
    virtual void resetToHungry();
    // Overridden to indicate which foods the Elephant likes
    virtual bool likesFood(const Food& food) const;
    // Overridden to implement feeding behaviour
    virtual unsigned int feed(Food& food);
};

#endif /* end of include guard: ELEPHANT_HPP */