#ifndef BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
#define BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <boost/optional.hpp>
#include "stdio.h"
#include "User.h"
#include "includes/md5.h"
#include "BookstoreInventory.h"

using namespace std;

//UserDatabase Class
class UserDatabase {
public:
    UserDatabase();

    void updateUserPassword();

    void addUser();

    void addUser(User user);

    bool loginUser(string username, string password);

    User getCurrentUser();

    boost::optional<User> searchUser(const string &username); // searches for user based on username

    string searchShopper(const string &username);

    void addShopper(string email, string name, float total);

private:
    User currentUser;
    
    static int searchUserCallback(void *data, int argc, char **argv, char **azColName);

    void updateUser(User user);

    static int searchShopperCallback(void *data, int argc, char **argv, char **azColName);
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
