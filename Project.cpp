#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
#define X_SIZE 20
#define Y_SIZE 10
#define ITEM_NUMBER 5

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *p;
GameMechs *g;

int main(void)
{

    Initialize();

    while (g->getExitFlagStatus() == false)
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

    g = new GameMechs(X_SIZE, Y_SIZE);
    p = new Player(g);
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        g->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    p->updatePlayerDir();
    p->movePlayer();
    g->clearInput();
}

void DrawScreen(void)
{
    int i, j;

    MacUILib_clearScreen();

    for (i = 0; i < Y_SIZE; i++)
    {
        for (j = 0; j < X_SIZE; j++)
        {

            if (j == p->getPlayerPos().pos->x && i == p->getPlayerPos().pos->y)
            {
                MacUILib_printf("%c", p->getPlayerPos().symbol);
            }

            else if (j == 0 || j == (X_SIZE - 1) || i == 0 || i == (Y_SIZE - 1))
            {
                MacUILib_printf("#");
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", g->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (g->getLoseFlagStatus())
    {
        MacUILib_printf("You lost.");
    }

    else
    {
        MacUILib_printf("You Won!");
    }

    delete p;
    delete g;

    MacUILib_uninit();
}
