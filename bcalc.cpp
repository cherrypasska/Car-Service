#include "bcalc.h"
#include "car.h"
Bcalc::Bcalc() {}

int Bcalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 2;
        if(car->getbit() == false){
            g = 3;
        }
        int op;
        if(car->options.length() > 10){
            op = 130;
        }
        else op = 70;
        return g * car->year * op;
    }
    else{
        int g = 3;
        if(car->getbit() == false){
            g = 5;
        }
        int op;
        if(car->options.length() > 10){
            op = 190;
        }
        else op = 80;
        return g * car->year * op;
    }
}
