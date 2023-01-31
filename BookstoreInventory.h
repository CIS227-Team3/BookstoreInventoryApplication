#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "readFile.h"

using namespace std;

//Class of bookstoreInventory
class BookstoreInventory {

public:
    BookstoreInventory();
    void listInventory();
    optional<Book> searchForBook(string title);

private:
    vector<Book> Inventory;
    void addInitialInventory();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
