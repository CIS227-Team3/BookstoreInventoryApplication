#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <vector>
#include "Book.h"
#include "readFile.h"

using namespace std;

class BookstoreInventory {

public:
    BookstoreInventory();
    void listInventory();

private:
    vector<Book> Inventory;
    void addInitialInventory();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
