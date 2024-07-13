#include "ecalc.h"

Ecalc::Ecalc() {}

int Ecalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 6;
        if(car->getbit() == false){
            g = 7;
        }
        int op;
        if(car->options.length() > 10){
            op = 210;
        }
        else op = 170;
        return g * car->year * op;
    }
    else{
        int g = 8;
        if(car->getbit() == false){
            g = 9;
        }
        int op;
        if(car->options.length() > 10){
            op = 300;
        }
        else op = 200;
        return g * car->year * op;
    }
}
