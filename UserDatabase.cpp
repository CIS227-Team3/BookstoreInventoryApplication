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

bool UserDatabase::searchUser(string username) {
	bool userFound = false;
    const char* dbName = "../users.db";

    sqlite3 *usersDB;
    string findQuery = "SELECT * FROM USERS where username = '" + username + "';";

    try{
        if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
            sqlite3_stmt *select = NULL;
            if (sqlite3_prepare_v2(usersDB, findQuery.c_str(), findQuery.length(), &select, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(select, 1, username.c_str(), username.length(), NULL);

                auto returnedColumns = sqlite3_exec(usersDB, findQuery.c_str(), this->searchUserCallback, nullptr, nullptr);
                sqlite3_reset(select);
                if(returnedColumns == 4){
                    userFound = true;
                }
            }
        }
    }
    catch (...){
        cout << "Error finding user in database." << endl;
    }
	return userFound;
}

void UserDatabase::addUser() {
	string username;
	string password;
    short int hashed = 1; //default because password gets hashed on entry
    short int isAdmin;

    string tempDBName = "../users.db";
    const char* dbName = tempDBName.c_str();

    sqlite3 *usersDB;
    string insertQuery = "INSERT INTO users VALUES(?, ?, ?, ?)";

	// prompts user to enter a username
	cout << "Please enter a username: " << endl;
	cin >> username;
	// checks to make sure that user does not already exist
	if (!searchUser(username)) {
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

        try{
            if (sqlite3_open(dbName, &usersDB) == SQLITE_OK) {
                sqlite3_stmt *insert = NULL;
                if (sqlite3_prepare_v2(usersDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) == SQLITE_OK) {
                    sqlite3_bind_text(insert, 1, username.c_str(), username.length(), NULL);
                    sqlite3_bind_text(insert, 2, hashedPassword.c_str(), hashedPassword.length(), NULL);
                    sqlite3_bind_int(insert, 3, hashed);
                    sqlite3_bind_int(insert, 4, isAdmin);

                    sqlite3_step(insert);
                    sqlite3_reset(insert);

                    Users.push_back(User(username, password, hashed, isAdmin));
                }
                sqlite3_finalize(insert);
            }
        }
        catch (...){
            cout << "Error adding user to database." << endl;
        }
	}
    else{
        cout << "Username already taken" << endl;
    }
}

int UserDatabase::searchUserCallback(void *notUsed, int argc, char **argv, char **azColName) {
    // https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    // only goes in here if statement finds user
    return argc;
}

/*
void UserDatabase::updateUser() {
	string username;
	string newPassword;
	cout << "Please enter your username:" << endl;
	cin >> username;
	// checks that user is in database
	while (!searchUser(username)) {
		cout << "Username not found. Please re-enter your username." << endl;
		cin >> username;
	}
	cout << "Please enter your new password:" << endl;
	cin >> newPassword;
	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username == Users.at(i).getUsername()) {
			// sets the password as the matching user
			Users.at(i).setPassword(newPassword);
			// looks through csv file for username for row number
			string filename = "users.csv";
			rapidcsv::Document doc(filename, rapidcsv::LabelParams(0, 0));
			unsigned int rowIndex;
			try {
				unsigned int numRows = doc.GetRowCount();
				// gets the row number containing the username
				for (unsigned int i = 0; i < numRows; ++i) {
					if (username == doc.GetCell<string>(0, i)) {
						rowIndex = i;
					}
				}
				// sets the password cell with the new password
				// column for password = 1
				doc.SetCell(1, rowIndex, newPassword);
				cout << "User successfully updated";
			}
			catch (...) {
				cout << "Unable to update user. Please try again." << endl;
			}
		}
	}
}
*/
