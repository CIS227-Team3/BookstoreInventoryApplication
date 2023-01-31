#include "BookstoreInventory.h"

//Constructor
BookstoreInventory::BookstoreInventory() {
    addInitialInventory();
}

//Lists inventory in terminal
void BookstoreInventory::listInventory() {
    cout  << "ISBN | Book-Title | Book-Author | Year Published | Publisher " << endl;
    for (auto & book : this->Inventory) {
        cout << book.ISBN << " | " << book.title << " | " << book.author << " | " << book.year <<  " | " << book.publisher << endl;
    }
}


//Adds initial inventory of file path
void BookstoreInventory::addInitialInventory() {
    string filePath;

    cout << "Enter file path: ";

    cin >> filePath;

    readBooksFile(filePath,Inventory);
}

//Watches for Cases so we can use lower or upper case charecters
bool caseInsensitiveMatch(string string1, string string2) {
    //convert string1 and string2 into lower case strings
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
    if(string1.compare(string2) == 0) {
        return true;
    }
    return false;
}


//Searches for a specific book within BookstoreInventory
optional<Book> BookstoreInventory::searchForBook(string title) {
    for (auto & book : this->Inventory) {
        if(caseInsensitiveMatch(book.title, title)){
            return book;
        }
    }
    return nullopt;
}
