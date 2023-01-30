#include "BookstoreInventory.h"

BookstoreInventory::BookstoreInventory() {
    addInitialInventory();
}

void BookstoreInventory::listInventory() {
    cout  << "ISBN | Book-Title | Book-Author | Year Published | Publisher " << endl;
    for (auto & book : this->Inventory) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year <<  " | " << book.publisher << endl;
    }
}

void BookstoreInventory::addInitialInventory() {
    string filePath;

    cout << "Enter file path: ";

    cin >> filePath;

    readBooksFile(filePath,Inventory);
}

bool caseInsensitiveMatch(string string1, string string2) {
    //convert string1 and string2 into lower case strings
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
    if(string1.compare(string2) == 0) {
        return true;
    }
    return false;
}

optional<Book> BookstoreInventory::searchForBook(string title) {
    for (auto & book : this->Inventory) {
        if(caseInsensitiveMatch(book.title, title)){
            return book;
        }
    }
    return nullopt;
}
