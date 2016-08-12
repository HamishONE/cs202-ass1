#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS

// include headers for classes being tested
#include "Zoo/Food.hpp"
#if defined(ENABLE_T2_TESTS) || defined(ENABLE_T3_TESTS) || defined(ENABLE_T4_TESTS)
#include "Zoo/Monkey.hpp"
#include "Zoo/Lion.hpp"
#include "Zoo/Elephant.hpp"
#include "Zoo/Snake.hpp"
#include "Zoo/Otter.hpp"
#endif /*ENABLE_T2_TESTS*/
#if defined(ENABLE_T3_TESTS) || defined(ENABLE_T4_TESTS)
#include "Zoo/ZooManagementSystem.hpp"
#endif /*ENABLE_T3_TESTS*/

using namespace std;

// This sigma value is the acceptable range of error for floating point (double) calculations
const double SIGMA = 0.001;

/*
The outcome of each test case is described by this enum, which should make the result more obvious
than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
Helper macro to eliminate a lot of of code repetition. Macros aren't the best, but this is an easy
way to get what we want.
*/

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

/*
Helper macro to simplify the checking of double values against expected results. Directly comparing
values would result in brittle tests, so we have to instead check if the value we got is acceptably
close to the expected value.
*/
#define EXPECT_SIGMA(value, expected)                                                                            \
    {                                                                                                            \
        double value_eval = value;                                                                               \
        double expected_eval = expected;                                                                         \
        if (value_eval <= (expected_eval - SIGMA) || value_eval > (expected_eval + SIGMA)) {                     \
            cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                                           \
                 << "\tFloating-point value " << value_eval << " differed from expected value " << expected_eval \
                 << " by more than " << SIGMA << endl;                                                           \
            return TR_FAIL;                                                                                      \
        }                                                                                                        \
    }
/*
Test creating an instance of the Food class creates it with the correct name and cost, and that the
getName() and getCost() methods work properly.
*/
TestResult test_FoodNameCost() {
    Food banana("banana", 4.50, 250);
    ASSERT(banana.getName() == "banana");
    EXPECT_SIGMA(banana.getCost(), 4.50);
    ASSERT(banana.getEnergy() == 250);

    Food hay("hay", 2.00, 960);
    ASSERT(hay.getName() == "hay");
    EXPECT_SIGMA(hay.getCost(), 2.00);
    ASSERT(hay.getEnergy() == 960);

    return TR_PASS;
}

/*
Test Food quantity is initially set to 0.
*/
TestResult test_FoodQuantity() {
    Food banana("banana", 4.50, 250);
    ASSERT(banana.getQuantity() == 0);

    return TR_PASS;
}

/*
Test Food Purchasing works properly.
*/
TestResult test_FoodPurchase() {
    Food banana("banana", 4.50, 250);
    banana.purchase(4);
    ASSERT(banana.getQuantity() == 4);
    banana.purchase(3);
    ASSERT(banana.getQuantity() == 7);

    return TR_PASS;
}

/*
Test Food Consumption works properly.
*/
TestResult test_FoodConsume() {
    Food banana("banana", 4.50, 250);
    banana.purchase(10);
    ASSERT(banana.getQuantity() == 10);
    // Eat 3
    ASSERT(banana.consume(3) == 3);
    ASSERT(banana.getQuantity() == 7);
    // Eat 4
    ASSERT(banana.consume(4) == 4);
    ASSERT(banana.getQuantity() == 3);

    return TR_PASS;
}

#ifdef ENABLE_T2_TESTS
/*
Test the behavior of the Monkey class. This test doesn't test feeding behavior.
*/
TestResult test_Monkey() {
    Animal* monkey = new Monkey();
    ASSERT(monkey->type() == Animal::AT_MONKEY);
    ASSERT(monkey->hungerLevel() == 800);
    ASSERT(monkey->likesFood(Food("banana", 0, 0)));
    ASSERT(monkey->likesFood(Food("mealworms", 0, 0)));
    ASSERT(monkey->likesFood(Food("watermelon", 0, 0)));
    ASSERT(!monkey->likesFood(Food("hay", 0, 0)));
    delete monkey;

    return TR_PASS;
}

