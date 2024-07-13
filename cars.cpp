#include "calcfacade.h"
#include "car.h"
#include "cars.h"
#include "ui_cars.h"

#include <QHash>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>

Cars::Cars(QWidget *parent)
    : QWidget(parent), ui(new Ui::Cars), cars(new QHash<QString, Car>), flag(false)
{
    ui->setupUi(this);
    buys = new QList<oneBuy>();
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 140);
    ui->tableWidget->setColumnWidth(2, 70);
    ui->tableWidget->setColumnWidth(3, 140);
    ui->tableWidget->setColumnWidth(4, 300);
    ui->tableWidget->setColumnWidth(5, 90);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер" << "Название машины" << "Год" << "Цена" << "Опции" << "Пробег");
    zap();
    zapbuys();
    if(flag) print(ui->tableWidget);
    ui->addCar->setEnabled(false);
    ui->delCar->setEnabled(false);
    ui->searchByNum->setEnabled(false);
}

void Cars::zapbuys()
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

Cars::~Cars() {
    delete ui;
    delete cars;
}

void Cars::on_addCar_clicked() {
    bool b = false;;
    for(int i = 0;i<buys->size();i++){
        if(buys->at(i).num == ui->num->text()) b = true;
    }
    if(!b){
        bool checkbit = false;
        Car::CarClass clas;
        QString s;
        switch (index) {
        case 0:
            clas = Car::MINICAR;
            s = "A";
            break;
        case 1:
            clas = Car::SMALLSITYCAR;
            s = "B";
            break;
        case 2:
            clas = Car::COMFORTCAR;
            s = "C";
            break;
        case 3:
            clas = Car::COMFORTPLUSCAR;
            s = "D";
            break;
        case 4:
            clas = Car::EXPENSIVE;
            s = "E";
            break;
        case 5:
            clas = Car::SCLASS;
            s = "F";
            break;
        default:
            break;
        }
        Car *c = new Car(ui->carname->text(), ui->num->text(), checkbit, ui->probeg->text().toInt(), options, ui->year->text().toInt(), clas);
        int value = calcfacade::getCost(c);
        c->setPrice(value);
        if(!cars->contains(ui->num->text())){
            QString str = ui->carname->text() + '\n' + ui->num->text() + '\n';
            if(checkbit) {
                str += "битая\n";
            } else {
                str += "нет\n";
            }
            str += ui->probeg->text() + '\n' + options + '\n' + ui->year->text() + '\n' + s;
            if(cars->contains(c->carnum)) {
                qDebug() << "Машина с таким номером уже зарегистрирована";
            } else {
                cars->insert(c->carnum, *c);
                QFile file("C:/Qt/untitled/cars/" + ui->num->text() + ".txt");
                if(file.open(QIODeviceBase::WriteOnly)) {
                    QTextStream out(&file);
                    out << str;
                }
                print(ui->tableWidget);
            }
        }
        else{
            qDebug() << "Car already exist";
        }
    }
    else{
        qDebug() << "Car already sell";
    }
}

void Cars::print(QTableWidget *table) {
    table->clear();
    zap();
    int row = 0;
    for (const auto &c : cars->values()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(c.carnum));
        table->setItem(row, 1, new QTableWidgetItem(c.carname));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(c.year)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(c.price)));
        table->setItem(row, 4, new QTableWidgetItem(c.options));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(c.probeg)));
        row++;
        if(c.carnum == ""){
            break;
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер" << "Название машины" << "Год" << "Цена" << "Опции" << "Пробег");
}

void Cars::on_delCar_clicked() {
    if(cars->contains(ui->num->text())) {
        cars->remove(ui->num->text());
        QFile file("C:/Qt/untitled/cars/" + ui->num->text() + ".txt");
        file.remove();
        print(ui->tableWidget);
        qDebug() << "Машина успешно удалена.";
    } else {
        qDebug() << "Машины с таким номером нет.";
    }
}

void Cars::on_checkAuto_clicked() {
    print(ui->tableWidget);
}

void Cars::on_searchByNum_clicked() {
    if(cars->contains(ui->num->text())) {
        Car p = cars->take(ui->num->text());
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(p.carnum));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(p.carname));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(p.year)));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(p.price)));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(p.options));
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(p.probeg)));
    }
}

void Cars::zap() {
    QString folderPath = "C:/Qt/untitled/cars";
    QDir directory(folderPath);
    if (!directory.exists()) {
        qDebug() << "unable to access the database";
        return;
    }
    if(directory.isEmpty()) {
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
            bool fl = data[2] == "битая";
            Car::CarClass clas;
            if(data[6] == "A") clas = Car::MINICAR;
            else if(data[6] == "B") clas = Car::SMALLSITYCAR;
            else if(data[6] == "C") clas = Car::SMALLSITYCAR;
            else if(data[6] == "D") clas = Car::SMALLSITYCAR;
            else if(data[6] == "E") clas = Car::SMALLSITYCAR;
            else clas = Car::SCLASS;
            Car cl(data[0], data[1], fl, data[3].toInt(), data[4], data[5].toInt(), clas);
            cl.setPrice(calcfacade::getCost(&cl));
            cars->insert(cl.carnum, cl);
        }
        file.close();
    }
}

void Cars::on_checkByOptions_clicked() {
    int row = 0;
    ui->tableWidget->clear();
    for (const auto &p : cars->values()) {
        if(p.options == options && p.bit == checkbit && p.carname == ui->carname->text() && ui->probeg->text().toInt() <= p.probeg) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(p.carnum));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(p.carname));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(p.year)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(p.price)));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(p.options));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(p.probeg)));
            row++;
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер" << "Название машины" << "Год" << "Цена" << "Опции" << "Пробег");
}

void Cars::checkEq(QString &s)
{
    QString str;
    if(ui->rule->isChecked()){
        str+="обогрев руля,";

    }
    if(ui->sits->isChecked()){
        str+="подогрев сидений,";
    }
    if(ui->antirain->isChecked()){
        str+="антидождь,";
    }
    if(ui->top->isChecked()){
        str+="панорамная крыша,";
    }
    if(str.isEmpty()){
        str = "Нет";
    }
    else{
        str.chop(1);
    }
    s = str;
}

void Cars::on_sits_clicked()
{
    checkEq(options);
}

void Cars::on_rule_clicked()
{
    checkEq(options);
}

void Cars::on_antirain_clicked()
{
    checkEq(options);
}

void Cars::on_top_clicked()
{
    checkEq(options);
}

void Cars::on_bitai_clicked(bool checked)
{
    checkbit = checked;
}


void Cars::on_comboBox_currentIndexChanged(int index)
{
    this->index = index;
}

void Cars::check()
{
    if(ui->carname->text().isEmpty() || ui->num->text().isEmpty() || ui->probeg->text().isEmpty() || ui->year->text().isEmpty() || ui->year->text().length() < 4){
        ui->addCar->setEnabled(false);
    }
    else{
        ui->addCar->setEnabled(true);
    }
    if(ui->num->text().isEmpty()){
        ui->delCar->setEnabled(false);
        ui->searchByNum->setEnabled(false);
    }
    else{
        ui->delCar->setEnabled(true);
        ui->searchByNum->setEnabled(true);
    }
}


void Cars::on_num_textChanged(const QString &arg1)
{
    check();
}


void Cars::on_probeg_textChanged(const QString &arg1)
{
    check();
}


void Cars::on_year_textChanged(const QString &arg1)
{
    check();
}


void Cars::on_carname_textChanged(const QString &arg1)
{
    check();
}
