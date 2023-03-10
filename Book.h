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
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/date_time/posix_time/posix_time_io.hpp"

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
    string dateAdded;

    // custom compare based on price
    struct priceCompare {
        bool operator()(const Book &book1, const Book &book2) const {
            float right = book1.msrp;
            float left = book2.msrp;
            return (left > right);
        }
    };

private:
    float generatePrice();
    string getTimestamp();
};

#endif /* BOOK_H_ */
