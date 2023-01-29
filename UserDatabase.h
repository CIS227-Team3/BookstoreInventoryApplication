#ifndef BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
#define BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H

#include <iostream>
#include <vector>
#include "User.h"
#include "readFile.h"

class UserDatabase {
public:
    UserDatabase();

private:
    vector<User> Users;
    void addInitialUsers();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
