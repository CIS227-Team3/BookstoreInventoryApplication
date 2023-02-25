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
#include "BookstoreInventory.h"
#include "User.h"

using namespace std;

void exportInventoryToCsv(BookstoreInventory &inventoryObject);

void writeBooksFile(deque<Book> &UserList);

void readBookFile(BookstoreInventory &inventoryObject, string filePath);

#endif /* READFILE_H_ */
