#ifndef BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
#define BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
// #include "boost/optional.hpp"
#include "Book.h"
#include "fileOperations.h"

using namespace std;

//Class of bookstoreInventory
class BookstoreInventory {

public:
    BookstoreInventory();

    deque<Book> searchForBook(string title);

    boost::optional<Book> searchForBookByISBN(string isbn);

    void addBook(Book book);

    void deleteBook(string title);

    void updateDescription(string title, string description);

    void updateGenre(string title, string genre);

    void displayLatestFive(); // gets five latest additions to database in timestamp order

private:
    static int searchBookCallback(void *data, int argc, char **argv, char **azColName);
    QSqlDatabase booksDB;
};


#endif //BOOKSTOREINVENTORYAPPLICATION_BOOKSTOREINVENTORY_H