/*
Test the behavior of the Lion class. This test doesn't test feeding behavior.
*/
TestResult test_Lion() {
    Animal* lion = new Lion();
    ASSERT(lion->type() == Animal::AT_LION);
    ASSERT(lion->hungerLevel() == 2200);
    ASSERT(lion->likesFood(Food("steak", 0, 0)));
    ASSERT(lion->likesFood(Food("mouse", 0, 0)));
    ASSERT(lion->likesFood(Food("fish", 0, 0)));
    ASSERT(!lion->likesFood(Food("mealworms", 0, 0)));
    delete lion;

    return TR_PASS;
}

/*
Test the behavior of the Elephant class. This test doesn't test feeding behavior.
*/
TestResult test_Elephant() {
    Animal* elephant = new Elephant();
    ASSERT(elephant->type() == Animal::AT_ELEPHANT);
    ASSERT(elephant->hungerLevel() == 8400);
    ASSERT(elephant->likesFood(Food("banana", 0, 0)));
    ASSERT(elephant->likesFood(Food("hay", 0, 0)));
    ASSERT(elephant->likesFood(Food("watermelon", 0, 0)));
    ASSERT(!elephant->likesFood(Food("mouse", 0, 0)));
    delete elephant;

    return TR_PASS;
}

/*
Test the behavior of the Snake class. This test doesn't test feeding behavior.
*/
TestResult test_Snake() {
    Animal* snake = new Snake();
    ASSERT(snake->type() == Animal::AT_SNAKE);
    ASSERT(snake->hungerLevel() == 250);
    ASSERT(snake->likesFood(Food("mouse", 0, 0)));
    ASSERT(snake->likesFood(Food("egg", 0, 0)));
    ASSERT(!snake->likesFood(Food("hay", 0, 0)));
    delete snake;

    return TR_PASS;
}

/*
Test the behavior of the Otter class. This test doesn't test feeding behavior.
*/
TestResult test_Otter() {
    Animal* otter = new Otter();
    ASSERT(otter->type() == Animal::AT_OTTER);
    ASSERT(otter->hungerLevel() == 750);
    ASSERT(otter->likesFood(Food("fish", 0, 0)));
    ASSERT(otter->likesFood(Food("mouse", 0, 0)));
    ASSERT(!otter->likesFood(Food("watermelon", 0, 0)));
    delete otter;

    return TR_PASS;
}
#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
/*
Check the student has implemented some return value for the ZooManagementSystem::Author() static
method. Doesn't check if the value is a valid UPI, just that something of about the right size is
returned.
*/
TestResult test_UPI() {
    string upi = ZooManagementSystem::author();

    // UPIs should be at least 4 characters long
    ASSERT(upi.size() >= 4);
    // First character should be alphabetic
    ASSERT(isalpha(upi[0]));
    // Last 3 characters should be numeric
    ASSERT(isdigit(upi[upi.size() - 1]));
    ASSERT(isdigit(upi[upi.size() - 2]));
    ASSERT(isdigit(upi[upi.size() - 3]));

    // If nothing went wrong, the test passed
    return TR_PASS;
}

/*
Test the ZooManagementSystem is constructed correctly and that all the getter methods return the
expected initial values.
*/
TestResult test_ZMSConstruction() {
    // Create a ZMS with a zero balance
    ZooManagementSystem zms(0.0);

    EXPECT_SIGMA(zms.getBalance(), 0.0);
    vector<Animal*> animals = zms.getAnimals();
    ASSERT(animals.size() == 0);
    vector<Food> food = zms.getFood();
    ASSERT(food.size() == 0);

    // If nothing went wrong, the test passed
    return TR_PASS;
}

