/*
 * User.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <deque>
#include "User.h"

//Constructor
User::User() {
    username = "none";
    password = "none";
    hashed = 0; // 0 for false (sqlite database does not store boolean values)
    isAdmin = 0; // 0 for false
}

//Makes a User
User::User(string username, string password, int hashed, int isAdmin) {
    this->username = username;
    this->password = password;
    this->hashed = hashed;
    this->isAdmin = isAdmin;
    this->UserList;
}

//Sets Username
void User::setUsername(string username) {
    this->username = username;
}

//Gets Username
string User::getUsername() const {
    return username;
}

//Sets Password
void User::setPassword(string password) {
    this->password = password;
}

//Gets Password
string User::getPassword() const {
    return password;
}

void User::setEncryptStatus(int hashed) {
    this->hashed = hashed;
}

int User::getEncryptStatus() {
    return hashed;
}

void User::setAdminStatus(int isAdmin) {
    this->isAdmin = isAdmin;
}

int User::getAdminStatus() {
    return isAdmin;
}

//Updates Password
void User::updatePassword(string username, string password) {

}

//Lists user's list in terminal
void User::listUserList() {
    cout << "ISBN | Book-Title | Book-Author" << endl;
    for (auto &book: this->UserList) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << endl;
    }

    cout << "Total items in list: " << this->UserList.size();
}

//Lists user's shopping list in terminal
void User::listUserShoppingList() {
    cout << "ISBN | Book-Title | Book-Author | Year Published | Publisher | Description | Genre | Price | Quantity"
         << endl;
    for (auto &book: this->UserShoppingList) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year << " | "
             << book.publisher << " | " << book.description << " | " << book.genre << " | " << book.msrp << " | "
             << book.quantity << endl;
    }
}

void User::addToUserList(Book book) {
    this->UserList.push_back(book);
}

void User::addToUserShoppingList(Book book) {
    this->UserShoppingList.insert(book);
}
