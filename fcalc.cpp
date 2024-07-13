#include "fcalc.h"

Fcalc::Fcalc() {}

int Fcalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 8;
        if(car->getbit() == false){
            g = 9;
        }
        int op;
        if(car->options.length() > 10){
            op = 250;
        }
        else op = 210;
        return g * car->year * op;
    }
    else{
        int g = 10;
        if(car->getbit() == false){
            g = 11;
        }
        int op;
        if(car->options.length() > 10){
            op = 350;
        }
        else op = 300;
        return g * car->year * op;
    }
}
