#include "BookstoreInventory.h"

//Constructor
BookstoreInventory::BookstoreInventory() {
    addInitialInventory();
}

//Lists inventory in terminal
void BookstoreInventory::listInventory() {
    cout << "ISBN | Book-Title | Book-Author | Year Published | Publisher | Description | Genre " << endl;
    for (auto &book: this->Inventory) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year << " | "
             << book.publisher << " | " << book.description << " | " << book.genre << endl;
    }
}

//Adds initial inventory of file path
void BookstoreInventory::addInitialInventory() {
    string filePath = "books.db";
    readBooksFile(filePath, Inventory);
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
Book BookstoreInventory::searchForBook(string title) {
    bool bookFound = false;
    cout << "Searching database for book with title " << title << endl;

	for (auto &book: this->Inventory) { // searches inventory for exact match in title
		if (caseInsensitiveMatch(book.title, title)) { // if a match is found, information is output
			cout << "Book details: " << endl;
			cout << "ISBN: " << book.ISBN << endl;
			cout << "Title: " << book.title << endl;
			cout << "Author: " << book.author << endl;
			cout << "Year Published: " << book.year << endl;
			cout << "Publisher: " << book.publisher << endl;
			cout << "Description: " << book.description << endl;
			cout << "Genre: " << book.genre << endl;
			bookFound = true;
			return book;
		}
	}

    if (!bookFound) {
		cout << "Book with title " << title << " not found." << endl;
	}
}

// Adds a new book to the database
void BookstoreInventory::addBook(Book book) {
    string tempDBName = "books.db";
    const char* dbName = tempDBName.c_str();

    sqlite3 *bookDB;
    string insertQuery = "INSERT INTO books(isbn, title, author, year, publisher, description, genre) VALUES(?, ?, ?, ?, ?, ?, ?)";

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

                sqlite3_step(insert);
                sqlite3_reset(insert);

                Inventory.push_back(book);
            }
            sqlite3_finalize(insert);
        }

    }

    catch(...) {
        cout << "Error adding book to database." << endl;
    }

    sqlite3_close(bookDB);

    cout << "Book successfully added to database." << endl;
}

// deletes a book from the database
void BookstoreInventory::deleteBook(string title) {
    string tempDBName = "books.db";
    const char* dbName = tempDBName.c_str();

    sqlite3 *bookDB;
    string deleteQuery = "DELETE FROM books WHERE title = ?";

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

                deque<Book>::iterator bookToDel = Inventory.begin();
                for (auto bookToDel = Inventory.begin(); bookToDel != Inventory.end(); ++bookToDel) {
                	Book delBook = *bookToDel;
					if (caseInsensitiveMatch(title, delBook.title)) {
						Inventory.erase(bookToDel);
						cout << "Book with title " << title << " has been successfully deleted from database." << endl;
						break;
					}
				}
            }
            sqlite3_finalize(del);
        }
    }

    catch(...) {
        cout << "Error deleting book from database." << endl;
    }

    sqlite3_close(bookDB);

}

// updates the description of a book already in inventory
void BookstoreInventory::updateDescription(string title, string description) {
    string tempDBName = "books.db";
    const char* dbName = tempDBName.c_str();

    Book bookUpdate;

    sqlite3 *bookDB;
    string updateQuery = "UPDATE books SET description = ? WHERE title = ?";

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
            }
            sqlite3_finalize(update);
        }

        for (unsigned int i = 0; i < Inventory.size(); ++i) {
        	if (caseInsensitiveMatch(title, Inventory.at(i).title)) {
        		Inventory.at(i).description = description;
        		cout << "Description of book with title " << title << " successfully updated in database." << endl;
        	}
        }
    }

    catch(...) {
        cout << "Error updating book in database." << endl;
    }

    sqlite3_close(bookDB);
}

// updates the genre of a book already in inventory
void BookstoreInventory::updateGenre(string title, string genre) {
    string tempDBName = "books.db";
    const char* dbName = tempDBName.c_str();

    Book bookUpdate;

    sqlite3 *bookDB;
    string updateQuery = "UPDATE books SET genre = ? WHERE title = ?";

    try {
        if (sqlite3_open(dbName, &bookDB) == SQLITE_OK) {

            sqlite3_stmt *update = NULL;
            if (sqlite3_prepare_v2(bookDB, updateQuery.c_str(), updateQuery.length(), &update, nullptr) == SQLITE_OK) {

                // binds values to ? in prepared insert query statement
                // text (statementName, paramNum, value (converted to c_str), length of value, pointer)
                // int (statementName, paramNum, intVal)
                sqlite3_bind_text(update, 1, genre.c_str(), genre.length(), NULL);
                sqlite3_bind_text(update, 2, title.c_str(), title.length(), NULL);

                sqlite3_step(update);
                sqlite3_reset(update);
            }
            sqlite3_finalize(update);
        }

        // gets book object with matching title
        for (unsigned int i = 0; i < Inventory.size(); ++i) {
			if (caseInsensitiveMatch(title, Inventory.at(i).title)) {
				Inventory.at(i).genre = genre;
				cout << "Genre of book with title " << title << " successfully updated in database." << endl;
			}
		}
    }

    catch(...) {
        cout << "Error updating book in database." << endl;
    }

    sqlite3_close(bookDB);


}

void BookstoreInventory::exportInventoryToCsv() {
    writeBooksFile(this->Inventory);
}
