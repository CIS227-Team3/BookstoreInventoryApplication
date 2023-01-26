/*
 * Book.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "Book.h"

Book::Book() {
	title = "none";
	author = "none";
	publisher = "none";
	year = 2000;

}

Book::Book(string title, string author, string publisher, int year) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->year = year;
}

