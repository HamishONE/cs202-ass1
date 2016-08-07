#ifndef MONKEY_HPP
#define MONKEY_HPP

#include "Animal.hpp"

class Monkey : public Animal {
public:
    Monkey();

    // Overridden so we can return AT_MONKEY
    virtual AnimalType type() const;
    // Overridden to implement the monkey's hunger level
    virtual unsigned int hungerLevel() const;
    // Overridden to allow resetting of the monkey's hunger at the end of the day
    virtual void resetToHungry();
    // Overridden to indicate which foods the Monkey likes
    virtual bool likesFood(const Food& food) const;
    // Overridden to implement feeding behaviour
    virtual unsigned int feed(Food& food);
};

#endif /* end of include guard: MONKEY_HPP */