#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs *thisGMRef, Food *foodReference)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = foodReference;

    // more actions to be included

    // Instantiating PlayPosition ArrayList as snake will hold multiple locations
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(10, 5, '*')); // Starting Position
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement();
}

objPosArrayList *Player::getPlayerPosList() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    if (input != 0)
    {
        switch (input)
        {
        case 27:
            // Escape key, exit game
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

void Player::movePlayer()
{
    objPos currentHead = playerPosList->getHeadElement(); // Get current head position
    objPos newHead = currentHead;                         // Create a new position object based on current position
    bool foodCollision = false;

    if (myDir == STOP)
    {
        // If the snake is stationary, do nothing
        return;
    }

    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        newHead.pos->y = (currentHead.pos->y - 1);
        if (newHead.pos->y == 0)
        {
            newHead.pos->y = mainGameMechsRef->getBoardSizeY() - 2; // Wrap to bottom boundary
        }
        break;

    case DOWN:
        newHead.pos->y = (currentHead.pos->y + 1);
        if (newHead.pos->y == mainGameMechsRef->getBoardSizeY() - 1)
        {
            newHead.pos->y = 1; // Wrap to top boundary
        }
        break;

    case LEFT:
        newHead.pos->x = (currentHead.pos->x - 1);
        if (newHead.pos->x == 0)
        {
            newHead.pos->x = mainGameMechsRef->getBoardSizeX() - 2; // Wrap to right boundary
        }
        break;

    case RIGHT:
        newHead.pos->x = (currentHead.pos->x + 1);
        if (newHead.pos->x == mainGameMechsRef->getBoardSizeX() - 1)
        {
            newHead.pos->x = 1; // Wrap to left boundary
        }
        break;

    default:
        break;
    }

    // Check for self collision
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        if (playerPosList->getElement(i).isPosEqual(&newHead))
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }
    }

    // Check for food collision
    for (int i = 0; i < food->getFoodList()->getSize(); i++)
    {
        
        if (food->getFoodList()->getElement(i).isPosEqual(&newHead))
        {
            playerPosList->insertHead(newHead);
            if (!(food->getFoodList()->getElement(i).getSymbol() == '@'))
            {
                // Just normal movement if its a special food (with score increment)
                playerPosList->removeTail();
            }
            foodCollision = true;
            food->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
        }
    }

    if (!foodCollision)
    {
        playerPosList->insertHead(newHead); // Regular movement
        playerPosList->removeTail();        // Remove the tail
    }
}