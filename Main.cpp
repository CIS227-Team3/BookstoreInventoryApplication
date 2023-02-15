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

    string ISBN;
	string author;
	int year;
	string publisher;
	string description;
	string genre;

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
                case 2:
                    cout << "Please enter a title to search: " << endl;
                    getline(cin, title);
                    inventory.searchForBook(title);
                    break;
                case 3:
                {
                    cout << "Please add the following information. " << endl;
                    cout << "ISBN, Book-Title, Book-Author, Year-Of-Publication, Publisher: " << endl;
                    cout << "Add ISBN: " << endl;
                    getline(cin, ISBN);
                    cout << "Add Book-Title: " << endl;
                    getline(cin, title);
                    cout << "Add Book-Author: " << endl;
                    getline(cin, author);
                    cout << "Add Year-Of-Publication: " << endl;
                    year = validateYear(); // validates that the year entered is an integer
                    cout << "Add Publisher: " << endl;
                    getline(cin, publisher);

                    // By default, user does not have to enter a description or a genre at the time it is added to the database
                    Book book(ISBN, title, author, year, publisher, "", "");

                    // adds book to inventory
                    inventory.addBook(book);

                    break;
                }
                case 4:
                {
					cout << "Please enter title of book to delete:" << endl;
					getline(cin, title);
					inventory.deleteBook(title);
					break;
				}
                case 5:
                {
                    cout << "Please enter title: " << endl;
                    getline(cin, title);
                    cout << "Please enter description/plot: " << endl;
                    getline(cin, description);
                    cout << "Please enter genre: " << endl;
                    getline(cin, genre);
                    
                    // updates the description and genre of the specified book.
                    inventory.updateDescription(title, description);
                    inventory.updateGenre(title, genre);
                    break;
                }
                case 6:
                {
                    cout << "Please enter title of book to add:" << endl;
                    getline(cin, title);
                    foundBook = inventory.searchForBook(title);
                    currentUser.addToUserList(foundBook);
                    break;
                }

                case 7:
                {
                    currentUser.listUserList();
                    break;
                }
                case 8:
                {
                    inventory.exportInventoryToCsv();
                    break;
                }
                default:
                {
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
