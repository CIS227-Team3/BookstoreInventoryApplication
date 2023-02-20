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
    User currentUser;
    Book foundBook;

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
        currentUser = users.getCurrentUser();
        menuOption = 1; // starts the menu at 1 for menu
        while (menuOption != 0) {
            switch (menuOption) {
                case 1:
                    // do nothing so the menu will prompt on loop
                    break;
                case 2: {
                    inventoryManagementOptions(inventory);
                    break;
                }
                case 3: {
                    adminMenu(users);
                    break;
                }
                case 4: {
                    cout << "Please enter title of book to add:" << endl;
                    getline(cin, title);
                    foundBook = inventory.searchForBook(title);
                    currentUser.addToUserList(foundBook);
                    break;
                }
                case 5: {
                    currentUser.listUserList();
                    break;
                }
                case 6: {
                    inventory.exportInventoryToCsv();
                    break;
                }

                case 7: {
                    cout << "Welcome to the shopping cart!" << endl;
                    cout << "Please enter the title of the book you want to purchase: " << endl;
                    getline(cin, title);
                    foundBook = inventory.searchForBook(title);
                    currentUser.addToUserShoppingList(foundBook);
                    break;
                }
                case 8: {
                    cout << "Here is a list of everything in your cart:" << endl;
                    currentUser.listUserShoppingList();
                    break;
                }
                default: {
                    cout << "Menu option not recognized." << endl;
                    break;
                }
            }
            menuOption = menuOptions();
        }
    }

    cout << "Exiting BOOKIN. Goodbye!" << endl;

    return EXIT_SUCCESS;
}
