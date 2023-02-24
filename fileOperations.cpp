/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "fileOperations.h"

//Reads from a file of books
void readBooksDatabase(string filePath, deque<Book> &Inventory) {
    string selectQuery = "SELECT * FROM books"; // table data is stored in books table in books.db
    string rowCountQuery = "SELECT COUNT(*) FROM books as rowCount";
    int numRows = 0;

    // converts string to cstring so filename can be used as parameter in sqlite_open function
    // reference: https://www.geeksforgeeks.org/convert-string-char-array-cpp/
    const char *filename = filePath.c_str();

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
            string ISBN = (const char *) sqlite3_column_text(query, 0); // column 0 contains ISBN
            string title = (const char *) sqlite3_column_text(query, 1); // column 1 contains title
            string author = (const char *) sqlite3_column_text(query, 2); // column 2 contains author
            int year = sqlite3_column_int(query, 3); // column 3 contains year
            string publisher = (const char *) sqlite3_column_text(query, 4); // column 4 contains publisher
            string description = (const char *) sqlite3_column_text(query, 5); // column 5 contains description
            string genre = (const char *) sqlite3_column_text(query, 6); // column 6 contains genre
            float msrp = sqlite3_column_double(query, 7); // column 7 contains msrp
            int quantity = sqlite3_column_int(query, 8); // column 8 contains quantity

            // creates a book object and adds it to inventory
            Book book(ISBN, title, author, year, publisher, description, genre, msrp, quantity);
            Inventory.push_back(book);
        }

        // statement object destructor
        sqlite3_finalize(query);

    }

    catch (...) {
        cout << "Error opening or accessing database." << endl;
    }

    // closes database connection
    sqlite3_close(bookDB);
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

