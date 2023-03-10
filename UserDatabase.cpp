#include "UserDatabase.h"

//Constructor
UserDatabase::UserDatabase() {
    cout << "Loading users..." << endl;
    cout << "Finished loading users." << endl;
}

bool UserDatabase::loginUser(string username, string password) {
    bool loginUser = false;
    // instantiates md5 object for hashing
    MD5 md5;
    // hashes input password
    string hashedPassword = md5(password);

    boost::optional<User> user = searchUser(username);

    if(user){
        if(hashedPassword == user->getPassword()){
            loginUser = true;
            this->currentUser = user;
        } else {
            cout << "Incorrect password entered. Please re-try login" << endl;
            loginUser = false;
        }
    }

    if (loginUser == false) {
        cout << "Login failed. Please retry login." << endl;
    }

    return loginUser;
}

User UserDatabase::getCurrentUser() {
    return this->currentUser;
}

boost::optional<User> UserDatabase::searchUser(const string &username) {
    const char *dbName = "../users.db";
    User user;

    sqlite3 *usersDB;
    string findQuery = "SELECT * FROM users where username = ?";

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *find = NULL;
            if (sqlite3_prepare_v2(usersDB, findQuery.c_str(), findQuery.length(), &find, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(find, 1, username.c_str(), username.length(), NULL);
                sqlite3_exec(usersDB, sqlite3_expanded_sql(find), this->searchUserCallback, &user, nullptr);
                sqlite3_reset(find);
                sqlite3_finalize(find);
                sqlite3_close(usersDB);

                if(user.getUsername() == "none"){
                    return boost::none;
                }
                return user;
            }
        }
    }
    catch (...) {
        cout << "Error finding user in database." << endl;
    }
    return boost::none;
}

void UserDatabase::addUser() {
    string username;
    string password;
    short int hashed = 1; //default because password gets hashed on entry
    short int isAdmin;

    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *usersDB;
    string insertQuery = "INSERT INTO users VALUES(?, ?, ?, ?)";

    // prompts user to enter a username
    cout << "Please enter a username: " << endl;
    cin >> username;
    // checks to make sure that user does not already exist
    boost::optional<User> user = searchUser(username);
    if (!user) {
        // prompts user to enter a password
        cout << "Please enter a password: " << endl;
        cin >> password;

        // instantiates md5 object for hashing
        MD5 md5;
        // hashes input password
        string hashedPassword = md5(password);

        cout << "Should user be admin 1 for yes or 0 for no: " << endl;
        while (true) {
            if (cin >> isAdmin && (isAdmin == 0 || isAdmin == 1)) { // if the user entered an integer
                cin.ignore(1000, '\n');
                break;
            } else {
                cout << "Input cannot negative, non-numeric, or out-of-range. Please enter 0 or 1." << endl;

                cin.clear();  // clears error state if the user entered a string or char.
                cin.ignore(1000, '\n'); // clears the input causing error from stream.
            }
        }

        try {
            if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
                sqlite3_stmt *insert = NULL;
                if (sqlite3_prepare_v2(usersDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) ==
                    SQLITE_OK) {
                    sqlite3_bind_text(insert, 1, username.c_str(), username.length(), NULL);
                    sqlite3_bind_text(insert, 2, hashedPassword.c_str(), hashedPassword.length(), NULL);
                    sqlite3_bind_int(insert, 3, hashed);
                    sqlite3_bind_int(insert, 4, isAdmin);

                    sqlite3_step(insert);
                    sqlite3_reset(insert);
                }
                sqlite3_finalize(insert);
            }
        }
        catch (...) {
            cout << "Error adding user to database." << endl;
        }
        sqlite3_close(usersDB);
    } else {
        cout << "Username already taken" << endl;
    }
}

void UserDatabase::addUser(User user) {
    string username = user.getUsername();
    string password = user.getPassword();
    short int hashed = user.getEncryptStatus();
    short int isAdmin = user.getAdminStatus();

    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *usersDB;
    string insertQuery = "INSERT INTO users VALUES(?, ?, ?, ?)";

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *insert = NULL;
            if (sqlite3_prepare_v2(usersDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) ==
                SQLITE_OK) {
                sqlite3_bind_text(insert, 1, username.c_str(), username.length(), NULL);
                sqlite3_bind_text(insert, 2, password.c_str(), password.length(), NULL);
                sqlite3_bind_int(insert, 3, hashed);
                sqlite3_bind_int(insert, 4, isAdmin);

                sqlite3_step(insert);
                sqlite3_reset(insert);
            }
            sqlite3_finalize(insert);
        }
    }
    catch (...) {
        cout << "Error adding user to database." << endl;
    }
    sqlite3_close(usersDB);
}

