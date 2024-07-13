#include "buy.h"
#include "ui_buy.h"
#include "ui_cars.h"
#include <QFile>
#include <QDate>
#include <QDateEdit>
#include <QDir>
#include <QDebug>
#include "oneBuy.h"
#include "car.h"
#include "calcfacade.h"

buy::buy(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::buy)
    , finalPrice(0)
    , skidka(0)
    , wheels(0)
{
    ui->setupUi(this);
    buys = new QList<oneBuy>();
    zap();
}

buy::~buy()
{
    delete ui;
    delete buys;
}

void buy::on_checkBox_clicked(bool checked)
{
    if (checked) {
        skidka += 5;
    } else {
        skidka -= 5;
    }
    ui->label_4->setText(QString::number(skidka));
}

void buy::on_checkBox_2_clicked(bool checked)
{
    if (checked) {
        wheels+=30000;
    }
    else{
        wheels-=30000;
    }
}

void buy::on_clientName_textChanged(const QString &arg1)
{
    clientName = arg1;
    check();
}

void buy::on_pass_textChanged(const QString &arg1)
{
    pass = arg1;
    check();
}

void buy::on_sellerName_textChanged(const QString &arg1)
{
    prodName = arg1;
    check();
}

void buy::on_carNum_textChanged(const QString &arg1)
{
    carNum = arg1;
    check();
}

void buy::check()
{
    if(ui->clientName->text().isEmpty() || ui->pass->text().isEmpty() || ui->sellerName->text().isEmpty() || ui->carNum->text().isEmpty()){
        ui->pushButton_2->setEnabled(false);
    }
    else ui->pushButton_2->setEnabled(true);
    if(ui->carNum->text().isEmpty()){
        ui->pushButton->setEnabled(false);
    }
    else ui->pushButton->setEnabled(true);
}

void buy::on_pushButton_clicked()
{
    QString str = ui->carNum->text();
    QFile file("C:/Qt/untitled/cars/" + str + ".txt");
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList data = in.readAll().split('\n');
            bool fl = data[2] == "битая";
            Car::CarClass clas;
            if(data[6] == "A") clas = Car::MINICAR;
            else if(data[6] == "B") clas = Car::SMALLSITYCAR;
            else if(data[6] == "C") clas = Car::COMFORTCAR;
            else if(data[6] == "D") clas = Car::COMFORTPLUSCAR;
            else if(data[6] == "E") clas = Car::EXPENSIVE;
            else clas = Car::SCLASS;
            Car cl(data[0], data[1], fl, data[3].toInt(), data[4], data[5].toInt(), clas);
            cl.setPrice(calcfacade::getCost(&cl));
            finalPrice = cl.getPrice();
        }
        file.close();
        finalPrice -= (finalPrice / 100) * skidka;
        finalPrice += wheels;

        ui->lineEdit_5->setText(QString::number(finalPrice));
    } else {
        qDebug() << "Нет такой машины(";
    }
    check();
}

void buy::on_pushButton_2_clicked()
{
    QString str = ui->carNum->text();
    QFile file("C:/Qt/untitled/cars/" + str + ".txt");
    QFile fileop("C:/Qt/untitled/Sales/" + str + ".txt");
    if (file.exists() && file.open(QIODevice::ReadOnly) && !fileop.exists()) {
        QTextStream in(&file);
        QStringList data = in.readAll().split('\n');
        bool fl = data[2] == "битая";
        Car::CarClass clas;
        if(data[6] == "A") clas = Car::MINICAR;
        else if(data[6] == "B") clas = Car::SMALLSITYCAR;
        else if(data[6] == "C") clas = Car::COMFORTCAR;
        else if(data[6] == "D") clas = Car::COMFORTPLUSCAR;
        else if(data[6] == "E") clas = Car::EXPENSIVE;
        else clas = Car::SCLASS;
        Car cl(data[0], data[1], fl, data[3].toInt(), data[4], data[5].toInt(), clas);
        cl.setPrice(calcfacade::getCost(&cl));
        QString carname = cl.getname();
        int pric = cl.getPrice();
        file.close();

        QDate date = QDate::currentDate();
        oneBuy joint(ui->clientName->text(), ui->sellerName->text(), carname, ui->carNum->text(), pric, date, ui->pass->text());

        buys->push_back(joint);

        QFile salesFile("C:/Qt/untitled/Sales/" + ui->carNum->text() + ".txt");

        if (salesFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&salesFile);
            out << ui->clientName->text() << '\n'
                << ui->sellerName->text() << '\n'
                << carname << '\n'
                << ui->carNum->text() << '\n'
                << pric << '\n'
                << date.toString("yyyy.MM.dd") << '\n'
                << ui->pass->text();
            salesFile.close();
        }
        file.remove();
        QStringList daa;
        QFile ClientFile("C:/Qt/untitled/clients/" + ui->pass->text() + ".txt");
            if(ClientFile.open(QIODevice::ReadOnly)){
                QTextStream in(&ClientFile);
                daa = in.readAll().split('\n');
            }
            if(ClientFile.open(QIODevice::WriteOnly)){
                QTextStream out(&ClientFile);
                for(int i = 0; i < daa.size(); i++){
                    out << daa[i];
                    out << '\n';
                }
                out << '\n' + carNum;
            }
            if(ClientFile.open(QIODevice::WriteOnly)){
                QTextStream out(&ClientFile);
                for(int i = 0; i < daa.size(); i++){
                    out << ui->clientName->text();
                    out << '\n';
                    out << ui->pass->text();
                    out << '\n';
                }
                out << carNum;
            }
        ui->label_9->setText("Машина продана!");
    } else {
        qDebug() << "Нет такой машины или она уже продана(";
    }
    check();
}

void buy::zap()
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

void buy::on_pushButton_3_clicked()
{
    if(!buys->isEmpty()){
        ui->carNum->setText(buys->last().num);
        ui->clientName->setText(buys->last().clientName);
        ui->sellerName->setText(buys->last().prodName);
        ui->lineEdit_5->setText(QString::number(buys->last().price));
        buys->removeLast();
    }
    else{
        qDebug() << "the list is empty";
    }
}

