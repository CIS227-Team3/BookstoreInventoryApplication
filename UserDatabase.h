#ifndef BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
#define BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "stdio.h"
#include "User.h"
#include "fileOperations.h"

using namespace std;

//UserDatabase Class
class UserDatabase {
public:
    UserDatabase();

    // void addUser();
    // void updateUser();
    bool loginUser(string username, string password);

private:
    list<User> Users;

    void addInitialUsers();
    // bool searchUser(string username); // searches for user based on username
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
