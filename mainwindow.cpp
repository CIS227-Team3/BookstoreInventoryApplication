#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchForBook() {
    string title;
    deque<Book> results;
    title = ui->lnBookSearch->text().toStdString();

    BookstoreInventory bookstoreInventory;
    results = bookstoreInventory.searchForBook(title);
    // reference https://wiki.qt.io/How_to_Use_QTableWidget
    ui->tblBooks->clearContents();
    for (unsigned int i = 0; i < results.size(); ++i) {
        ui->tblBooks->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(results.at(i).ISBN)));
        ui->tblBooks->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(results.at(i).title)));
        ui->tblBooks->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(results.at(i).author)));
        ui->tblBooks->setItem(i, 3, new QTableWidgetItem(QString::number(results.at(i).year)));
        ui->tblBooks->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(results.at(i).publisher)));
        ui->tblBooks->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(results.at(i).description)));
        ui->tblBooks->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(results.at(i).genre)));
        ui->tblBooks->setItem(i, 7, new QTableWidgetItem(QString::number(results.at(i).msrp)));
        ui->tblBooks->setItem(i, 8, new QTableWidgetItem(QString::number(results.at(i).quantity)));
        ui->tblBooks->setItem(i, 9, new QTableWidgetItem(QString::fromStdString(results.at(i).dateAdded)));
    }
    ui->tblBooks->resizeColumnsToContents();
}
