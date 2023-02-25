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

#include <chrono>
#include <deque>
#include <boost/optional.hpp>
#include "includes/sqlite3.h"

//Book class, creates variables related to the Book object
class Book {
public:
    Book();

    Book(const string &isbn, const string &title, const string &author, int year, const string &publisher,
         const float &msrp, const int &quantity);

    Book(const string &isbn, const string &title, const string &author, int year, const string &publisher,
         const string &description, const string &genre, const float &msrp, const int &quantity);

    Book(boost::optional<Book> anOptional);

    string ISBN;
    string title;
    string author;
    int year;
    string publisher;
    string description;
    string genre;
    float msrp;
    unsigned int quantity;

    // custom compare for set based on price
    bool operator<(const Book &msgObj) const {
        float right = msgObj.msrp;
        float left = this->msrp;
        return (left < right);
    }

private:
    float generatePrice();
};

#endif /* BOOK_H_ */
