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
#include "Book.h"

using namespace std;

//CLass User
class User {
public:
    User();

    User(string username, string password);

    void setUsername(string username);

    string getUsername() const;

    void setPassword(string password);

    string getPassword() const;

    void updatePassword(string username, string password);

    void listUserList();

private:
    string username;
    string password;

    deque<Book> UserList;
};

#endif /* USER_H_ */
