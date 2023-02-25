#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "User.h"
#include "Book.h"
#include "fileOperations.h"

using namespace std;

//Class of bookstoreInventory
class BookstoreInventory {

public:
    BookstoreInventory();

    void listInventory();

    Book searchForBook(string title);

    multiset<Book> searchForBookByISBN(vector<string> isbns);

    void exportInventoryToCsv();

    void addBook(Book book);

    void deleteBook(string title);

    void updateDescription(string title, string description);

    void updateGenre(string title, string genre);

    void readBookFile(BookstoreInventory &inventoryObject, string filePath);

    deque<Book> Inventory;

private:

    void addInitialInventory();
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
