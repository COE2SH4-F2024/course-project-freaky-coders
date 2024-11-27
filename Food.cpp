#include "Food.h"

Food::Food() {
    foodPos = objPos();
}

Food::~Food() {
    // No heap members
}

void Food::generateFood(objPos blockOff) {
    int x_coord, y_coord, valid_coords;
    char diffSymbol;
    srand(time(NULL));

    valid_coords = 0;
    while (!valid_coords)
    {
        valid_coords = 1;
        x_coord = rand() % (20 - 2) + 1;
        y_coord = rand() % (10 - 2) + 1;

        if (x_coord == blockOff.pos->x && y_coord == blockOff.pos->y)
        {
            valid_coords = 0;
        }
    }

    foodPos.pos->x = x_coord;
    foodPos.pos->y = y_coord;

}

objPos Food::getFoodPos() const {
    return foodPos;
}