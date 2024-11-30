#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    boardSizeX = 20;
    boardSizeY = 10;
    exitFlag = 0;
    loseFlag = 1;
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // No items on heap, no destructor necessary
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setLoseFlag()
{
    loseFlag = 1;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}