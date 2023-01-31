/*
 * User.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <string>

using namespace std;

#ifndef USER_H_
#define USER_H_

//CLass User
class User {
public:
	User();
	User(string username, string password);
	void setUsername(string username);
	string getUsername();
	void setPassword(string password);
	string getPassword();
	void updatePassword(string username, string password);

private:
	string username;
	string password;
};

#endif /* USER_H_ */
