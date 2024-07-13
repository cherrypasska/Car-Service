#include "basedcalc.h"

basedcalc::basedcalc() {}

int basedcalc::getCost(oneBuy *value)
{
    return value->price;
}
