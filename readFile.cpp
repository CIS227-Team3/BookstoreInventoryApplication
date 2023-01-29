/*
 * readFile.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: Group 3
 */

#include "readFile.h"

void readFile(string filePath){
    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0));

    cout  << doc.GetColumnName(-1) << " | " << doc.GetColumnName(0) << " | " << doc.GetColumnName(1) << " | " << doc.GetColumnName(2) <<  " | " << doc.GetColumnName(3) << endl;

    for (int i = 0; i < doc.GetRowCount(); ++i) {
        string ISBN = doc.GetRowName(i);
        string title = doc.GetCell<string>("Book-Title", ISBN);
        string author = doc.GetCell<string>("Book-Author", ISBN);
        int year =doc.GetCell<int>("Year-Of-Publication", ISBN);
        string publisher = doc.GetCell<string>("Publisher", ISBN);

        cout << ISBN << " | " << title << " | " << author << " | " << year <<  " | " << publisher << endl;
    }
}

