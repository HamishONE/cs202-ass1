#ifndef LION_HPP
#define LION_HPP

#include "Animal.hpp"

class Lion : public Animal {
public:
    Lion();

    // Overridden  so we can return AT_LION
    virtual AnimalType type() const;
    // Overridden to implement the lion's hunger level
    virtual unsigned int hungerLevel() const;
    // Overridden to allow resetting of the lion's hunger at the end of the day
    virtual void resetToHungry();
    // Overridden to indicate which foods the Lion likes
    virtual bool likesFood(const Food& food) const;
    // Overridden to implement feeding behaviour
    virtual unsigned int feed(Food& food);
};

#endif /* end of include guard: LION_HPP */