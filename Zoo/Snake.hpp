#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Animal.hpp"

class Snake : public Animal {
public:
    Snake();
protected:
    unsigned int hunger_level;
};

#endif /* end of include guard: SNAKE_HPP */