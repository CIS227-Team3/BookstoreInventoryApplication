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

    readBooksFile(filePath, this->Inventory);
}
