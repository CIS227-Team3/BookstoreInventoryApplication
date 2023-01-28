/*
 * readFile.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#ifndef READFILE_H_
#define READFILE_H_

// #include "includes/rapidcsv.h"
// #include "includes/json.hpp"
#include "rapidcsv.h"
#include "json.h"
#include "book.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifndef READFILE_H_
#define READFILE_H_

void readFile(string filename);
void printBooks(); // temporary function for testing

#endif /* READFILE_H_ */
