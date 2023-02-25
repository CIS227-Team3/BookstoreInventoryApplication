/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "fileOperations.h"

void writeBooksFile(deque<Book> &Inventory) {
    string filename = "../printBooks.csv";
    ofstream out(filename, std::ios::out);
    cout << "File can be found as: " << filename << endl;
    out << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Genre,Description,MSRP,Quantity" << endl;

    for (auto &book: Inventory) {
        out << book.ISBN << ",";
        out << book.title << ",";
        out << book.author << ",";
        out << book.year << ",";
        out << book.publisher << ",";
        out << book.genre << ",";
        out << book.description << ",";
        out << book.msrp << ",";
        out << book.quantity << "," << endl;
    }

    out.close();
    cout << "Done writing file." << endl;
}

void readBookFile(BookstoreInventory &inventoryObject, string filePath) {
    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0));

    for (int i = 0; i < doc.GetRowCount(); ++i) {
        try {
            string ISBN = doc.GetRowName(i);
            string title = doc.GetCell<string>("Book-Title", ISBN);
            string author = doc.GetCell<string>("Book-Author", ISBN);
            int year = doc.GetCell<int>("Year-Of-Publication", ISBN);
            string publisher = doc.GetCell<string>("Publisher", ISBN);
            string description = doc.GetCell<string>("Description", ISBN);
            string genre = doc.GetCell<string>("Genre", ISBN);
            float msrp = doc.GetCell<float>("MSRP", ISBN);
            int quantity = doc.GetCell<int>("Quantity", ISBN);

            Book book(ISBN, title, author, year, publisher, description, genre, msrp, quantity);

            inventoryObject.addBook(book);
        } catch (...) {

        }
    }
}

void exportInventoryToCsv(BookstoreInventory &inventoryObject) {
    deque<Book> allBooks = inventoryObject.getAllBooks();
    writeBooksFile(allBooks);
}