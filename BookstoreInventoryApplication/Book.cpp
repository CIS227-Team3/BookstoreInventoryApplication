/*
 * Book.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "Book.h"

float Book::generatePrice() {
    float price;

    srand(time(NULL)); // may need to include chrono to make this work

    // generates random integer between 3499 and 10397
    // reference https://cplusplus.com/forum/beginner/183358/
    // rand() % maxNum + minNum
    int randomPrice = rand() % 10397 + 3499;

    // divides random number by 100 to get it to two decimal places
    price = randomPrice / 100;

    return price;
}

string Book::getTimestamp() {
	string dateAdded;

	// reference: https://thispointer.com/get-current-date-time-in-c-example-using-boost-date-time-library/
	boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();

	boost::gregorian::date currentDate = timeLocal.date(); // sets the date to the random numbers generated for year, month, and day	boost::posix_time::time_duration time = timeLocal.time_of_day(); // sets the time to the random numbers generated for hour, minute, and second
	int hour = timeLocal.time_of_day().hours();
	int minute = timeLocal.time_of_day().minutes();
	int second = timeLocal.time_of_day().seconds();

	boost::posix_time::time_duration currentTime(hour, minute, second);
	boost::posix_time::ptime currentTimestamp(currentDate, currentTime);

	dateAdded = to_iso_extended_string(currentTimestamp);

	return dateAdded;
}

Book::Book() {
    ISBN = "none";
    title = "none";
    author = "none";
    publisher = "none";
    year = 2000;
    msrp = generatePrice();
    quantity = 1;
    dateAdded = getTimestamp();
}

Book::Book(const string &isbn, const string &title, const string &author, int year,
           const string &publisher, const float &msrp, const int &quantity) :
        ISBN(isbn), title(title), author(author), year(year),
        publisher(publisher), msrp(msrp), quantity(quantity), dateAdded(getTimestamp()) {}

Book::Book(const string &isbn, const string &title, const string &author, int year, const string &publisher,
           const string &description, const string &genre, const float &msrp, const int &quantity) :
        ISBN(isbn), title(title), author(author), year(year), publisher(publisher), description(description),
        genre(genre), msrp(msrp), quantity(quantity), dateAdded(getTimestamp()) {}

Book::Book(const string &isbn, const string &title, const string &author, int year, const string &publisher,
           const string &description, const string &genre, const float &msrp, const int &quantity, const string &dateAdded) :
        ISBN(isbn), title(title), author(author), year(year), publisher(publisher), description(description),
        genre(genre), msrp(msrp), quantity(quantity), dateAdded(dateAdded) {}

Book::Book(boost::optional<Book> anOptional) {
    if (anOptional) {
        this->ISBN = anOptional->ISBN;
        this->title = anOptional->title;
        this->author = anOptional->author;
        this->year = anOptional->year;
        this->publisher = anOptional->publisher;
        this->description = anOptional->description;
        this->genre = anOptional->genre;
        this->msrp = anOptional->msrp;
        this->quantity = anOptional->quantity;
        this->dateAdded = anOptional->getTimestamp();
    }
}
