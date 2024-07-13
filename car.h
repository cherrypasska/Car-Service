#ifndef CAR_H
#define CAR_H

#include <QString>

class Car {
public:
    enum CarClass {
        MINICAR,
        SMALLSITYCAR,
        COMFORTCAR,
        COMFORTPLUSCAR,
        EXPENSIVE,
        SCLASS
    };
    Car() = default;
    Car(QString cname, QString cnun, bool b, int prob, QString op, int y, CarClass c)
        : carname(cname), carnum(cnun), bit(b), probeg(prob), options(op), year(y), flag(false), clas(c) {}
    void setPrice(int pr){
        price = pr;
    }
    int getPrice(){
        return price;
    }
    QString getname(){
        return carname;
    }
    QString getnum(){
        return carnum;
    }
    bool getbit(){
        return bit;
    }
    int getprobeg(){
        return probeg;
    }
    QString getoptions(){
        return options;
    }
    bool getflag(){
        return flag;
    }
    CarClass getclas(){
        return clas;
    }
    int price;
    QString carname;
    QString carnum;
    bool bit;
    int probeg;
    QString options;
    int year;
    bool flag;
    CarClass clas;
};

#endif // CAR_H
