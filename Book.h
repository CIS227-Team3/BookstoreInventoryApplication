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

class Book {
public:
	Book();
	Book(string title, string author, string publisher, int year);

private:
	string title;
	string author;
	string publisher;
	int year;
};

#endif /* BOOK_H_ */
