#ifndef CALCFACADE_H
#define CALCFACADE_H
#include "car.h"
#include "acalc.h"
#include "bcalc.h"
#include "ccalc.h"
#include "dcalc.h"
#include "ecalc.h"
#include "fcalc.h"
#include <QObject>

class calcfacade: public QObject
{
    Q_OBJECT
public:
    calcfacade();
    explicit calcfacade(QObject *parent = nullptr);
    static int getCost(Car *value);
};

#endif // CALCFACADE_H
