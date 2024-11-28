#include "Food.h"

Food::Food()
{
    foodPos = objPos();
}

Food::~Food()
{
    // No heap members
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int x_coord, y_coord, valid_coords;
    char diffSymbol;

    // Seed random with the current time
    srand(time(NULL));

    valid_coords = 0;

    // Randomly generate new coordinates until valid ones are found
    while (!valid_coords)
    {
        valid_coords = 1;
        x_coord = rand() % (X_SIZE - 2) + 1;
        y_coord = rand() % (Y_SIZE - 2) + 1;

        // Check every element of snake list
        for (int i = 0; i < blockOff->getSize(); i++)
        {
            if (x_coord == blockOff->getElement(i).pos->x && y_coord == blockOff->getElement(i).pos->y)
            {
                valid_coords = 0;
            }
        }
    }

    // Set the food position to these newly generated random coordinates
    foodPos.pos->x = x_coord;
    foodPos.pos->y = y_coord;
}

objPos Food::getFoodPos() const
{
    return foodPos;
}