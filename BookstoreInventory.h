#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "User.h"
#include "Book.h"
#include "fileOperations.h"

using namespace std;

//Class of bookstoreInventory
class BookstoreInventory {

public:
    BookstoreInventory();

    void listInventory();

    boost::optional<Book> searchForBook(string title);

    boost::optional<Book> searchForBookByISBN(string isbn);

    void exportInventoryToCsv();

    void addBook(Book book);

    void deleteBook(string title);

    void updateDescription(string title, string description);

    void updateGenre(string title, string genre);

    void readBookFile(BookstoreInventory &inventoryObject, string filePath);

    deque<Book> getAllBooks();

private:
    static int searchBookCallback(void *data, int argc, char **argv, char **azColName);

    static int allBooksCallback(void *data, int argc, char **argv, char **azColName);
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
