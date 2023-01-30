#include "UserDatabase.h"

UserDatabase::UserDatabase() {
    addInitialUsers();
}

void UserDatabase::addInitialUsers() {
    readUsersFile(this->Users);
}

void UserDatabase::updateUserDatabase() {
	// creates a temporary csv file to store all of the user data in the Users vector.
	fstream userFileUpdate;

	// opens existing file or creates new file
	userFileUpdate.open("tempUsers.csv", ios::out);

	try {
		for (unsigned int i = 0; i < Users.size(); ++i) {
			userFileUpdate << Users.at(i).getUsername()
					<< "," << Users.at(i).getPassword() << "\n";
		}

		// removes the old file
		remove("users.csv");

		// renames the temporary file with the old file's name
		rename("tempUsers.csv", "users.csv");

		cout << "User file successfully updated." << endl;
	}

	catch (...) {
		cout << "Updating user file failed. Please try again." << endl;
	}

	// closes the temporary file
	userFileUpdate.close();
}

bool UserDatabase::searchUser(string username) {
	bool userFound = false;

	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username == Users.at(i).getUsername());
		userFound = true; // if user is found, returns true, otherwise, userFound will remain false
	}

	return userFound;
}

bool UserDatabase::validUser(string username, string password) {
	bool userValid = false;

	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username == Users.at(i).getUsername() && password == Users.at(i).getPassword());
		userValid = true;
	}

	return userValid;
}

void UserDatabase::addUser() {
	string username;
	string password;

	// prompts user to enter a username
	cout << "Please enter a username: " << endl;
	cin >> username;

	// checks to make sure that user does not already exist
	if (!searchUser(username)) {
		// prompts user to enter a password
		cout << "Please enter a password: " << endl;

		// if the user does not enter a password, they are prompted to enter one
		while (password.length() < 1) {
			cout << "Please enter a password" << endl;
			cin >> password;
		}

		// adds new user to the users vector
		Users.push_back(User(username, password));
		cout << "User successfully added." << endl;
	}
}

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

	while (newPassword.length() < 1) {
		cout << "Please enter a new password:" << endl;
		cin >> newPassword;
	}

	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username == Users.at(i).getUsername()) {
			// sets the password as the matching user
			Users.at(i).setPassword(newPassword);
			cout << "User successfully updated";
		}
	}
}
