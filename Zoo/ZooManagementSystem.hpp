#ifndef ZOOMANAGEMENTSYSTEM_HPP
#define ZOOMANAGEMENTSYSTEM_HPP

#include <vector>
#include <string>

#include "Food.hpp"
#include "Animal.hpp"

// Hopefully remove
#include "Monkey.hpp"
#include "Elephant.hpp"
#include "Otter.hpp"
#include "Snake.hpp"
#include "Lion.hpp"

class ZooManagementSystem {
public:
    /*
    The FeedResult enum describes the outcome of an attempted feeding operation.
    - FR_SUCCESS: the feed operation was successful and the animal was completely fed.
    - FR_INVALID_ANIMAL: the animal index was invalid and didn't refer to an animal held by the zoo
    - FR_INVALID_FOOD: the food index was invalid and didn't refer to a food held by the zoo
    - FR_INCOMPATIBLE: the animal won't eat the food it was given
    - FR_EXHAUSTED: the type of food fed to the animal was exhaused, so the animal is still hungry
    
    */
    enum FeedResult {
        FR_SUCCESS,
        FR_INVALID_ANIMAL,
        FR_INVALID_FOOD,
        FR_INCOMPATIBLE,
        FR_EXHAUSTED
    };

    /*
    The ZooManagementSystem constructor; initialize all internal state.
    */
    ZooManagementSystem(double initialBalance);

    /*
    The ZooManagementSystem destructor; be careful to properly destroy all heap-allocated objects
    owned by the ZooManagementSystem here.
    */
    ~ZooManagementSystem();

    /*
    The Author static method should return your UPI, e.g. "mgre411".
    */
    static std::string author();

    /*
    Return the Zoo's current bank balance
    */
    double getBalance() const;

    /*
    Allow visitors to enter the Zoo. Takes the number of Adults and Children in the group, and
    returns the total cost admittance fee.
    */
    double admitVisitors(unsigned int adults, unsigned int children);

    /*
    Return a vector of the types of food the Zoo has access to.
    */
    std::vector<Food> getFood() const;
    
    /*
    Add a new type of food to the food store.
    */
    void addFood(const Food& new_food);

    /*
    Purchase more of a type of food. If the food exists and there is enough money in the balance to
    purchase the requested amount, purchase the food and subtract the total cost from the balance. 
    Returns a boolean value indicating if the transaction was successful (true for successful, 
    false otherwise), and also returns the total cost of the transaction (regardless of whether it 
    was successful or not) via the cost parameter.
    */
    bool purchaseFood(double& cost, unsigned int index, unsigned int quantity);

    /*
    Return a vector of all animals currently held by the Zoo.
    */
    std::vector<Animal*> getAnimals() const;

    /*
    Add an animal by its type name. Returns true if the animal was successfully added, or false
    otherwise. The only reason this method would return false is if the animal type name is invalid.
    */
    bool addAnimal(Animal::AnimalType new_animal_type);

    /*
    Feed an Animal. The input for this method is the index of the animal in the animals vector.
    */
    FeedResult feedAnimal(unsigned int& quantity_eaten, unsigned int animal_index, unsigned int food_index);
    
    /*
    Reset the hunger value of all Animals. This will set the hunger for all animals to the maximum 
    value, which is equal to that Animal's daily food intake requirement. For example, all monkeys
    will have their hunger level reset to 800.
    */
    void resetAllAnimals();
    
    /*
    This method is used for fully automatic feeding behaviour and should be implemented for Task 4.
    */
    void feedAllAnimals();
	
private:
	double balance;
	std::vector<Food> allFoods;
	std::vector<Animal*> allAnimals;
};

#endif /* end of include guard: ZOOMANAGEMENTSYSTEM_HPP */