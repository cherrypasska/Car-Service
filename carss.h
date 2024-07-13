#ifndef CARSS_H
#define CARSS_H
#include "car.h"
#include <QHash>
class carss
{
public:
    carss();
    QHash<QString, car>* cars;
};

#endif // CARSS_H
