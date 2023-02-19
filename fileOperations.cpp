/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "fileOperations.h"

//Reads from a file of books
void readBooksFile(string filePath, deque<Book> &Inventory) {
	string selectQuery = "SELECT * FROM books"; // table data is stored in books table in books.db
	string rowCountQuery = "SELECT COUNT(*) FROM books as rowCount";
	int numRows = 0;

	// converts string to cstring so filename can be used as parameter in sqlite_open function
	// reference: https://www.geeksforgeeks.org/convert-string-char-array-cpp/
	const char* filename = filePath.c_str();

	// reads user database information
	sqlite3 *bookDB;
	try {
		// gets the number of rows in the database
		// checks that database opened successfully
		if (sqlite3_open(filename, &bookDB) == SQLITE_OK) {

			// instantiates statement object
			sqlite3_stmt *rowCount;
			sqlite3_prepare_v2(bookDB, rowCountQuery.c_str(), rowCountQuery.length(), &rowCount, nullptr);

			// checks that the end of the database rows has not been reached
			if (sqlite3_step(rowCount) != SQLITE_DONE) {
				numRows = sqlite3_column_int(rowCount, 0); // row count is in the first (and only) column
				cout << "Number of books found: " << numRows << endl;
			}

			// sql statement destructor
			sqlite3_finalize(rowCount);
		}

		// gets user information from the database
		sqlite3_stmt *query;
		sqlite3_prepare_v2(bookDB, selectQuery.c_str(), selectQuery.length(), &query, nullptr);

		for (int i = 0; i < numRows; ++i) {
			sqlite3_step(query);
			string ISBN = (const char*)sqlite3_column_text(query, 0); // column 0 contains ISBN
			string title = (const char*)sqlite3_column_text(query, 1); // column 1 contains title
			string author = (const char*)sqlite3_column_text(query, 2); // column 2 contains author
			int year = sqlite3_column_int(query, 3); // column 3 contains year
			string publisher = (const char*)sqlite3_column_text(query, 4); // column 4 contains publisher
			string description = (const char*)sqlite3_column_text(query, 5); // column 5 contains description
			string genre = (const char*)sqlite3_column_text(query, 6); // column 6 contains genre
			float msrp = sqlite3_column_double(query, 7); // column 7 contains msrp
			int quantity = sqlite3_column_int(query, 8); // column 8 contains quantity

			// creates a book object and adds it to inventory
			Book book(ISBN, title, author, year, publisher, description, genre, msrp, quantity);
			Inventory.push_back(book);
		}

		// statement object destructor
		sqlite3_finalize(query);

	}

	catch(...) {
		cout << "Error opening or accessing database." << endl;
	}

	// closes database connection
	sqlite3_close(bookDB);
}

//Reads from a file of users
void readUsersFile(list<User> &Users) {
	string tmpFilename = "users.db";
	const char* filename = tmpFilename.c_str(); // stores filename as a c_string to be used in sqlite commands

	string rowCountQuery = "SELECT COUNT(*) FROM users as rowCount";
	string dataQuery = "SELECT * FROM users";
	int numRows = 0;

	string username;
	string password;
	int isHashed;
	int isAdmin;

	// declares userDB connection
	sqlite3 *userDB;

	try {
		// checks that database file successfully opened
		if (sqlite3_open(filename, &userDB) == SQLITE_OK) {
			// gets the number of rows in the database
			sqlite3_stmt *rowCount;
			sqlite3_prepare_v2(userDB, rowCountQuery.c_str(), rowCountQuery.length(), &rowCount, nullptr);

			if (sqlite3_step(rowCount) != SQLITE_DONE) {
				numRows = sqlite3_column_int(rowCount, 0);
				// cout << "Number of rows: " << numRows << endl;
			}

			// statement destructor
			sqlite3_finalize(rowCount);

			// gets user information from the database
			sqlite3_stmt *query;
			sqlite3_prepare_v2(userDB, dataQuery.c_str(), dataQuery.length(), &query, nullptr);

			for (int i = 0; i < numRows; ++i) {
				sqlite3_step(query);
				username = (const char*)sqlite3_column_text(query, 0); // column 0 contains username
				password = (const char*)sqlite3_column_text(query, 1); // column 1 contains password
				isHashed = sqlite3_column_int(query, 2); // column 2 contains hash status
				isAdmin = sqlite3_column_int(query, 3);

				User user(username, password, isHashed, isAdmin);
				Users.push_back(user);
			}

			// statement destructor
			sqlite3_finalize(query);
		}
	}

	catch (...) {
		cout << "Error opening and accessing database." << endl;
	}

	sqlite3_close(userDB);
}

void writeBooksFile(deque<Book> &Inventory) {
    string filename = "../printBooks.csv";
    ofstream out(filename, std::ios::out);
    cout << "File can be found as: " << filename << endl;
    out << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Genre,Description,MSRP,Quantity" << endl;

    for (auto &book: Inventory) {
        out << book.ISBN << ",";
        out << book.title << ",";
        out << book.author << ",";
        out << book.year << ",";
        out << book.publisher << ",";
        out << book.genre << ",";
        out << book.description << ",";
        out << book.msrp << ",";
        out << book.quantity << "," << endl;
    }

    out.close();
    cout << "Done writing file." << endl;
}

