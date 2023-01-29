/*
 * User.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifndef USER_H_
#define USER_H_

class User {
public:
	User();
	User(string username, string password);
	void setUsername(string username);
	string getUsername();
	void setPassword(string password);
	string getPassword();
	void updatePassword(string username, string password);

	// void deleteUser(string username); // possibly used in the future

private:
	string username;
	string password;
	vector<User> users;
	vector<User> getUsers();
	bool searchForUser(string username);
	bool validateUser(string username, string password);
	void createUser(string username, string password);
};

#endif /* USER_H_ */
