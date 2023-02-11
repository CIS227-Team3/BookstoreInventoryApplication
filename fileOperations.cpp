/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "fileOperations.h"

//Reads from a file of books
void readBooksFile(string filePath, vector<Book> &Inventory) {
    unsigned int added = 0;
    unsigned int failed = 0;

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0));

    for (int i = 0; i < doc.GetRowCount(); ++i) {
        try {
            string ISBN = doc.GetRowName(i);
            string title = doc.GetCell<string>("Book-Title", ISBN);
            string author = doc.GetCell<string>("Book-Author", ISBN);
            int year = doc.GetCell<int>("Year-Of-Publication", ISBN);
            string publisher = doc.GetCell<string>("Publisher", ISBN);

            Inventory.push_back(Book(ISBN, title, author, year, publisher));
            added++;
        }
        catch (...) {
            cout << "Problem reading book in CSV with ISBN: " << doc.GetRowName(i) << ", did not add to inventory."
                 << endl;
            failed++;
        }
    }
    cout << "Added " << added << " books to inventory. Failed adding: " << failed << endl;

    writeBooksFile(Inventory);
}

//Reads from a file of users
void readUsersFile(vector<User> &Users) {
    rapidcsv::Document doc("../users.csv", rapidcsv::LabelParams(0, 0));

    for (unsigned int i = 0; i < doc.GetRowCount(); ++i) {
        try {
            string username = doc.GetRowName(i);
            string password = doc.GetCell<string>("Password", username);

            Users.push_back(User(username, password));
        }
        catch (...) {
            cout << "Problem reading user in CSV" << endl;
        }
    }
}

void writeBooksFile(vector<Book> &Inventory) {
    std::string filename = "../printBooks.csv";
    std::ofstream  out(filename, std::ios::out);
    out << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher" << endl;

    for (auto & book : Inventory) {
        out << book.ISBN << ",";
        out << book.title << ",";
        out << book.author << ",";
        out << book.year << ",";
        out << book.publisher << "," << endl;
    }

    out .close();
}

