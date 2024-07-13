#include "calcfacade.h"

calcfacade::calcfacade(QObject *parent) : QObject(parent)
{

}
int calcfacade::getCost(Car *value)
{
    int cost;
    switch (value->getclas()) {
    case Car::CarClass::MINICAR:
        cost = Acalc::getCost(value);
        break;
    case Car::CarClass::SMALLSITYCAR:
        cost = Bcalc::getCost(value);
        break;
    case Car::CarClass::COMFORTCAR:
        cost = Ccalc::getCost(value);
        break;
    case Car::CarClass::COMFORTPLUSCAR:
        cost = Dcalc::getCost(value);
        break;
    case Car::CarClass::EXPENSIVE:
        cost = Ecalc::getCost(value);
        break;
    case Car::CarClass::SCLASS:
        cost = Fcalc::getCost(value);
        break;
    default:
        cost = -1;
        break;
    }
    return cost;
}
