#include "megacalc.h"

megacalc::megacalc() {}

int megacalc::getCost(oneBuy *value)
{
    return value->price*1.5;
}
