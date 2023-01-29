/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "readFile.h"

void readBooksFile(string filePath, vector<Book> &Inventory){
    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0));

    for (int i = 0; i < doc.GetRowCount(); ++i) {
        try {
            string ISBN = doc.GetRowName(i);
            string title = doc.GetCell<string>("Book-Title", ISBN);
            string author = doc.GetCell<string>("Book-Author", ISBN);
            int year =doc.GetCell<int>("Year-Of-Publication", ISBN);
            string publisher = doc.GetCell<string>("Publisher", ISBN);

            Inventory.push_back(Book(ISBN, title, author, year, publisher));
        }
        catch (...) {
            cout << "Problem reading book in CSV with ISBN: " << doc.GetRowName(i) << ", did not add to inventory." << endl;
        }
    }
}

