#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define X_SIZE 20
#define Y_SIZE 10

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *player;
GameMechs *gameMechs;
Food *food;

int main(void)
{

    Initialize();

    while (gameMechs->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Initialize three main objects
    gameMechs = new GameMechs(X_SIZE, Y_SIZE);
    food = new Food();
    player = new Player(gameMechs, food);

    // Generate first coordinates for food
    food->generateFood(player->getPlayerPosList());
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        gameMechs->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Iterate through the board
    for (int i = 0; i < Y_SIZE; i++)
    {
        for (int j = 0; j < X_SIZE; j++)
        {

            bool isSnake = false;
            bool isFood = false;

            // Check if the current position corresponds to a part of the snake
            for (int k = 0; k < player->getPlayerPosList()->getSize(); k++)
            {
                objPos bodyPart = player->getPlayerPosList()->getElement(k);
                if (bodyPart.pos->x == j && bodyPart.pos->y == i)
                {
                    MacUILib_printf("%c", bodyPart.symbol); // Draw the snake body part
                    isSnake = true;
                    break;
                }
            }

            // Check if its Food
            for(int k = 0; k < food->getFoodList()->getSize(); k++)
            {
                if(j == food->getFoodList()->getElement(k).pos->x && i == food->getFoodList()->getElement(k).pos->y)
                {
                    MacUILib_printf("%c", food->getFoodList()->getElement(k).getSymbol());
                    isFood = true;
                }
            }
            
            if (!isSnake && !isFood)
            {
                // Check if its a Border
                if (j == 0 || j == (X_SIZE - 1) || i == 0 || i == (Y_SIZE - 1))
                {
                    MacUILib_printf("#");
                }

                // Otherwise just whitespace
                else
                {
                    MacUILib_printf(" ");
                }
            }

        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n", gameMechs->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (gameMechs->getLoseFlagStatus())
    {
        MacUILib_printf("You lost.");
    }

    else
    {
        MacUILib_printf("You Won!");
    }

    delete player;
    delete gameMechs;
    delete food;

    MacUILib_uninit();
}
