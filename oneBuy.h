#ifndef ONEBUY_H
#define ONEBUY_H

#include <QString>
#include <QDate>

class oneBuy
{
public:
    oneBuy(QString clName, QString prName, QString carName, QString nums, int price, QDate date, QString pass)
        : clientName(clName), prodName(prName), carName(carName), num(nums), price(price), date(date), passport(pass)
    {}
    QDate date;
    QString passport;
    QString clientName;
    QString prodName;
    QString carName;
    int price;
    QString num;
};

#endif // ONEBUY_H
