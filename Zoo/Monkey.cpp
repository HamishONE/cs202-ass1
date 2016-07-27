#include "Monkey.hpp"

using namespace std;

Monkey::Monkey() {
	defaultHunger = 800;
	resetToHungry();
	animalType = AT_MONKEY;
	
	foodsEaten[0] = "banana";
	foodsEaten[1] = "watermelon";
	foodsEaten[2] = "mealworms";
}