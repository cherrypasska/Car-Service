#ifndef CLINTS_H
#define CLINTS_H
#include "Client.h"

class clints
{
public:
    clints();
    QList<Client>* clients;
    void addCar(QString num, Car car);
};

#endif // CLINTS_H
