/*
main.cpp

This is the central logic for the command-line interface to the Zoo Management application.

You shouldn't need to modify this file at all; your task is to modify the following classes and files in the Zoo
folder to implement the program's behaviour:

- Food (Food.hpp/Food.cpp)
- Animal (Animal.hpp/Animal.cpp)
- Cage (Cage.hpp/Cage.cpp)
- Your own new classes in new hpp and cpp files.
*/

#include <iostream>
#include <iomanip>
#include <limits>

#include "Zoo/ZooManagementSystem.hpp"
#include "Zoo/Animal.hpp"
#include "Zoo/Food.hpp"

using namespace std;

// If cin is in a failure state, tries to skip the bad input
void skipBadInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
    }
}

// Print an error message to the standard output
void error(const string& message) {
    cout << "\n\n#########################################################\n"
         << "Error:\n" << message << "\n"
         << "#########################################################\n" << endl;
}

string animalTypeToString(Animal::AnimalType animaltype) {
    vector<string> types;
    types.push_back("monkey");
    types.push_back("lion");
    types.push_back("elephant");
    types.push_back("snake");
    types.push_back("otter");
    return types[static_cast<int>(animaltype)];
}

// Display the top-level menu and return the option number the user selected
int topMenu() {
    int selection = -1;
    while (selection == -1) {
        cout << "Please select from one of the following options:\n"
             << "\t0: QUIT\n"
             << "\t1: Display the zoo's available balance\n"
             << "\t2: Admit visitors to the zoo\n"
             << "\t3: Display the available food stock\n"
             << "\t4: Purchase food\n"
             << "\t5: Display the animals currently held by the zoo\n"
             << "\t6: Add an animal to the zoo\n"
             << "\t7: Feed the animals\n"
             << "\t8: Automatically feed all Animals\n"
             << "\t9: Reset the hunger levels for all animals\n\n"
             << ">>>";
        cout.flush();
        cin >> selection;

        // Protect against bad inputs
        if (cin.fail() || selection > 9 || selection < 0) {
            // recieved some sort of invalid input, print the error and ask for a new input
            skipBadInput();
            selection = -1;
            error("Invalid menu selection, please input a number between 1 and 9.");
        }
    }
    return selection;
}

// Request the initial balance for the day from the user.
double requestInitialBalance() {
    bool valid = false;
    double balance = 0.0f;
    while (!valid) {
        cout << "Please input the initial bank balance:\n"
             << ">>>$";
        cout.flush();
        cin >> balance;
        valid = !cin.fail();
        if (!valid) {
            skipBadInput();
            error("Invalid initial balance, please input a valid balance such as \"100.00\"");
        }
    }
    return balance;
}

// Print the Zoo's current balance to the screen.
void displayBalance(ZooManagementSystem& zms) {
    // Display the zoo's bank balance
    double balance = zms.getBalance();
    cout << "=============================\n"
         << "Bank Balance: $" << fixed << setprecision(2) << balance << "\n"
         << "=============================\n" << endl;
}

/*
Admit visitors to the Zoo.

Visitors will be charged a different fee according to whether they are a child or adult. The total
cost for the group admitted to ther zoo will be displayed.
*/
void admitVisitors(ZooManagementSystem& zms) {
    // Admit visitors to the zoo
    int adults, children;
    cout << "# of Adults:";
    cin >> adults;
    cout << "# of Children:";
    cin >> children;

    double cost = zms.admitVisitors(adults, children);
    cout << "\nTotal Cost: \t" << cost << "\n" << endl;
}

// Display the Zoo's food stocks.
void displayFood(ZooManagementSystem& zms) {
    vector<Food> food = zms.getFood();
    cout << "### Food available ###\n\n"
         << "Index | Name         | Quantity\n"
         << "-------------------------------\n";
    for (unsigned int i = 0; i < food.size(); ++i) {
        cout << left << setw(8) << i << setw(15) << food[i].getName() << setw(9) << food[i].getQuantity() << "\n";
    }
    cout << endl;
}

// Purchase more food to replenish the Zoo's stocks.
void purchaseFood(ZooManagementSystem& zms) {
    vector<Food> food = zms.getFood();
    cout << "### Food available for purchase ###\n\n"
         << "Index | Name         | Price ($)\n"
         << "------------------------------\n";
    for (unsigned int i = 0; i < food.size(); ++i) {
        cout << left << setw(8) << i << setw(15) << food[i].getName() << setw(9) << fixed << setprecision(2) << food[i].getCost() << "\n";
    }
    cout << "\nEnter food index:";
    int food_index;
    cin >> food_index;
    cout << "\nEnter quantity:";
    int quantity;
    cin >> quantity;
    double cost;
    bool success = zms.purchaseFood(cost, food_index, quantity);
    if (success) {
        food = zms.getFood();
        cout << "\nPurchase cost: $" << fixed << setprecision(2) << cost << "\n" << food[food_index].getName()
             << " quantity available: " << food[food_index].getQuantity() << "\n" << endl;
    } else {
        error("Purchase unsuccessful, please ensure the selected food exists and there is enough money to make the purchase.");
    }
}

// Display Animals currently held by the zoo.
void displayAnimals(ZooManagementSystem& zms) {
    vector<Animal*> animals = zms.getAnimals();
    cout << "### Animals currently held by the Zoo ###\n\n"
         << "Index | Type \n"
         << "------------------------------\n";
    for (unsigned int i = 0; i < animals.size(); ++i) {
        cout << left << setw(8) << i << setw(14) << animalTypeToString(animals[i]->type()) << "\n";
    }
    cout << endl;
}

