#include "luxecalc.h"

luxecalc::luxecalc() {}

int luxecalc::getCost(oneBuy *value)
{
    return value->price*1.25;
}
