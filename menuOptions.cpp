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
    cout << "Press 2 to bring up the book management menu." << endl;
    cout << "Press 3 to bring up the user management menu." << endl;
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

void inventoryManagementOptions(BookstoreInventory &inventory){
    short int menuOption = 1;
    string title;
    string ISBN;
    string author;
    int year;
    string publisher;
    string description;
    string genre;

    while(menuOption != 0){
        switch (menuOption) {
            case 1: {
                // do nothing so the menu will prompt on loop
                break;
            }
            case 2:
            {
                cout << "Please enter a title to search: " << endl;
                getline(cin, title);
                inventory.searchForBook(title);
                break;
            }
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
                Book book(ISBN, title, author, year, publisher, "", "", 10, 1);

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
            default:
            {
                cout << "Menu option not recognized." << endl;
                break;
            }
        }
        cout << endl << endl <<"Press 0 to exit this menu." << endl;
        cout << "Press 1 to bring up this menu again." << endl;
        cout << "Press 2 to search for a book." << endl;
        cout << "Press 3 to add a book to inventory." << endl;
        cout << "Press 4 to delete a book from inventory." << endl;
        cout << "Press 5 to add a description/plot and genre." << endl;
        menuOption = validateMenuOption();
    }
}

void adminMenu(UserDatabase &users) {
    short int menuOption = 1;

    while(menuOption != 0){
        switch (menuOption) {
            case 1: {
                // do nothing so the menu will prompt on loop
                break;
            }
            case 2: {
                users.addUser();
                break;
            }
            case 3: {

                break;
            }
            case 4: {

                break;
            }
            case 5: {

                break;
            }
            default:
            {
                cout << "Menu option not recognized." << endl;
                break;
            }
        }
        cout << endl << endl <<"Press 0 to exit this menu." << endl;
        cout << "Press 1 to bring up this menu again." << endl;
        cout << "Press 2 to add a user." << endl;
        cout << "Press 3 to change a users password." << endl;
        cout << "Press 4 to import book file." << endl;
        cout << "Press 5 to import user file." << endl;
        menuOption = validateMenuOption();
    }
}
