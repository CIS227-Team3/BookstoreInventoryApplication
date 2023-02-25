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
#include <boost/optional.hpp>
#include "Book.h"
#include "includes/sqlite3.h"

using namespace std;

//CLass User
class User {
public:
    User();

    User(string username, string password, int hashed, int isAdmin);

    User(boost::optional<User> anOptional);

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

    //void listUserShoppingList();

    void addToUserList(Book book);

    //void addToUserShoppingList(Book book);

    //void saveUserShoppingList();

    //void getUserShoppingList(BookstoreInventory inventory);

private:
    string username;
    string password;
    int hashed;
    int isAdmin;

    deque<Book> UserList;
    //multiset<Book> UserShoppingList;

    //static int searchUserShoppingCartCallback(void *data, int argc, char **argv, char **azColName);
};

#endif /* USER_H_ */
