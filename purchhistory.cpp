#include "purchhistory.h"
#include "ui_purchhistory.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QFileInfo>
#include "buy.h"
#include "oneBuy.h"

purchhistory::purchhistory(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::purchhistory)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ФИО клиента" << "ФИО продавца" << "Название машины" << "Цена"  << "Номер");
    ui->tableWidget->setColumnWidth(0, 140);
    ui->tableWidget->setColumnWidth(1, 140);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(5, 90);

    list = new QList<oneBuy>();

    zap();
    print(ui->tableWidget);
}

purchhistory::~purchhistory()
{
    delete ui;
    delete list;
}

void purchhistory::zap()
{
    QString folderPath = "C:/Qt/untitled/Sales";
    QDir directory(folderPath);
    if (!directory.exists()) {
        qDebug() << "unable to access the database";
        return;
    }
    if (directory.isEmpty()) {
        flag = false;
        return;
    }

    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);
    foreach (const QString &filename, files) {
        QString filePath = folderPath + QDir::separator() + filename;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "can't open the file" << filename;
            continue;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList data = in.readAll().split('\n');
            if (data.size() < 6) {
                qDebug() << "Invalid data in file" << filename;
                continue;
            }
            QDate da = QDate::fromString(data[5], "dd/MM/yyyy");
            oneBuy buy(data[0], data[1], data[2], data[3], data[4].toInt(), da, data[6]);
            list->append(buy);
        }
        file.close();
    }
}

void purchhistory::print(QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);  // Clear previous content
    for (int i = 0; i < list->size(); ++i) {
        const oneBuy &buy = list->at(i);
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(buy.clientName));
        tableWidget->setItem(i, 1, new QTableWidgetItem(buy.prodName));
        tableWidget->setItem(i, 2, new QTableWidgetItem(buy.carName));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(buy.price)));
        tableWidget->setItem(i, 4, new QTableWidgetItem(buy.num));
    }
}

void purchhistory::on_historycheck_clicked()
{
    list->clear();
    zap();
    if (!list->isEmpty()) {
        print(ui->tableWidget);
    }
}

void purchhistory::on_deletehistrory_clicked()
{
    QString folderPath = "C:/Qt/untitled/Sales";
    QDir directory(folderPath);
    if (!directory.exists()) {
        qDebug() << "unable to access the database";
        return;
    }
    if (directory.isEmpty()) {
        flag = false;
        return;
    }
    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);
    foreach (const QString &filename, files) {
        QString filePath = folderPath + QDir::separator() + filename;
        QFile file(filePath);
        if (!file.remove()) {
            qDebug() << "Failed to remove file" << filename;
        }
    }
}