/*
Test the ZooManagementSystem is constructed with the correct balance and that fetching the balance
works correctly.
*/
TestResult test_InitialBalance() {
    {
        // Create a ZMS with a nonzero balance
        ZooManagementSystem zms(100.78);

        EXPECT_SIGMA(zms.getBalance(), 100.78);
    }

    {
        // Create a ZMS with a zero balance.
        ZooManagementSystem zms(0.0);

        EXPECT_SIGMA(zms.getBalance(), 0.0);
    }

    // If nothing went wrong, the test passed
    return TR_PASS;
}

/*
Test the admission of visitors to the Zoo. The ZooManagementSystem should return the correct total
cost for a group of visitors, and modify the Zoo's balance accordingly.
*/
TestResult test_Visitors() {
    {
        // Test with just adults
        ZooManagementSystem zms(0.0);

        EXPECT_SIGMA(zms.getBalance(), 0.0);
        EXPECT_SIGMA(zms.admitVisitors(3, 0), 42.0);
        EXPECT_SIGMA(zms.getBalance(), 42.0);
    }
    {
        // Test with adults and children
        ZooManagementSystem zms(100.0);
        EXPECT_SIGMA(zms.getBalance(), 100.0);
        EXPECT_SIGMA(zms.admitVisitors(2, 3), 35.0);
        EXPECT_SIGMA(zms.getBalance(), 135.0);
    }
    return TR_PASS;
}

/*
Test the addition of animals to the ZMS. Note that this only tests one type of animal; you should
extend it or add more tests to test that all types of animals can be added.
*/
TestResult test_AddAnimals() {
    ZooManagementSystem zms(100.0);

    vector<Animal*> animals = zms.getAnimals();
    ASSERT(animals.size() == 0);
    zms.addAnimal(Animal::AT_MONKEY);
    animals = zms.getAnimals();
    ASSERT(animals.size() == 1);
    ASSERT(animals[0]->type() == Animal::AT_MONKEY);

    return TR_PASS;
}

/*
Test the addition of food types to the ZMS. Note that this only tests one type of food; you should
extend it or add more tests to test different types of food.
*/
TestResult test_AddFood() {
    ZooManagementSystem zms(0.0);
    vector<Food> food = zms.getFood();
    ASSERT(food.size() == 0);

    // Add some food
    zms.addFood(Food("banana", 4.50, 250));
    food = zms.getFood();

    ASSERT(food.size() == 1);
    ASSERT(food[0].getName() == "banana");
    EXPECT_SIGMA(food[0].getCost(), 4.50);
    ASSERT(food[0].getEnergy() == 250);

    return TR_PASS;
}

/*
Tests the purchasing of additional food. This test assumes that we only try to purchase food when
there is enough money in the balance and the food index is valid: it would be wise to write
additional tests to check what happens when these conditions are not true.
*/
TestResult test_PurchaseFood() {
    ZooManagementSystem zms(1000.0);
    zms.addFood(Food("banana", 4.50, 250));

    // Purchase some food
    double cost;
    ASSERT(zms.purchaseFood(cost, 0, 5));
    vector<Food> food = zms.getFood();
    EXPECT_SIGMA(cost, 4.5 * 5);
    EXPECT_SIGMA(zms.getBalance(), 1000.0 - cost);
    ASSERT(food[0].getQuantity() == 5);

    return TR_PASS;
}

/*
Tests a simple case of feeding a single animal a food it likes that there is enough of. Note that
this test doesn't test what happens when there is not enough food or an animal is fed a food it
doesn't like.
*/
TestResult test_FeedAnimal() {
    // Set up the food and animal
    ZooManagementSystem zms(10000.0);
    zms.addFood(Food("banana", 4.50, 250));
    double cost;
    ASSERT(zms.purchaseFood(cost, 0, 20));
    EXPECT_SIGMA(cost, 20 * 4.5);
    zms.addAnimal(Animal::AT_MONKEY);

    // Feed the monkey
    unsigned int eaten;
    ZooManagementSystem::FeedResult result = zms.feedAnimal(eaten, 0, 0);
    ASSERT(result == ZooManagementSystem::FR_SUCCESS);
    // monkey must eat at least four bananas to be full
    ASSERT(eaten == 4);
    vector<Animal*> animals = zms.getAnimals();
    ASSERT(animals[0]->hungerLevel() == 0);

    return TR_PASS;
}

