#ifndef FOOD_HPP
#define FOOD_HPP

#include <string>

/*
The Food class is used to store types of food that can be fed to animals.

Each food has a name, cost, and quantity available.
*/
class Food {
public:
    /*
    The constructor takes the food's name and cost as parameters. These values cannot be changed
    after construction. The quantity property always starts at 0 for a new food type.
    */
    Food(const std::string& new_name, double new_cost, unsigned int new_energy);

    /*
    Return the food's name, e.g. "bananas"
    */
    std::string getName() const;

    /*
    Return the cost per item, in local $.
    */
    double getCost() const;

    /*
    Return the energy content per unit of this food.
    */
    unsigned int getEnergy() const;

    /*
    Return the quantity of the this food available on-hand at the Zoo
    */
    unsigned int getQuantity() const;

    /*
    Use some quantity of food as specified by the `count` parameter. If there is less of the food
    available than requested, consume as much as possible. Returns the quantity of this food
    consumed.
    */
    unsigned int consume(unsigned int count);

	/*
	Purchase more of this food. Increments the class's internal quantity counter by the value of the `count` parameter.
	*/
    void purchase(unsigned int count);
	
private:
	std::string name;
	double cost;
	unsigned int energy;
	unsigned int quant;
};

#endif /* end of include guard: FOOD_HPP */