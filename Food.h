#include "objPosArrayList.h"
#include "stdlib.h"
#include "time.h"

#ifndef FOOD_H

#define X_SIZE 20
#define Y_SIZE 10
#define FOOD_H

class Food
{
private:
    objPos foodPos;

public:
    Food();
    ~Food();

    void generateFood(objPosArrayList *blockOff);
    objPos getFoodPos() const;
};
#endif