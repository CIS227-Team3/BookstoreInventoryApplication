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
#include "readFile.h"
// #include "readFile.cpp"
#include "User.h"
// #include "User.cpp"

using namespace std;

int main() {
    User user;
    string password;
    cout << "---------------------------" << endl;
    cout << "Thank you for using BOOKIN!" << endl;
    cout << "---------------------------" << endl;
    cout << endl;
    cout << "Please type in your password" << endl;

    cin >> password;

    cout << endl;
    if (password == user.getPassword()) {
        cout << "Welcome" << user.getUsername();
        cout << endl;
    } else {
        cout << "Password is incorrect, now exiting." << endl;
        return(0);
    } 
    BookstoreInventory inventory;

    UserDatabase users;

    // for testing
    //inventory.listInventory();

    if(inventory.searchForBook("jane doe")){
        cout << "Found";
    }
    else{
        cout << "Not Found";
    }

	return EXIT_SUCCESS;
}

