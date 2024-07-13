#include "dcalc.h"

Dcalc::Dcalc() {}

int Dcalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 5;
        if(car->getbit() == false){
            g = 6;
        }
        int op;
        if(car->options.length() > 10){
            op = 180;
        }
        else op = 140;
        return g * car->year * op;
    }
    else{
        int g = 7;
        if(car->getbit() == false){
            g = 8;
        }
        int op;
        if(car->options.length() > 10){
            op = 260;
        }
        else op = 170;
        return g * car->year * op;
    }
}