void UserDatabase::updateUser(User user) {
    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    string username = user.getUsername();
    string password = user.getPassword();
    int encrypted = user.getEncryptStatus();
    int isAdmin = user.getAdminStatus();

    sqlite3 *usersDB;
    string updateQuery = "UPDATE users SET username = ?, password = ?, hash = ?, isAdmin = ? WHERE username = ?";

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *update = NULL;
            if (sqlite3_prepare_v2(usersDB, updateQuery.c_str(), updateQuery.length(), &update, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(update, 1, username.c_str(), username.length(), NULL);
                sqlite3_bind_text(update, 2, password.c_str(), password.length(), NULL);
                sqlite3_bind_int(update, 3, encrypted);
                sqlite3_bind_int(update, 4, isAdmin);
                sqlite3_bind_text(update, 5, username.c_str(), username.length(), NULL);

                sqlite3_step(update);
                sqlite3_reset(update);
            }
            sqlite3_finalize(update);
        }
    }
    catch (...) {
        cout << "Error updating user." << endl;
    }
    sqlite3_close(usersDB);
}

void UserDatabase::updateUserPassword() {
    string username;
    string password;

    cout << "Please enter username of user whose password will be updated: " << endl;
    getline(cin, username);

    boost::optional<User> user = searchUser(username);
    if (user) {
        cout << "Please enter new password: " << endl;
        getline(cin, password);

        // instantiates md5 object for hashing
        MD5 md5;
        // hashes input password
        string hashedPassword = md5(password);

        user->setPassword(hashedPassword);

        updateUser(user);
    } else {
        cout << "Username not found" << endl;
    }
}

int UserDatabase::searchUserCallback(void *data, int argc, char **argv, char **azColName) {
    // https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
    // data: is 4th argument passed in sqlite3_exec command
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    // only goes in here if statement finds user
    User *user = static_cast<User *>(data); // cast data to user object
    user->setUsername(argv[0]);
    user->setPassword(argv[1]);
    user->setEncryptStatus(stoi(argv[2]));
    user->setAdminStatus(stoi(argv[3]));
    return argc;
}

int UserDatabase::searchShopperCallback(void *data, int argc, char **argv, char **azColName) {
    // https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
    // data: is 4th argument passed in sqlite3_exec command
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    // only goes in here if statement finds user
    User *user = static_cast<User *>(data);
    user->setUsername(argv[1]);
    return argc;
}

string UserDatabase::searchShopper(const string &username){
    const char *dbName = "../users.db";
    User foundUser;

    sqlite3 *usersDB;
    string findQuery = "SELECT * FROM shoppers where name = ?";

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *find = NULL;
            if (sqlite3_prepare_v2(usersDB, findQuery.c_str(), findQuery.length(), &find, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(find, 1, username.c_str(), username.length(), NULL);
                sqlite3_exec(usersDB, sqlite3_expanded_sql(find), this->searchShopperCallback, &foundUser, nullptr);
                sqlite3_reset(find);
                sqlite3_finalize(find);
                sqlite3_close(usersDB);

                if(username == "none"){
                    return "none";
                }
                return foundUser.getUsername();
            }
        }
    }
    catch (...) {
        cout << "Error finding user in database." << endl;
    }
    return "none";
}

void UserDatabase::addShopper(string email, string name, float total) {
    string tempDBName = "../users.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *usersDB;
    string insertQuery = "INSERT INTO shoppers VALUES(?, ?, ?)";

    try {
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *insert = NULL;
            if (sqlite3_prepare_v2(usersDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) ==
                SQLITE_OK) {
                sqlite3_bind_text(insert, 1, email.c_str(), email.length(), NULL);
                sqlite3_bind_text(insert, 2, name.c_str(), name.length(), NULL);
                sqlite3_bind_double(insert, 3, total);

                sqlite3_step(insert);
                sqlite3_reset(insert);
            }
            sqlite3_finalize(insert);
        }
    }
    catch (...) {
        cout << "Error adding user to database." << endl;
    }
    sqlite3_close(usersDB);
}