#endif /*ENABLE_T3_TESTS*/

/////////////// HAMISHS TESTS ////////////////////

TestResult test_hamish_1() {
	
	//3.1.1
	Food apple("Apple", 700.40, 121);
	
	//3.1.2
	ASSERT(apple.getName() == "Apple");
	EXPECT_SIGMA(apple.getCost(), 700.40);
	ASSERT(apple.getQuantity() == 0);
	ASSERT(apple.getEnergy() == 121);
	
	//3.1.3
	ASSERT(apple.consume(0) == 0);
	ASSERT(apple.consume(20) == 0);
	ASSERT(apple.getQuantity() == 0);
	
	//3.1.4
	apple.purchase(300);
	ASSERT(apple.getQuantity() == 300);
	ASSERT(apple.consume(40) == 40);
	ASSERT(apple.getQuantity() == 260);
	ASSERT(apple.consume(280) == 260);
	ASSERT(apple.getQuantity() == 0);
	
    return TR_PASS;
}

TestResult test_hamish_2() {

	//3.2 (Lion)
	Animal *lion = new Lion();
	ASSERT(lion->type() == Animal::AT_LION);
	ASSERT(lion->hungerLevel() == 2200);
	ASSERT(lion->likesFood(Food("steak",0,0)) == true);
	ASSERT(lion->likesFood(Food("mouse",0,0)) == true); 
	ASSERT(lion->likesFood(Food("fish",0,0)) == true);
	ASSERT(lion->likesFood(Food("banana",0,0)) == false);
	ASSERT(lion->likesFood(Food("watermelon",0,0)) == false); 
	ASSERT(lion->likesFood(Food("mealworms",0,0)) == false);
	ASSERT(lion->likesFood(Food("hay",0,0)) == false);
	ASSERT(lion->likesFood(Food("egg",0,0)) == false);	
	Food steak("steak",0,4);
	steak.purchase(200);
	ASSERT(lion->feed(steak) == 200);
	ASSERT(steak.getQuantity() == 0);
	ASSERT(lion->hungerLevel() == 1400);
	lion->resetToHungry();
	ASSERT(lion->hungerLevel() == 2200);
	steak.purchase(600);
	ASSERT(lion->feed(steak) == 550);
	ASSERT(steak.getQuantity() == 50);
	ASSERT(lion->hungerLevel() == 0);
	lion->resetToHungry();
	ASSERT(lion->hungerLevel() == 2200);
	Food steak2("steak",0,2400);
	steak2.purchase(1);
	ASSERT(lion->feed(steak2) == 1);
	ASSERT(steak2.getQuantity() == 0);
	ASSERT(lion->hungerLevel() == 0);
	lion->resetToHungry();
	ASSERT(lion->hungerLevel() == 2200);
	Food hay("hay",0,24);
	hay.purchase(20);
	ASSERT(lion->feed(hay) == 0);
	ASSERT(hay.getQuantity() == 20);
	ASSERT(lion->hungerLevel() == 2200);
	
    return TR_PASS;
}


