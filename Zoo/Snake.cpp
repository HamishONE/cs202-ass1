#include "Snake.hpp"

using namespace std;

Snake::Snake() {
	defaultHunger = 250;
	resetToHungry();
	animalType = AT_SNAKE;
	
	foodsEaten.push_back("mouse");
	foodsEaten.push_back("egg");
}