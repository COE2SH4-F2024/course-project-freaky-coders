#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Copy constructor (unused however implemented as per rule of 4)
objPosArrayList::objPosArrayList(objPosArrayList &list)
{
    listSize = list.listSize;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
    for (int i = 0; i < listSize; i++)
    {
        aList[i] = list.aList[i];
    }
}

// Copy Assignment Operator (unused however implemented as per rule of 4)
objPosArrayList& objPosArrayList::operator=(objPosArrayList &list)
{
    listSize = list.listSize;
    arrayCapacity = ARRAY_MAX_CAP;
    for (int i = 0; i < listSize; i++)
    {
        aList[i] = list.aList[i];
    }

    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // First, check we have not exceeded capacity
    if (listSize < arrayCapacity)
    {
        listSize++;
        for (int i = listSize - 1; i > 0; i--)
        {
            // Shift the elements down
            aList[i] = aList[i - 1];
        }
        // Insert the given element at the head of the list
        aList[0] = thisPos;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // First, check we have not exceeded capacity
    if (listSize < arrayCapacity)
    {
        // Insert element at tail
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    // Check this would not result in a negative list size
    if (listSize > 0)
    {
        for (int i = 0; i < listSize - 1; i++)
        {
            // Shift elements down
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    // Check this would not result in a negative list size
    if (listSize > 0)
    {
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    // Ensure the index is valid input
    if (index >= 0 && index < listSize)
    {
        return aList[index];
    }
}