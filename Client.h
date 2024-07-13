#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QHash>
#include "car.h"

class Client{
public:
    QString ClientName;
    QString cars;
    QString clientPas;
    Client(QString l, QString client, QString pas){
        cars = l;
        ClientName = client;
        clientPas = pas;
    }
};

#endif // CLIENT_H
