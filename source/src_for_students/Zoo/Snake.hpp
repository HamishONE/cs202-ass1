#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Animal.hpp"

class Snake : public Animal {
public:
    Snake();

    // Overridden  so we can return AT_SNAKE
    virtual AnimalType type() const;
    // Overridden to implement the snake's hunger level
    virtual unsigned int hungerLevel() const;
    // Overridden to allow resetting of the snake's hunger at the end of the day
    virtual void resetToHungry();
    // Overridden to indicate which foods the Snake likes
    virtual bool likesFood(const Food& food) const;
    // Overridden to implement feeding behaviour
    virtual unsigned int feed(Food& food);

protected:
    unsigned int hunger_level;
};

#endif /* end of include guard: SNAKE_HPP */