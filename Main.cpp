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

    short unsigned int menuOption1;
    short unsigned int menuOption2;
    string title;

    menuOption1 = 1; // starts the menu at 1 to allow user to enter a title to search
    while (menuOption1 != 0 ) {
        switch (menuOption1) { 
            case 1:
                cout << "---------------------------" << endl;
                cout << "Thank you for using BOOKIN!" << endl;
                cout << "---------------------------" << endl;
                cout << endl;

                cout << "Press 0 to exit application." << endl;
                cout << "Press 1 restart the program." << endl;
                cout << "Press 2 to login." << endl;
            case 2:
                cout << "Please type in your username:" << endl;
                cin >> username;
                cout << "Please type in your password:" << endl;
                cin >> password;

                // removes newline character from buffer
                cin.clear();
                cin.ignore(1000, '\n');

                 if (users.loginUser(username, password)) {
                     currentUser = users.getCurrentUser();
                    menuOption2 = 1; // starts the menu at 1 to allow user to enter a title to search
                    while (menuOption2 != 0) {
                    switch (menuOption2) {
                        case 1:
                            cout << "Press 0 to exit application." << endl;
                            cout << "Press 1 to bring up this menu again." << endl;
                            cout << "Press 2 to search for a book." << endl;
                            cout << "Press 3 to add a book." << endl;
                            cout << "Press 4 to add a description/plot and genre." << endl;
                        case 2:
                            cout << "Please enter a title to search: " << endl;
                            getline(cin, title);
                            inventory.searchForBook(title);
                            break;
                        case 3:
                            cout << "Please add this information." << endl;
                            cout << "ISBN, Book-Title, Book-Author, Year-Of-Publication, Publisher: " << endl;
                            cout << "Add ISBN: " << endl;
                            //cin ISBN
                            cout << "Add Book-Title: " << endl;
                            //cin Book-Title
                            cout << "Add Book-Author: " << endl;
                            //cin Book-Author
                            cout << "Add Year-Of-Publication: " << endl;
                            //cin Year-Of-Publication
                            cout << "Add Publisher: " << endl;
                            //cin Publisher
                            //add book to list
                            break;
                        case 4:
                            cout << "Please enter ISBN number: " << endl;
                            //cin ISBN number
                            cout << "Please enter description/plot: " << endl;
                            //cin ISBN number
                            cout << "Please enter genre: " << endl;
                            //cin ISBN number
                            //add it to a csv
                            break;
                        default:
                            cout << "Menu option not recognized." << endl;
                            break;
                        }
                        menuOption2 = promptUserInput();
                    }
                } else {
                    cout << "User is not recognized!" << endl;
                    menuOption1 = promptUserInput();
                }
            default:
                cout << "Menu option not recognized." << endl;
                break;
            }
            menuOption1 = promptUserInput();
        }


    cout << "Exiting BOOKIN. Goodbye!" << endl;

    return EXIT_SUCCESS;
}

