/*
 * User.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>
#include "Book.h"

using namespace std;

//CLass User
class User {
public:
    User();

    User(string username, string password, int hashed, int isAdmin);

    void setUsername(string username);

    string getUsername() const;

    void setPassword(string password);

    string getPassword() const;

    void updatePassword(string username, string password);

    void setEncryptStatus(int hashed);

    int getEncryptStatus();

    void setAdminStatus(int status);

    int getAdminStatus();

    void listUserList();

    void listUserShoppingList();

    void addToUserList(Book book);

    void addToUserShoppingList(Book book);

private:
    string username;
    string password;
    int hashed;
    int isAdmin;

    deque<Book> UserList;
    set<Book> UserShoppingList;
};

#endif /* USER_H_ */
