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
#include "fileOperations.h"
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

    void addToUserShoppingList(Book book);

    void saveUserShoppingList();

    void getUserShoppingList(BookstoreInventory inventory);

    void listUserShoppingList();

    void readUsersFile(UserDatabase &users, string filePath);

    boost::optional<User> searchUser(const string &username); // searches for user based on username

private:
    User currentUser;
    multiset<Book> UserShoppingList;
    
    static int searchUserCallback(void *data, int argc, char **argv, char **azColName);

    static int searchUserShoppingCartCallback(void *data, int argc, char **argv, char **azColName);

    void updateUser(User user);
};


#endif //BOOKSTOREINVENTORYAPPLICATION_USERDATABASE_H