// Add an animal to the Zoo
void addAnimal(ZooManagementSystem& zms) {
    cout << "### Animal types available ###\n\n"
         << "Index | Type\n"
         << "--------------------\n";
    for (int i = 0; i < Animal::AT_INVALID; ++i) {
        cout << left << setw(8) << i << setw(12) << animalTypeToString(static_cast<Animal::AnimalType>(i)) << "\n";
    }
    cout << "Enter an animal type index (0 to " << (Animal::AT_INVALID - 1) << "): ";
    int new_animal_type;
    cin >> new_animal_type;
    bool success = zms.addAnimal(static_cast<Animal::AnimalType>(new_animal_type));
    if (success) {
        cout << "Animal " << animalTypeToString(static_cast<Animal::AnimalType>(new_animal_type)) << " successfully added to ZMS.\n";
    } else {
        cout << "Animal of type " << new_animal_type << " could not be added.\n";
    }
    cout << endl;
}

// Feed an animal
void feedAnimal(ZooManagementSystem& zms) {
    displayAnimals(zms);

    cout << "Please enter the index of the animal to feed:";
    unsigned int animal_index;
    cin >> animal_index;

    displayFood(zms);

    cout << "\nPlease enter the index of the food you would like to use:";
    unsigned int food_index;
    cin >> food_index;

    unsigned int quantity_eaten = 0;
    ZooManagementSystem::FeedResult result = zms.feedAnimal(quantity_eaten, animal_index, food_index);
    vector<Animal*> animals = zms.getAnimals();
    vector<Food> food = zms.getFood();
    // Check indexes are valid, if so then the feeding must have failed
    cout << "\n";
    switch (result) {
    case ZooManagementSystem::FR_SUCCESS:
        cout << "Animal " << animals[animal_index] << " ate " << quantity_eaten << " of food " << food[food_index].getName() << "\n"
             << food[food_index].getQuantity() << " of food " << food[food_index].getName() << "remaining.\n";
    case ZooManagementSystem::FR_INVALID_ANIMAL:
        cout << "Error: Animal index " << animal_index << " is invalid\n";
        break;
    case ZooManagementSystem::FR_INVALID_FOOD:
        cout << "Error: Food index " << food_index << " is invalid\n";
        break;
    case ZooManagementSystem::FR_INCOMPATIBLE:
        cout << "Error: Animal " << animals[animal_index]->type() << " doesn't want to eat food " << food[food_index].getName()
             << "\n";
        break;
    case ZooManagementSystem::FR_EXHAUSTED:
        cout << "Error: Exhausted supply of food " << food[food_index].getName() << " before animal was fully fed\n"
             << "Animal still needs " << animals[animal_index]->hungerLevel() << "kJ\n";
        break;
    default:
        break;
    }
    cout << endl;
}

void feedAllAnimals(ZooManagementSystem& zms) {
    cout << "Feeding all animals...\n" << endl;
    zms.feedAllAnimals();
    cout << "Automatic feeding complete!\n" << endl;
}

void resetAllHunger(ZooManagementSystem& zms) {
    cout << "Resetting hunger levels on all animals to their maximum values...\n" << endl;
    zms.resetAllAnimals();
    cout << "Hunger levels for all animals now at maximum, feed the animals!\n" << endl;
}

/*
Execute a choice from the main menu when a selection is made by the user. The actual implementation
for each action is defined in other functions called from within this one.
*/
void executeSelection(ZooManagementSystem& zms, int selection) {
    switch (selection) {
    case 1:
        // Display the zoo's bank balance
        displayBalance(zms);
        break;

    case 2:
        // Admit visitors to the zoo
        admitVisitors(zms);
        break;

    case 3:
        // Display total food stocks
        displayFood(zms);
        break;

    case 4:
        // Purchase food
        purchaseFood(zms);
        break;

    case 5:
        // Display animals currrently held and status
        displayAnimals(zms);
        break;

    case 6:
        // Add an animal
        addAnimal(zms);
        break;

    case 7:
        // Feed animals
        feedAnimal(zms);
        break;
    
    case 8:
        // Reset hunger on all animals
        feedAllAnimals(zms);
        break;
    case 9:
        // Reset hunger on all animals
        resetAllHunger(zms);
        break;
    default:
        break;
    }
}

int main() {
    cout << "Zoo Management System v1.0 by " << ZooManagementSystem::author() << "\n\n" << endl;
    
    // Set up the ZMS
    double initialBalance = requestInitialBalance();
    ZooManagementSystem zms(initialBalance);
    zms.addFood(Food("banana", 4.5, 250));
    zms.addFood(Food("steak", 15.8, 760));
    zms.addFood(Food("watermelon", 6, 385));
    zms.addFood(Food("mouse", 2, 250));
    zms.addFood(Food("egg", 0.6, 100));
    zms.addFood(Food("mealworms", 4.75, 310));
    zms.addFood(Food("fish", 7.6, 563));
    zms.addFood(Food("hay", 10.2, 960));

    // Present the top-level menu
    int selection = topMenu();
    while (selection != 0) {
        executeSelection(zms, selection);
        selection = topMenu();
    }

    cout << "\nOption 0 Selected, Exiting Zoo Management!" << endl;

    return 0;
}