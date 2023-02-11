/*
 * Book.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "Book.h"

Book::Book() {
    ISBN = "none";
    title = "none";
    author = "none";
    publisher = "none";
    year = 2000;
}

Book::Book(const string &isbn, const string &title, const string &author, int year, const string &publisher) :
        ISBN(isbn), title(title), author(author), year(year), publisher(publisher) {}

Book::Book(const string &isbn, const string &title, const string &author, int year, const string &publisher,
           const string &description, const string &genre) :
        ISBN(isbn), title(title), author(author), year(year), publisher(publisher), description(description),
        genre(genre) {}