TestResult test_hamish_3() {
	
	//3.3.2
	ZooManagementSystem zms(300.15);
	EXPECT_SIGMA(zms.getBalance(), 300.15);
	
	//3.3.3
	EXPECT_SIGMA(zms.admitVisitors(0,0), 0);
	EXPECT_SIGMA(zms.getBalance(), 300.15);
	EXPECT_SIGMA(zms.admitVisitors(1,0), 14);
	EXPECT_SIGMA(zms.getBalance(), 314.15);
	EXPECT_SIGMA(zms.admitVisitors(0,1), 5);
	EXPECT_SIGMA(zms.admitVisitors(2,1), 33);
	EXPECT_SIGMA(zms.admitVisitors(2,2), 30);
	EXPECT_SIGMA(zms.admitVisitors(2,3), 35);
	EXPECT_SIGMA(zms.admitVisitors(4,4), 60);
	EXPECT_SIGMA(zms.admitVisitors(4,6), 70);
	EXPECT_SIGMA(zms.getBalance(), 547.15);
	
	//3.3.4
	ASSERT(zms.getFood().empty() == true);
	Food pipe("pipe",30.15,700);
	zms.addFood(pipe);
	vector<Food> fd = zms.getFood();
	ASSERT(fd.size() == 1);
	ASSERT(fd[0].getName() == "pipe");
	Food pipe2("pipe2",12.99,40);
	zms.addFood(pipe2);
	fd = zms.getFood();
	ASSERT(fd.size() == 2);
	ASSERT(fd[0].getName() == "pipe");
	ASSERT(fd[1].getName() == "pipe2");
	
	//3.3.5
	ASSERT(zms.getAnimals().empty() == true);
	ASSERT(zms.addAnimal(Animal::AT_LION) == true);
	vector<Animal*> an = zms.getAnimals();
	ASSERT(an.size() == 1);
	ASSERT(an[0]->type() == Animal::AT_LION);
	ASSERT(zms.addAnimal(Animal::AT_SNAKE) == true);
	an = zms.getAnimals();
	ASSERT(an.size() == 2);
	ASSERT(an[0]->type() == Animal::AT_LION);
	ASSERT(an[1]->type() == Animal::AT_SNAKE);
	ASSERT(zms.addAnimal(Animal::AT_INVALID) == false);
	an = zms.getAnimals();
	ASSERT(an.size() == 2);
	
	//3.3.6
	Food steak("steak",0,1);
	steak.purchase(200);
	ASSERT(an[0]->feed(steak) == 200);
	ASSERT(an[0]->hungerLevel() == 2000);	
	Food mouse("mouse",0,1);
	mouse.purchase(200);
	ASSERT(an[1]->feed(mouse) == 200);
	ASSERT(an[1]->hungerLevel() == 50);	
	zms.resetAllAnimals();
	an = zms.getAnimals();
	ASSERT(an[0]->hungerLevel() == 2200);
	ASSERT(an[1]->hungerLevel() == 250);	
	
	//3.3.8
	double cost;
	ZooManagementSystem zms3(10000);
	Food apple("apple",30,700);
	zms3.addFood(apple);
	Food rock("rock",2000,600);
	zms3.addFood(rock);
	// Initial state
	fd = zms3.getFood();
	ASSERT(fd[0].getQuantity() == 0);
	ASSERT(fd[1].getQuantity() == 0);
	ASSERT(zms3.getBalance() == 10000);
	// First purchase
	ASSERT(zms3.purchaseFood(cost, 0, 30) == true);
	EXPECT_SIGMA(cost, 900);
	fd = zms3.getFood();
	ASSERT(fd[0].getQuantity() == 30);
	ASSERT(fd[1].getQuantity() == 0);
	ASSERT(zms3.getBalance() == 9100);
	// Second purchase
	ASSERT(zms3.purchaseFood(cost, 0, 60) == true);
	EXPECT_SIGMA(cost, 1800);
	fd = zms3.getFood();
	ASSERT(fd[0].getQuantity() == 90);
	ASSERT(fd[1].getQuantity() == 0);
	ASSERT(zms3.getBalance() == 7300);
	// Index too high (borderline)
	ASSERT(zms3.purchaseFood(cost, 2, 60) == false);
	EXPECT_SIGMA(cost, 0);
	fd = zms3.getFood();
	ASSERT(fd[0].getQuantity() == 90);
	ASSERT(fd[1].getQuantity() == 0);
	ASSERT(zms3.getBalance() == 7300);
	// Not enough money case
	ASSERT(zms3.purchaseFood(cost, 1, 5) == false);
	EXPECT_SIGMA(cost, 10000);
	fd = zms3.getFood();
	ASSERT(fd[0].getQuantity() == 90);
	ASSERT(fd[1].getQuantity() == 0);
	ASSERT(zms3.getBalance() == 7300);
	
	//3.3.9
	ZooManagementSystem zms4(100000);
	ASSERT(zms4.addAnimal(Animal::AT_LION) == true);
	ASSERT(zms4.addAnimal(Animal::AT_SNAKE) == true);
	Food f1("steak",1,440);
	zms4.addFood(f1);
	ASSERT(zms4.purchaseFood(cost, 0, 60) == true);
	Food f2("mouse",1,200);
	zms4.addFood(f2);
	ASSERT(zms4.purchaseFood(cost, 1, 1) == true);
	unsigned int quantity_eaten;
	//case1
	ASSERT(zms4.feedAnimal(quantity_eaten, 0, 0) == ZooManagementSystem::FR_SUCCESS);
	ASSERT(quantity_eaten == 5);
	//case2
	ASSERT(zms4.feedAnimal(quantity_eaten, 2, 0) == ZooManagementSystem::FR_INVALID_ANIMAL);
	ASSERT(quantity_eaten == 0);
	//case3
	ASSERT(zms4.feedAnimal(quantity_eaten, 0, 2) == ZooManagementSystem::FR_INVALID_FOOD);
	ASSERT(quantity_eaten == 0);
	//case4
	ASSERT(zms4.feedAnimal(quantity_eaten, 2, 2) == ZooManagementSystem::FR_INVALID_ANIMAL);
	ASSERT(quantity_eaten == 0);
	//case5
	ASSERT(zms4.feedAnimal(quantity_eaten, 1, 0) == ZooManagementSystem::FR_INCOMPATIBLE);
	ASSERT(quantity_eaten == 0);
	//case6
	ASSERT(zms4.feedAnimal(quantity_eaten, 1, 1) == ZooManagementSystem::FR_EXHAUSTED); //snake to eat mouse
	ASSERT(quantity_eaten == 1);
	
    return TR_PASS;
}

