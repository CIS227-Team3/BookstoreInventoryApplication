/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "readFile.h"

vector<Book> allBookInfo; // contains all books
vector<string> book; // contains attributes of single book
string fileLine;
string data;

void readFile(string filename) {

	// opens the file with the specified name
	ifstream readBooks(filename);

	// gets the first line of the books file with titles
	getline(readBooks, fileLine);

	// opens file and reads the file line by line
	if (readBooks.is_open()) {
		while (getline(readBooks, fileLine)) {
			book.clear();
			stringstream ss(fileLine);

			while ((getline(ss, data, ','))) {
				book.push_back(data);
			}

			string bookISBN = book.at(0);
			string bookTitle = book.at(1);
			string bookAuthor = book.at(2);
			// stoi converts string to integer value
			// reference: https://www.geeksforgeeks.org/csv-file-management-using-c/
			int bookYear = stoi(book.at(3));
			string bookPublish = book.at(4);

			// creates an instance of a book
			Book bookEntry(bookISBN, bookTitle, bookAuthor, bookYear, bookPublish);

			// adds book entry to vector that contains all books
			allBookInfo.push_back(bookEntry);

		}
		// closes file
		readBooks.close();
	}
}

void printBooks() { 
	for (unsigned short int i = 0; i < allBookInfo.size(); ++i) {
		Book book;
		book = allBookInfo.at(i);
		book.bookToString();
	}
}

