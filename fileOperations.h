/*
 * readFile.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#ifndef READFILE_H_
#define READFILE_H_

#include "includes/rapidcsv.h"
#include "includes/json.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include "includes/sqlite3.h"
#include "Book.h"
#include "User.h"
#include "BookstoreInventory.h"

using namespace std;

void readBooksFile(string filePath, deque<Book> &Inventory);

void writeBooksFile(deque<Book> &Inventory);

void readUsersFile(list<User> &Users);


#endif /* READFILE_H_ */
