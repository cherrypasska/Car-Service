#include "states.h"
States::States(QObject *parent) : QObject(parent)
{
    actualData = nullptr;
}
States::~States()
{
    if(actualData){
        delete actualData;
        actualData = nullptr;
    }
    qDeleteAll(array);
    array.clear();
}

void States::undo()
{
    if (array.isEmpty()) {
        actualData = nullptr;
    }
    else {
        actualData = array.last();
        array.removeLast();
    }
}

bool States::hasStates()
{
    return !array.empty();
}

oneBuy *States::getActualData()
{
    return actualData;
}

void States::add(oneBuy *value)
{
    array.append(value);
}
