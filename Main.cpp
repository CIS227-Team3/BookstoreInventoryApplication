/*
 * Main.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "Book.h";
// #include "Book.cpp"
#include "readFile.h"
// #include "readFile.cpp"
#include "User.h"
// #include "User.cpp"

using namespace std;

int main() {
    cout << "Please create a password." << endl;

    cin >> //string something >> endl;
    //Add code for transfering password to new csv file

    cout << "Thank you for creating a password!" << endl;
    cout << "Please type the name of the book you desire." << endl;

    cin >> //string book >> endl;  
    //find the book in the csv file

    //if book is found print:
    cout << "Successfully found" << //book name endl;
    cout << //Name of book, author, publish, year, description endl;

    //if not
    cout << "Search not successful" << endl;
	return 0;
}

