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
    void updateUserPassword();
    void addUser();
    bool loginUser(string username, string password);
    User getCurrentUser();

private:
    list<User> Users;
    User currentUser;
    void addInitialUsers();
    User searchUser(string username); // searches for user based on username
    static int searchUserCallback(void *notUsed, int argc, char **argv, char **azColName);
    void updateUser(User user);
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
