#include "PasswordDecoder.hpp"
#include <iostream>

constexpr int LEFT = -1;
constexpr int RIGHT = 1;


uint32_t PassWordDecoder::getPassword()
{
    /** Check if the file is open **/ 
    if (!mRotations.is_open())
    {
        throw std::runtime_error("Error Opening File");
    }

   while(mRotations.peek() != EOF)
   {
        int rotation = getNextRotation();
        updatePosition(rotation);
   }
   
   return mZeroCount;

}

int PassWordDecoder::getNextRotation()
{
     /** Read a line */
    string currentLine;
    getline(mRotations, currentLine);

    /** Parse the line into direction and steps **/
    char directionChar = currentLine[0];
    int steps = stoi(currentLine.substr(1));

    if (directionChar == 'L')
    {
        return LEFT * steps;
    }
    else if (directionChar == 'R')
    {
        return RIGHT * steps;
    }
}

void PassWordDecoder::updatePosition(int rotationStep)
{
    mPosition = ((mPosition + rotationStep) % MAX_POS + MAX_POS) % MAX_POS;
    if (mPosition == 0)
    {
        mZeroCount++;
    }
}