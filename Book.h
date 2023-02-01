/*
 * Book.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include <string>

using namespace std;

#ifndef BOOK_H_
#define BOOK_H_

//Book class, creates variables related to the Book object
class Book {
public:
    Book();

    Book(const string &isbn, const string &title, const string &author, int year, const string &publisher);

    string ISBN;
    string title;
    string author;
    int year;
    string publisher;
};

#endif /* BOOK_H_ */
