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

}

//Makes a User
User::User(string username, string password) {
	this->username = username;
	this->password = password;
}

//Sets Username
void User::setUsername(string username) {
	this->username = username;
}

//Gets Username
string User::getUsername() {
	return username;
}

//Sets Password
void User::setPassword(string password) {
	this->password = password;
}

//Gets Password
string User::getPassword() {
	return password;
}

//Updates Password
void User::updatePassword(string username, string password) {

}