TestResult test_hamish_4() {
	
	// useful vars
	double cost;
	vector<Animal*> animals;
	ZooManagementSystem zms(1000000000000); //much moneys
	
	// Create 5 animals, checking for success
	ASSERT(zms.addAnimal(Animal::AT_LION) == true);		// 2200 : steak,mouse,fish
	ASSERT(zms.addAnimal(Animal::AT_SNAKE) == true);	// 250 : mouse,egg
	ASSERT(zms.addAnimal(Animal::AT_MONKEY) == true);	// 800 : banana,watermelon,mealworms
	ASSERT(zms.addAnimal(Animal::AT_OTTER) == true);	// 750 : fish,mouse
	ASSERT(zms.addAnimal(Animal::AT_ELEPHANT) == true);	// 8400 : banana,watermelon,hay
	
	// Add all foods (all free of cost)
	zms.addFood(Food("steak",0,0));		//0
	zms.addFood(Food("mouse",0,1)); 	//1
	zms.addFood(Food("fish",0,0));		//2
	zms.addFood(Food("banana",0,1));	//3
	zms.addFood(Food("watermelon",0,1));//4 
	zms.addFood(Food("mealworms",0,0));	//5
	zms.addFood(Food("hay",0,7600));	//6
	zms.addFood(Food("egg",0,0));		//7
	
	// Add some mouse, should be eaten fully by lion then some for otter none for snake
	ASSERT(zms.purchaseFood(cost, 1, 2300) == true); //buy 2300 mouse
	zms.feedAllAnimals();
	animals = zms.getAnimals();
	ASSERT(animals[0]->hungerLevel() == 0); //lion
	ASSERT(animals[3]->hungerLevel() == 650); //otter
	ASSERT(animals[1]->hungerLevel() == 250); //snake
	
	zms.resetAllAnimals(); //now no food and animals hungry
	
	// Add enough hay such that elephant eats and is 800 hungry like monkey
	ASSERT(zms.purchaseFood(cost, 6, 1) == true); //buy 1 hay
	zms.feedAllAnimals();
	animals = zms.getAnimals();
	ASSERT(animals[2]->hungerLevel() == 800); //monkey
	ASSERT(animals[4]->hungerLevel() == 800); //elephant

	// Monkey should eat bananas now as higher index
	ASSERT(zms.purchaseFood(cost, 3, 800) == true); //buy 800 hay
	zms.feedAllAnimals();
	animals = zms.getAnimals();
	ASSERT(animals[2]->hungerLevel() == 0); //monkey
	ASSERT(animals[4]->hungerLevel() == 800); //elephant

	zms.resetAllAnimals(); //now no food and animals hungry

	ASSERT(zms.purchaseFood(cost, 3, 8400) == true); //buy 8400 banana
	ASSERT(zms.purchaseFood(cost, 6, 8400) == true); //buy 8400 hay
	zms.feedAllAnimals();
	animals = zms.getAnimals();
	ASSERT(animals[4]->hungerLevel() == 0); //elephant
	vector<Food> fd = zms.getFood();
	ASSERT(fd[3].getQuantity() == 0);
	ASSERT(fd[6].getQuantity() == 8400);

	return TR_PASS;
}

