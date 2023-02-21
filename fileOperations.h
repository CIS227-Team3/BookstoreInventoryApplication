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
#include "includes/sqlite3.h"

#include <iostream>
#include <fstream>
#include <list>
#include "Book.h"
#include "User.h"

using namespace std;

void readBooksDatabase(string filePath, deque<Book> &Inventory);

void writeBooksFile(deque<Book> &UserList);

void readUsersDatabase(list<User> &Users);

#endif /* READFILE_H_ */
