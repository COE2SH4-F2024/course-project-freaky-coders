#include "objPosArrayList.h"
#include "stdlib.h"
#include "time.h"

#ifndef FOOD_H

#define X_SIZE 20
#define Y_SIZE 10
#define FOOD_ITEMS 5
#define FOOD_H

class Food
{
private:
    objPosArrayList* foodBucket;

public:
    Food();
    ~Food();

    void generateFood(objPosArrayList *blockOff);
    objPosArrayList* getFoodList() const;
};
#endif