#ifndef BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
#define BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H

#include <iostream>
#include <vector>
#include "User.h"
#include "readFile.h"

//UserDatabase Class
class UserDatabase {
public:
    UserDatabase();
    void addUser();
    void updateUser();

private:
    vector<User> Users;
    void addInitialUsers();
    bool searchUser(string username); // searches for user based on username
    bool validUser(string username, string password); // validates that user is in database and password matches
    void updateUserDatabase();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
