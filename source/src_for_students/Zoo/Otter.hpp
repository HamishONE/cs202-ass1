#ifndef OTTER_HPP
#define OTTER_HPP

#include "Animal.hpp"

class Otter : public Animal {
public:
    Otter();

    // Overridden  so we can return AT_OTTER
    virtual AnimalType type() const;
    // Overridden to implement the otter's hunger level
    virtual unsigned int hungerLevel() const;
    // Overridden to allow resetting of the otter's hunger at the end of the day
    virtual void resetToHungry();
    // Overridden to indicate which foods the Otter likes
    virtual bool likesFood(const Food& food) const;
    // Overridden to implement feeding behaviour
    virtual unsigned int feed(Food& food);
};

#endif /* end of include guard: ELEPHANT_HPP */