/*
 * menuOptions.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Group 3
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "BookstoreInventory.h"
#include "UserDatabase.h"

using namespace std;

short int promptUserInput();

short int menuOptions();

void printAndClearError();

short validateMenuOption();

unsigned short int validateYear();

float validatePrice();

unsigned int validateQuantity();

void inventoryManagementOptions(BookstoreInventory &inventory);

void adminMenu(UserDatabase &users);
