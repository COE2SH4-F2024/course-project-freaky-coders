#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = 10;
    playerPos.pos->y = 5;
    playerPos.symbol = '*';
    myDir = STOP;
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    if (input != 0)
    {
        switch (input)
        {
        case 27:
            mainGameMechsRef->setExitTrue();
            break;
            
        case 'w':
            if (myDir != UP && myDir != DOWN)
                myDir = UP;
            break;

        case 'a':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = LEFT;
            break;

        case 's':
            if (myDir != UP && myDir != DOWN)
                myDir = DOWN;
            break;

        case 'd':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT;
            break;

        default:
            break;
        }
    }
}
g
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        playerPos.pos->y = (playerPos.pos->y - 1) % (mainGameMechsRef->getBoardSizeY() - 1) + (mainGameMechsRef->getBoardSizeY() - 2) * (playerPos.pos->y == 1);
        break;

    case DOWN:
        playerPos.pos->y = (playerPos.pos->y + 1) % (mainGameMechsRef->getBoardSizeY() - 1) + (playerPos.pos->y == (mainGameMechsRef->getBoardSizeY() - 2));
        break;

    case LEFT:
        playerPos.pos->x = (playerPos.pos->x - 1) % (mainGameMechsRef->getBoardSizeX() - 1) + (mainGameMechsRef->getBoardSizeX() - 2) * (playerPos.pos->x == 1);
        break;

    case RIGHT:
        playerPos.pos->x = (playerPos.pos->x + 1) % (mainGameMechsRef->getBoardSizeX() - 1) + (playerPos.pos->x == (mainGameMechsRef->getBoardSizeX() - 2));
        break;

    default:
        break;
    }
}

// More methods to be added