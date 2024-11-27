#include "objPos.h"
#include "stdlib.h"
#include "time.h"

#ifndef FOOD_H
#define FOOD_H

class Food
{
    private:
    objPos foodPos;

    public:
    Food();
    ~Food();

    void generateFood(objPos blockOff);
    objPos getFoodPos() const;

};
#endif