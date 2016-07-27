#include "Snake.hpp"

using namespace std;

Snake::Snake() {
	defaultHunger = 250;
	resetToHungry();
	animalType = AT_SNAKE;
	
	foodsEaten[0] = "mouse";
	foodsEaten[1] = "egg";
	foodsEaten[2] = "";
}