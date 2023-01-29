#include "BookstoreInventory.h"

BookstoreInventory::BookstoreInventory() {
    addInitialInventory();
}

void BookstoreInventory::listInventory() {
    cout  << "ISBN | Book-Title | Book-Author | Year Published | Publisher " << endl;
    for (auto & i : Inventory) {
        cout << i.ISBN << " | " << i.title << " | " << i.author << " | " << i.year <<  " | " << i.publisher << endl;
    }
}

void BookstoreInventory::addInitialInventory() {
    string filePath;

    cout << "Enter file path: ";

    cin >> filePath;

    readBooksFile(filePath, Inventory);
}
