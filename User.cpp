/*
 * User.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "User.h"

//Constructor
User::User() {
    username = "none";
    password = "none";
    hashed = 0; // 0 for false (sqlite database does not store boolean values)
    isAdmin = 0; // 0 for false
}

//Makes a User
User::User(string username, string password, int hashed, int isAdmin) {
    this->username = username;
    this->password = password;
    this->hashed = hashed;
    this->isAdmin = isAdmin;
}

User::User(boost::optional<User> anOptional) {
    if(anOptional){
        this->username = anOptional->username;
        this->password = anOptional->password;
        this->hashed = anOptional->hashed;
        this->isAdmin = anOptional->isAdmin;
    }
}

//Sets Username
void User::setUsername(string username) {
    this->username = username;
}

//Gets Username
string User::getUsername() const {
    return username;
}

//Sets Password
void User::setPassword(string password) {
    this->password = password;
}

//Gets Password
string User::getPassword() const {
    return password;
}

void User::setEncryptStatus(int hashed) {
    this->hashed = hashed;
}

int User::getEncryptStatus() {
    return hashed;
}

void User::setAdminStatus(int isAdmin) {
    this->isAdmin = isAdmin;
}

int User::getAdminStatus() {
    return isAdmin;
}

//Lists user's list in terminal
void User::listUserList() {
    cout << "ISBN | Book-Title | Book-Author" << endl;
    for (auto &book: this->UserList) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << endl;
    }

    cout << "Total items in list: " << this->UserList.size();
}

void User::addToUserList(Book book) {
    this->UserList.push_back(book);
}


void User::getUserShoppingList(BookstoreInventory inventory) {
    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    vector<string> bookISBNs;

    sqlite3 *usersDB;
    string findQuery = "SELECT * FROM shoppingCart where username = ?";

    string bookList;

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *find = NULL;
            if (sqlite3_prepare_v2(usersDB, findQuery.c_str(), findQuery.length(), &find, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(find, 1, username.c_str(), username.length(), NULL);
                sqlite3_exec(usersDB, sqlite3_expanded_sql(find), this->searchUserShoppingCartCallback, &bookISBNs,
                             nullptr);
                sqlite3_reset(find);
                sqlite3_finalize(find);
            }
        }
    }
    catch (...) {
        cout << "Error finding user in database." << endl;
    }
    sqlite3_close(usersDB);

    for(auto &isbn: bookISBNs){
        boost::optional<Book> book = inventory.searchForBookByISBN(isbn);
        if(book){
            UserShoppingList.insert(book);
        }
    }
}

void User::listUserShoppingList() {
    cout << "ISBN | Book-Title | Book-Author | Year Published | Publisher | Description | Genre | Price | Quantity"
         << endl;
    for (auto &book: this->UserShoppingList) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year << " | "
             << book.publisher << " | " << book.description << " | " << book.genre << " | " << book.msrp << " | "
             << book.quantity << endl;
    }
}

void User::addToUserShoppingList(Book book) {
    this->UserShoppingList.insert(book);
}

void User::saveUserShoppingList() {
    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *usersDB;
    string insertQuery = "INSERT INTO shoppingCart VALUES(?, ?) ON CONFLICT (username) DO UPDATE SET cart = ?";

    string bookList;

    for (auto &book: this->UserShoppingList) {
        bookList += book.ISBN + ",";
    }

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *insert = NULL;
            if (sqlite3_prepare_v2(usersDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) ==
                SQLITE_OK) {
                sqlite3_bind_text(insert, 1, username.c_str(), username.length(),
                                  NULL);
                sqlite3_bind_text(insert, 2, bookList.c_str(), bookList.length(), NULL);
                sqlite3_bind_text(insert, 3, bookList.c_str(), bookList.length(), NULL);

                sqlite3_step(insert);
                sqlite3_reset(insert);
            }
            sqlite3_finalize(insert);
        }
    }
    catch (...) {
        cout << "Error saving shopping list." << endl;
    }
    sqlite3_close(usersDB);
}

int User::searchUserShoppingCartCallback(void *data, int argc, char **argv, char **azColName) {
    // https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
    // data: is 4th argument passed in sqlite3_exec command
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    vector<string> *bookISBNs = static_cast<vector<string> *>(data); // cast data to user object

    // Returns first token
    char *token = strtok(argv[1], ",");

    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
        bookISBNs->push_back(token);
        token = strtok(NULL, ",");
    }

    return argc;
}

deque<Book> User::getUserList() {
    return this->UserList;
}

void User::checkoutWithUserShoppingList(string username) {
    float total = 0;
    string name;
    if (username == "none") {
        name = "Guest";
    } else {
        name = username;
    }

    cout << "---Sales Receipt---" << endl;
    cout << "Shopper: " << name << endl;
    cout << "Items purchased:" << endl;
    cout << "Title  |  Price" << endl;
    for (auto &book: this->UserShoppingList) {
        cout << book.title << " | "  << book.msrp << endl;
        total += book.msrp;
    }

    cout << "SubTotal: " << total << endl;
    cout << "Tax: " << total * .06 << endl;
    cout << "Total: " << total + (total * .06) << endl;

    // Clear list and save on checkout
    this->UserShoppingList.clear();
    saveUserShoppingList();
}

