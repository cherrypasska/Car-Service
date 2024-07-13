#include "clientswindow.h"
#include "ui_clientswindow.h"
#include <QDir>
#include "Client.h"
#include <iterator>
clientswindow::clientswindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clientswindow)
{
    ui->setupUi(this);
    buys = new QList<oneBuy>();
    clients = new QHash<QString, Client>();
    zapbuys();
    zap();
}

clientswindow::~clientswindow()
{
    delete ui;
}

void clientswindow::zap()
{
    QString folderPath = "C:/Qt/untitled/clients";
    QDir directory(folderPath);
    if (!directory.exists() || directory.isEmpty()) {
        qDebug() << "unable to access the database or the directory is empty";
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
        QStringList data = in.readAll().split('\n');
        QString mashini;
        QString nameCl;
        QString passCl;
        for(auto i:filename){
            if(i == '.') break;
            else{
                passCl+=i;
            }
        }
        for(int i = 0; i < buys->size(); i++){
            if(buys->at(i).passport == passCl){
                nameCl = buys->at(i).clientName;
                qDebug() << nameCl;
            }
        }
        for(int i = 0; i < buys->size(); i++){
            if(buys->at(i).passport == passCl){
                mashini+=buys->at(i).num +',';
            }
        }
        mashini = mashini.left(mashini.size() - 1);
        Client client(mashini, nameCl, passCl);
        clients->insert(client.clientPas,client);
        file.close();
    }
}

void clientswindow::zapbuys()
{
        QString folderPath = "C:/Qt/untitled/Sales";
        QDir directory(folderPath);
        if (!directory.exists() || directory.isEmpty()) {
            qDebug() << "unable to access the database or the directory is empty";
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
            QStringList data = in.readAll().split('\n');
            if (data.size() >= 6) {
                QDate date = QDate::fromString(data[5], "yyyy.MM.dd");
                oneBuy buy(data[0], data[1], data[2], data[3], data[4].toInt(), date, data[6]);
                buys->append(buy);
            }
            file.close();
        }
}

void clientswindow::on_pushButton_2_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Паспорт" << "Номера машин");
    Client p = clients->take(ui->lineEdit_2->text());
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(p.ClientName));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(p.clientPas));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(p.cars));
}


void clientswindow::on_pushButton_5_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 100);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 200);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Паспорт" << "Номера машин");
    print(ui->tableWidget);
}

void clientswindow::print(QTableWidget *table)
{
    table->clear();
    ui->tableWidget->setRowCount(0);
    int row = 0;
    for (const auto &c : clients->values()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(c.clientPas));
        table->setItem(row, 1, new QTableWidgetItem(c.ClientName));
        table->setItem(row, 2, new QTableWidgetItem(c.cars));
        row++;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Паспорт" << "ФИО" << "Номера машин");
}


void clientswindow::on_pushButton_clicked()
{
    ui->tableWidget->clear();
}


void clientswindow::on_pushButton_3_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    int row = 0;
    for(auto &p:clients->values()){
        if(p.ClientName == ui->lineEdit->text()){
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(p.clientPas));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(p.ClientName));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(p.cars));
            row++;
        }
    }
}

