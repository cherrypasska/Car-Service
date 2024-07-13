#include "acalc.h"

Acalc::Acalc() {}

int Acalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 1;
        if(car->getbit() == false){
            g = 2;
        }
        int op;
        if(car->options.length() > 10){
            op = 100;
        }
        else op = 50;
        return g * car->year * op;
    }
    else{
        int g = 2;
        if(car->getbit() == false){
            g = 4;
        }
        int op;
        if(car->options.length() > 10){
            op = 170;
        }
        else op = 80;
        return g * car->year * op;
    }
}
