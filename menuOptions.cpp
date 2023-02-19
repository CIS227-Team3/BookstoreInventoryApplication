/*
 * menuOptions.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Group 3
 */

#include "menuOptions.h"

short int promptUserInput() {
    short int userInput;

    // prompts user to enter command
    cout << "Please enter 1 to enter a different title or 0 to exit the program" << endl;
    userInput = validateMenuOption();

    return userInput;
}

short int menuOptions() {
    short int userInput;

    // prompts user to enter command
    cout << endl << endl <<"Press 0 to exit application." << endl;
    cout << "Press 1 to bring up this menu again." << endl;
    cout << "Press 2 to search for a book." << endl;
    cout << "Press 3 to add a book to inventory." << endl;
    cout << "Press 4 to delete a book from inventory." << endl;
    cout << "Press 5 to add a description/plot and genre." << endl;
    cout << "Press 6 to add a book to a personal list." << endl;
    cout << "Press 7 to print your personal list." << endl;
    cout << "Press 8 to export the inventory as CSV." << endl;
    userInput = validateMenuOption();

    return userInput;
}

void printAndClearError() {
    cout << "Input cannot negative, non-numeric, or out-of-range. Please enter a positive value." << endl;

    cin.clear();  // clears error state if the user entered a string or char.
    // reference: https://cplusplus.com/forum/general/207458/
    cin.ignore(1000, '\n'); // clears the input causing error from stream.
    // reference: https://cplusplus.com/forum/general/207458/
}

short int validateMenuOption() {
    short int input;
    while (true) {
        if (std::cin >> input) { // if the user entered an integer
            cin.ignore(1000, '\n');
            return input;
        } else {
            printAndClearError();
        }
    }
}

unsigned short int validateYear() {
    unsigned short int year;

    while (true) {
        if (std::cin >> year) {
            cin.ignore(1000, '\n');
            return year;
        }

        else {
            printAndClearError();
        }
    }
}

float validatePrice() {
	float msrp;

	while (true) {
		if (std::cin >> msrp) {
			cin.ignore(1000, '\n');
			return msrp;
		}

		else {
			printAndClearError();
		}
	}
}

unsigned int validateQuantity() {
	unsigned int quantity;

	while (true) {
		if (std::cin >> quantity) {
			cin.ignore(1000, '\n');
			return quantity;
		}

		else {
			printAndClearError();
		}
	}
}
