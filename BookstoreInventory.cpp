#include "BookstoreInventory.h"

//Constructor
BookstoreInventory::BookstoreInventory() {
    cout << "Loading books..." << endl;
    cout << "Finished loading books. " << endl;
}

void BookstoreInventory::displayLatestFive() {
	const char* dbName = "../books.db";
	// selects five records with the five most recent timestamps
	string selectQuery = "SELECT title FROM books ORDER BY dateAdded DESC LIMIT 5";
	vector<string> topFive; // stores five most recently added books in database

	string title;

	sqlite3* bookDB;

	if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {
		sqlite3_stmt *select;
		if (sqlite3_prepare_v2(bookDB, selectQuery.c_str(), selectQuery.length(), &select, nullptr) == SQLITE_OK) {

			while (sqlite3_step(select) != SQLITE_DONE) {
				title = (const char*)sqlite3_column_text(select, 0);
				topFive.push_back(title);
			}
		}
	}

	cout << "--- FIVE LATEST ADDITIONS TO INVENTORY ---" << endl;
	for (unsigned int i = 0; i < 5; ++i) {
		cout << topFive.at(i) << endl;
	}
}

//Watches for Cases, so we can use lower or upper case characters
bool caseInsensitiveMatch(string string1, string string2) {
    //convert string1 and string2 into lower case strings
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
    if (string1.compare(string2) == 0) {
        return true;
    }
    return false;
}

//Searches for a specific book within BookstoreInventory
boost::optional<Book> BookstoreInventory::searchForBook(string title) {
    const char *dbName = "../books.db";
    Book book;

    sqlite3 *bookDB;
    string findQuery = "SELECT * FROM books where title like ?";

    title.push_back('%'); // appending % searches for any values starting with title (case-insensitive)

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {
            sqlite3_stmt *find = NULL;
            if (sqlite3_prepare_v2(bookDB, findQuery.c_str(), findQuery.length(), &find, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(find, 1, title.c_str(), title.length(), NULL);
                sqlite3_exec(bookDB, sqlite3_expanded_sql(find), this->searchBookCallback, &book, nullptr);
                sqlite3_reset(find);
                sqlite3_finalize(find);
                sqlite3_close(bookDB);

                title.pop_back();

                if (book.title == "none") {
                	cout << "Book with title " << title << " not found." << endl;
                    return boost::none;
                } else {
                    cout << "Book details: " << endl;
                    cout << "ISBN: " << book.ISBN << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "Year Published: " << book.year << endl;
                    cout << "Publisher: " << book.publisher << endl;
                    cout << "Description: " << book.description << endl;
                    cout << "Genre: " << book.genre << endl;
                    cout << "Price: $" << book.msrp << endl;
                    cout << "Quantity in Stock: " << book.quantity << endl;
                    cout << "Date Added: " << book.dateAdded << endl;
                    return book;
\
                    writeToLog("Found a book in the database");
                }
            }
        }
    } catch (...) {
        cout << "Error finding book in database." << endl;
    }
    return boost::none;
}

// Adds a new book to the database
void BookstoreInventory::addBook(Book book) {
    string tempDBName = "../books.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *bookDB;
    string insertQuery = "INSERT INTO books(isbn, title, author, year, publisher, description, genre, msrp, quantity, dateAdded) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ON CONFLICT (isbn) DO UPDATE SET quantity = quantity + 1";

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {

            sqlite3_stmt *insert = NULL;
            if (sqlite3_prepare_v2(bookDB, insertQuery.c_str(), insertQuery.length(), &insert, nullptr) == SQLITE_OK) {
                string ISBN = book.ISBN;
                string title = book.title;
                string author = book.author;
                int year = book.year;
                string publisher = book.publisher;
                string description = book.description;
                string genre = book.genre;
                float msrp = book.msrp;
                int quantity = book.quantity;
                string dateAdded = book.dateAdded;

                // binds values to ? in prepared insert query statement
                // text (statementName, paramNum, value (converted to c_str), length of value, pointer)
                // int (statementName, paramNum, intVal)
                sqlite3_bind_text(insert, 1, ISBN.c_str(), ISBN.length(), NULL);
                sqlite3_bind_text(insert, 2, title.c_str(), title.length(), NULL);
                sqlite3_bind_text(insert, 3, author.c_str(), author.length(), NULL);
                sqlite3_bind_int(insert, 4, year);
                sqlite3_bind_text(insert, 5, publisher.c_str(), publisher.length(), NULL);
                sqlite3_bind_text(insert, 6, description.c_str(), description.length(), NULL);
                sqlite3_bind_text(insert, 7, genre.c_str(), genre.length(), NULL);
                sqlite3_bind_double(insert, 8, msrp);
                sqlite3_bind_int(insert, 9, quantity);
                sqlite3_bind_text(insert, 10, dateAdded.c_str(), dateAdded.length(), NULL);

                sqlite3_step(insert);
                sqlite3_reset(insert);

                cout << "Book with title " << title << " successfully added to database." << endl;
            }
            sqlite3_finalize(insert);
        }
    }

    catch (...) {
        cout << "Error adding book to database." << endl;
    }

    sqlite3_close(bookDB);

}

