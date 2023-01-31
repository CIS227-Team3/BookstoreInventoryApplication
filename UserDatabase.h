#ifndef BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
#define BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stdio.h"
#include "User.h"
#include "readFile.h"

//UserDatabase Class
class UserDatabase {
public:
    UserDatabase();
    // void addUser();
    // void updateUser();
    bool loginUser(string username, string password);

private:
    vector<User> Users;
    void addInitialUsers();
    // bool searchUser(string username); // searches for user based on username
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
