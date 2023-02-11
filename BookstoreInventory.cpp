#include "BookstoreInventory.h"

//Constructor
BookstoreInventory::BookstoreInventory() {
    addInitialInventory();
}

//Lists inventory in terminal
void BookstoreInventory::listInventory() {
    cout << "ISBN | Book-Title | Book-Author | Year Published | Publisher " << endl;
    for (auto &book: this->Inventory) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year << " | "
             << book.publisher << endl;
    }
}

//Adds initial inventory of file path
void BookstoreInventory::addInitialInventory() {
    string filePath = "../miniBooks.csv";
    readBooksFile(filePath, Inventory);
}

//Watches for Cases, so we can use lower or upper case characters
bool caseInsensitiveMatch(string string1, string string2) {
    //convert string1 and string2 into lower case strings
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
    if (string1.compare(string2) == 0) {
        return true;
    }
    return false;
}

//Searches for a specific book within BookstoreInventory
void BookstoreInventory::searchForBook(string title) {
    bool bookFound = false;

    for (auto &book: this->Inventory) {
        if (caseInsensitiveMatch(book.title, title)) {
            cout << "Book details: " << endl;
            cout << "ISBN: " << book.ISBN << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Year Published: " << book.year << endl;
            cout << "Publisher: " << book.publisher << endl;
            bookFound = true;
            break;
        }
    }

    if (!bookFound) {
        cout << "Book with title " << title << " not found." << endl;
    }
}