// deletes a book from the database
void BookstoreInventory::deleteBook(string title) {
    string tempDBName = "../books.db";
    const char *dbName = tempDBName.c_str();

    sqlite3 *bookDB;
    string deleteQuery = "DELETE FROM books WHERE title like ?";

    title.push_back('%'); // appending % searches for any values starting with title (case-insensitive)

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {

            sqlite3_stmt *del = NULL;
            if (sqlite3_prepare_v2(bookDB, deleteQuery.c_str(), deleteQuery.length(), &del, nullptr) == SQLITE_OK) {

                // binds values to ? in prepared insert query statement
                // text (statementName, paramNum, value (converted to c_str), length of value, pointer)
                // int (statementName, paramNum, intVal)
                sqlite3_bind_text(del, 1, title.c_str(), title.length(), NULL);

                sqlite3_step(del);
                sqlite3_reset(del);

                title.pop_back();
                cout << "Book with title " << title << " successfully deleted." << endl;
            }
            sqlite3_finalize(del);
        }
    }

    catch (...) {
        cout << "Error deleting book from database." << endl;
    }

    sqlite3_close(bookDB);

}

// updates the description of a book already in inventory
void BookstoreInventory::updateDescription(string title, string description) {
    string tempDBName = "../books.db";
    const char *dbName = tempDBName.c_str();

    Book bookUpdate;

    sqlite3 *bookDB;
    string updateQuery = "UPDATE books SET description = ? WHERE title like ?";

    title.push_back('%'); // appending % searches for any values starting with title (case-insensitive)

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {

            sqlite3_stmt *update = NULL;
            if (sqlite3_prepare_v2(bookDB, updateQuery.c_str(), updateQuery.length(), &update, nullptr) == SQLITE_OK) {

                // binds values to ? in prepared insert query statement
                // text (statementName, paramNum, value (converted to c_str), length of value, pointer)
                // int (statementName, paramNum, intVal)
                sqlite3_bind_text(update, 1, description.c_str(), description.length(), NULL);
                sqlite3_bind_text(update, 2, title.c_str(), title.length(), NULL);

                sqlite3_step(update);
                sqlite3_reset(update);

                title.pop_back();
                cout << "Description of book with title " << title << " successfully updated." << endl;
            }
            sqlite3_finalize(update);
        }
    }

    catch (...) {
        cout << "Error updating book in database." << endl;
    }

    sqlite3_close(bookDB);
}

// updates the genre of a book already in inventory
void BookstoreInventory::updateGenre(string title, string genre) {
    string tempDBName = "../books.db";
    const char *dbName = tempDBName.c_str();

    Book bookUpdate;

    sqlite3 *bookDB;
    string updateQuery = "UPDATE books SET genre = ? WHERE title like ?";

    title.push_back('%'); // appending % searches for any values starting with title (case-insensitive)

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {

            sqlite3_stmt *update;
            if (sqlite3_prepare_v2(bookDB, updateQuery.c_str(), updateQuery.length(), &update, nullptr) == SQLITE_OK) {

                // binds values to ? in prepared insert query statement
                // text (statementName, paramNum, value (converted to c_str), length of value, pointer)
                // int (statementName, paramNum, intVal)
                sqlite3_bind_text(update, 1, genre.c_str(), genre.length(), NULL);
                sqlite3_bind_text(update, 2, title.c_str(), title.length(), NULL);

                sqlite3_step(update);
                sqlite3_reset(update);

                title.pop_back();
                cout << "Genre of book with title " << title << " successfully updated." << endl;
            }
            sqlite3_finalize(update);
        }
    }

    catch (...) {
        cout << "Error updating book in database." << endl;
    }

    sqlite3_close(bookDB);
}

boost::optional<Book> BookstoreInventory::searchForBookByISBN(string isbn) {
    const char *dbName = "../books.db";
    Book book;

    sqlite3 *bookDB;
    string findQuery = "SELECT * FROM books where isbn = ?";

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {
            sqlite3_stmt *find = NULL;
            if (sqlite3_prepare_v2(bookDB, findQuery.c_str(), findQuery.length(), &find, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(find, 1, isbn.c_str(), isbn.length(), NULL);
                sqlite3_exec(bookDB, sqlite3_expanded_sql(find), this->searchBookCallback, &book, nullptr);
                sqlite3_reset(find);
                sqlite3_finalize(find);
                sqlite3_close(bookDB);

                if (book.title == "none") {
                    return boost::none;
                }
                return book;
            }
        }
    } catch (...) {
        cout << "Error finding book in database." << endl;
    }
    return boost::none;
}

int BookstoreInventory::searchBookCallback(void *data, int argc, char **argv, char **azColName) {
    // https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
    // data: is 4th argument passed in sqlite3_exec command
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    // only goes in here if statement finds book
    Book *book = static_cast<Book *>(data); // cast data to book object
    book->ISBN = argv[0];
    book->title = argv[1];
    book->author = argv[2];
    book->year = stoi(argv[3]);
    book->publisher = argv[4];
    book->description = argv[5];
    book->genre = argv[6];
    book->msrp = stof(argv[7]);
    book->quantity = stoi(argv[8]);
    book->dateAdded = argv[9];
    return argc;
}
