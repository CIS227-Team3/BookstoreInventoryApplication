#include "UserDatabase.h"

//Constructor
UserDatabase::UserDatabase() {
    cout << "Loading users..." << endl;
    addInitialUsers();
}

//Adds initial users to database
void UserDatabase::addInitialUsers() {
    readUsersFile(this->Users);
    cout << "Finished loading users." << endl;
}

bool UserDatabase::loginUser(string username, string password) {
    bool loginUser = false;
	// instantiates md5 object for hashing
    MD5 md5;
	// hashes input password
    string hashedPassword = md5(password);

    // searches for the username in the Users list
    for (auto const& user : Users) {
        if (username.compare(user.getUsername()) == 0) {
            cout << "Username: " << user.getUsername() << endl;

            // makes sure that the password matches
            if (hashedPassword.compare(user.getPassword()) == 0) {
                loginUser = true;
				// stores the username of the logged-in user
                this->currentUser = user;
            } else {
                cout << "Incorrect password entered. Please re-try login" << endl;
                loginUser = false;
            }
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
