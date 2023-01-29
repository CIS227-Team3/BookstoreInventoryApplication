/*
 * User.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "User.h"

User::User() {
	username = "none";
	password = "none";

}

User::User(string username, string password) {
	this->username = username;
	this->password = password;
}

void User::setUsername(string username) {
	this->username = username;
}

string User::getUsername() {
	return username;
}

void User::setPassword(string password) {
	this->password = password;
}

string User::getPassword() {
	return password;
}

void User::updatePassword(string username, string password) {
	// checks to make sure that user exists
	unsigned short int userIndex;
	User user;
	if (searchForUser(username)) {
		for (unsigned short int i = 0; i < users.size(); ++i) {
			user = users.at(i);
			if (username == user.getUsername()) {
				// sets user index to current index of users to be updated
				userIndex = i;
			}
		}

	User userToUpdate = users.at(userIndex);
	userToUpdate.setPassword(password);
	cout << "Password successfully updated." << endl;


	}

	else {
		cout << "User " << username << " was not found. Please re-enter the username or create a new login." << endl;
	}
}

// opens file and gets a vector of users
vector<User> User::getUsers() {
	vector<string> oneUser;
	string userLine;
	string userInfo;
	string username;
	string password;
	string filename = "users.csv";
	ifstream usersFile(filename);

	if (usersFile.is_open()) {
		// gets the username data on each
		while (getline(usersFile, userLine)) {
			oneUser.clear();
			stringstream ss(userLine);

			while (getline(ss, userInfo, ',')) {
				oneUser.push_back(userInfo);
			}

			username = oneUser.at(0);
			password = oneUser.at(1);

			User user(username, password);

			users.push_back(user);

			usersFile.close();
		}
	}

	else {
		cout << "Unable to access user file. Please try again." << endl;
	}

	return users;
}

bool User::validateUser(string username, string password) {
	bool isValidUser = false;

	getUsers();
	User user;
	for (unsigned short int i = 0; i < users.size(); ++i) {
		user = users.at(i);
		// checks to make sure that username and password match a record in the user file
		if (username == user.getUsername() && password == user.getPassword()) {
			isValidUser = true;
		}

		else if (username == user.getUsername() && password != user.getPassword()) {
			cout << "Incorrect password entered. Please re-enter or reset password." << endl;
			isValidUser = false;
		}
	}

	return isValidUser;
}

bool User::searchForUser(string searchUsername) {
	getUsers();
	User user;
	bool userFound;

	for (unsigned short int i = 0; i < users.size(); ++i) {
		user = users.at(i);
		if (searchUsername == user.getUsername()) {
			userFound = true;
		}

		else {
			cout << "User " << searchUsername << " was not found." << endl;
			userFound = false;
		}
	}

	return userFound;
}

// adds a new user to the csv file containing users
void User::createUser(string username, string password) {
	User user(username, password);

	// searches user file to make sure that the user does not already exist
	if (!searchForUser(username)) {
		// if the user is not found, it is added to the user file
		ofstream usersFile("users.csv");

		if (usersFile.is_open()) {
			usersFile << user.getUsername() << ", " << user.getPassword() << "\n";
			usersFile.close();

			// adds user to users vector
			users.push_back(user);
		}

		else {
			cout << "Unable to access users file. Please try again." << endl;
		}

	}

	else {
		cout << "Username not found. Please enter or update your password." << endl;
	}
