#include "Food.h"

Food::Food()
{
    foodBucket = new objPosArrayList();

    // Three regular food items
    for (int i = 0; i < (FOOD_ITEMS / 2 + FOOD_ITEMS % 2); i++)
    {
        foodBucket->insertHead(objPos(0, 0, '@'));
    }

    // Two special food items
    for (int i = 0; i < FOOD_ITEMS / 2; i++)
    {
        char randomSymbol;
        bool notValid = 1;

        while (notValid)
        {
            notValid = 0;
            randomSymbol = rand() % 95 + 32;
            if(randomSymbol == '@' || randomSymbol == '#' || randomSymbol == ' ' || randomSymbol == '*')
            {
                notValid = 1;
            }
        }
        foodBucket->insertHead(objPos(0, 0, randomSymbol));
    }

}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList *blockOff)
{
    int x_coord, y_coord, valid_coords;
    int initial_size = foodBucket->getSize();
    char symbolsList[initial_size];
    bool notValid;

    // Generate random symbols for special food
    for (int i = 0; i < 2; i++)
    {   
        notValid = 1;
        while (notValid)
        {
            notValid = 0;
            symbolsList[i] = rand() % 95 + 32;
            if(symbolsList[i] == '@' || symbolsList[i] == '#' || symbolsList[i] == ' ' || symbolsList[i] == '*')
            {
                notValid = 1;
            }
        }
    }

    // Store symbols for normal food
    for (int i = 2; i < initial_size; i++)
    {   
        symbolsList[i] = foodBucket->getElement(i).getSymbol();
    }

    // Reset the food
    for (int i = 0; i < initial_size; i++)
        foodBucket->removeTail();

    // Seed random with the current time
    srand(time(NULL));

    for (int i = 0; i < initial_size; i++)
    {
        valid_coords = 0;

        // Randomly generate new coordinates until valid ones are found
        while (!valid_coords)
        {
            valid_coords = 1;
            x_coord = rand() % (X_SIZE - 2) + 1;
            y_coord = rand() % (Y_SIZE - 2) + 1;

            // Check every element of snake list
            for (int j = 0; j < blockOff->getSize(); j++)
            {
                if (x_coord == blockOff->getElement(j).pos->x && y_coord == blockOff->getElement(j).pos->y)
                {
                    valid_coords = 0;
                }
            }

            // Check other food items to ensure no overlap
            for (int j = 0; j < i; j++)
            {
                if (x_coord == foodBucket->getElement(j).pos->x && y_coord == foodBucket->getElement(j).pos->y)
                {
                    valid_coords = 0;
                }
            }
        }

        // Add new instance to list
        objPos added_food = objPos(x_coord, y_coord, symbolsList[i]);
        foodBucket->insertTail(added_food);
    }
}

objPosArrayList *Food::getFoodList() const
{
    return foodBucket;
}