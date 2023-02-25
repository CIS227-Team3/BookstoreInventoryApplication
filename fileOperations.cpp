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

