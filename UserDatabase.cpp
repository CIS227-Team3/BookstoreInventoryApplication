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

	// searches for the username in the Users vector
	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username.compare(Users.at(i).getUsername()) == 0) {
			cout << "Username: " << Users.at(i).getUsername() << endl;

			// makes sure that the password matches
			if (password.compare(Users.at(i).getPassword()) == 0) {
				loginUser = true;
			}

			else {
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
/*
bool UserDatabase::searchUser(string username) {
	bool userFound = false;

	for (unsigned int i = 0; i < Users.size(); ++i) {
		if (username == Users.at(i).getUsername())
		userFound = true; // if user is found, returns true, otherwise, userFound will remain false
	}

	return userFound;
}
*/

/*
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
		cin >> password;

		// creates string with row data to add to csv file.
		vector<string>rowData;
		rowData.push_back(username);
		rowData.push_back(password);

		// adds new user to the users vector
		Users.push_back(User(username, password));

		// instantiates new csv document object
		string filename = "users.csv";
		rapidcsv::Document doc(filename, rapidcsv::LabelParams(0, 0));

		try {
			// gets number of rows to place new user
			unsigned int numRows = doc.GetRowCount();
			doc.InsertRow(numRows, rowData);

			cout << "User successfully added." << endl;
		}

		catch (...) {
			cout << "Error adding user. Please try again." << endl;
		}

		doc.Clear();
	}
}
*/

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
