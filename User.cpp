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

}
