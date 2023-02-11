/*
 * Main.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "UserDatabase.h"
//#include "UserDatabase.cpp"
#include "BookstoreInventory.h"
//#includes "BookstoreInventory.cpp"
#include "Book.h"
// #include "Book.cpp"
#include "fileOperations.h"
// #include "readFile.cpp"
#include "User.h"
// #include "User.cpp"
#include "menuOptions.h"
// #include "menuOptions.cpp"

using namespace std;

int main() {
    string password;
    string username;

    BookstoreInventory inventory;
    UserDatabase users;

    short unsigned int menuOption;
    string title;

    cout << "---------------------------" << endl;
    cout << "Thank you for using BOOKIN!" << endl;
    cout << "---------------------------" << endl;
    cout << endl;
    cout << "Please type in your username" << endl;
    cin >> username;

    cout << "Please type in your password" << endl;
    cin >> password;

    // removes newline character from buffer
    cin.clear();
    cin.ignore(1000, '\n');

    if (users.loginUser(username, password)) {
        menuOption = 1; // starts the menu at 1 to allow user to enter a title to search
        while (menuOption != 0) {
            switch (menuOption) {
                case 1:
                    cout << "Please enter a title to search: " << endl;
                    getline(cin, title);
                    inventory.searchForBook(title);
                    break;
                default:
                    cout << "Menu option not recognized." << endl;
                    break;
            }
            menuOption = promptUserInput();
        }
    }

    cout << "Exiting BOOKIN. Goodbye!" << endl;

    return EXIT_SUCCESS;
}

