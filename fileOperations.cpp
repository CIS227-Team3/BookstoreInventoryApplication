/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "fileOperations.h"

//Reads from a file of books
void readBooksFile(string filePath, deque<Book> &Inventory) {
    unsigned int added = 0;
    unsigned int failed = 0;

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0));

    for (int i = 0; i < doc.GetRowCount(); ++i) {
        try {
            string ISBN = doc.GetRowName(i);
            string title = doc.GetCell<string>("Book-Title", ISBN);
            string author = doc.GetCell<string>("Book-Author", ISBN);
            int year = doc.GetCell<int>("Year-Of-Publication", ISBN);
            string publisher = doc.GetCell<string>("Publisher", ISBN);

            Inventory.push_back(Book(ISBN, title, author, year, publisher));
            added++;
        }
        catch (...) {
            cout << "Problem reading book in CSV with ISBN: " << doc.GetRowName(i) << ", did not add to inventory."
                 << endl;
            failed++;
        }
    }
    cout << "Added " << added << " books to inventory. Failed adding: " << failed << endl;
}

//Reads from a file of users
void readUsersFile(list<User> &Users) {
	string tmpFilename = "../users.db";
	const char* filename = tmpFilename.c_str(); // stores filename as a c_string to be used in sqlite commands

	string rowCountQuery = "SELECT COUNT(*) FROM users as rowCount";
	string dataQuery = "SELECT * FROM users";
	int numRows = 0;

	string username;
	string password;
	int isHashed;

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
				cout << "Number of rows: " << numRows << endl;
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

				User user(username, password, isHashed);
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
    cout << "File can be found at: " << filesystem::canonical(filename) << endl;
    out << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Genre,Description" << endl;

    for (auto &book: Inventory) {
        out << book.ISBN << ",";
        out << book.title << ",";
        out << book.author << ",";
        out << book.year << ",";
        out << book.publisher << ",";
        out << book.genre << ",";
        out << book.description << "," << endl;
    }

    out.close();
    cout << "Done writing file." << endl;
}

