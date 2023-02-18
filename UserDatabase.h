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
#include "includes/md5.h"

using namespace std;

//UserDatabase Class
class UserDatabase {
public:
    UserDatabase();

    void addUser();
    void updateUser();
    bool loginUser(string username, string password);
    User getCurrentUser();

private:
    list<User> Users;
    User currentUser;
    void addInitialUsers();
    bool searchUser(string username); // searches for user based on username
    static int searchUserCallback(void *notUsed, int argc, char **argv, char **azColName);
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
