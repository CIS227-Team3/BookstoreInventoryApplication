#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Book.h"
#include "fileOperations.h"

using namespace std;

//Class of bookstoreInventory
class BookstoreInventory {

public:
    BookstoreInventory();

    void listInventory();

    Book searchForBook(string title);

private:
    deque<Book> Inventory;

    void addInitialInventory();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
