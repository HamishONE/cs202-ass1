#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
// #define ENABLE_T2_TESTS
// #define ENABLE_T3_TESTS

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
    ASSERT(snake->hungerLevel() == 480);
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
    return 0;
}
