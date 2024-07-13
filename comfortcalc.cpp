#include "comfortcalc.h"

comfortcalc::comfortcalc() {}

int comfortcalc::getCost(oneBuy *value)
{
    return value->price*1.1;
}
