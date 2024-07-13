#include "ccalc.h"

Ccalc::Ccalc() {}

int Ccalc::getCost(Car *car)
{
    if(car->getprobeg() > 10000){
        int g = 4;
        if(car->getbit() == false){
            g = 5;
        }
        int op;
        if(car->options.length() > 10){
            op = 150;
        }
        else op = 100;
        return g * car->year * op;
    }
    else{
        int g = 6;
        if(car->getbit() == false){
            g = 7;
        }
        int op;
        if(car->options.length() > 10){
            op = 230;
        }
        else op = 140;
        return g * car->year * op;
    }
}