//////////////////////////////////////////////////

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;
    tests.push_back(&test_FoodNameCost);
    tests.push_back(&test_FoodQuantity);
    tests.push_back(&test_FoodPurchase);
    tests.push_back(&test_FoodConsume);
#ifdef ENABLE_T2_TESTS
    tests.push_back(&test_Monkey);
    tests.push_back(&test_Lion);
    tests.push_back(&test_Elephant);
    tests.push_back(&test_Snake);
    tests.push_back(&test_Otter);
#endif /*ENABLE_T2_TESTS*/
#ifdef ENABLE_T3_TESTS
    tests.push_back(&test_UPI);
    tests.push_back(&test_ZMSConstruction);
    tests.push_back(&test_InitialBalance);
    tests.push_back(&test_Visitors);
    tests.push_back(&test_AddAnimals);
    tests.push_back(&test_AddFood);
    tests.push_back(&test_PurchaseFood);
    tests.push_back(&test_FeedAnimal);
#endif /*ENABLE_T3_TESTS*/

	/////HAMISHS TESTS//////////////
	tests.push_back(&test_hamish_1);
	tests.push_back(&test_hamish_2);
	tests.push_back(&test_hamish_3);
	tests.push_back(&test_hamish_4);
	////////////////////////////////

    return tests;
}

int main(int argc, char const* argv[]) {
    // If one or more test numbers are passed as command-line parameters, execute them
    vector<TestResult (*)()> tests_to_run = generateTests();
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    unsigned int run_count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            unsigned int test_num = atoi(argv[i]);
            if (test_num > tests_to_run.size()) {
                cout << "ERROR: unknown test case " << test_num << endl;
                continue;
            }
            // run the test
            ++run_count;
            TestResult result = tests_to_run[test_num]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << test_num << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << test_num << " passed." << endl;
                ++pass_count;
            }
        }
    } else {
        // otherwise, run all tests
        // Make sure to update this section as you add more tests
        // Add the tests for the first task
        for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
            ++run_count;
            TestResult result = tests_to_run[t]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << t << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << t << " passed." << endl;
                ++pass_count;
            }
        }
    }
    cout << "\n-------------------------------------------------\n"
         << "Total Run: " << run_count << "\n"
         << "Total PASSED: " << pass_count << "\n"
         << "Total FAILED: " << fail_count << "\n"
         << "-------------------------------------------------\n" << endl;

    // Return 0 if everything was ok
	//system("pause");
    return 0;
}
