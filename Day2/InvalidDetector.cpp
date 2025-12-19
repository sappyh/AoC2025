#include "InvalidDetector.hpp"
#include <algorithm>
#include <cctype>
#include <string>

uint64_t InvalidDetector::calculateInvalidSum()
{
    /** Check if the file is open **/ 
    if (!mDataFile.is_open())
    {
        throw std::runtime_error("Error Opening File");
    }

   while(mDataFile.peek() != EOF)
   {
        std::string currentEntry;
        getline(mDataFile, currentEntry, ',');
        auto [rangeStart, rangeEnd] = parseRange(currentEntry);

        auto invalidValues = getInvalidValuesN(rangeStart, rangeEnd);
        for (const auto& val : invalidValues)
        {
            mInvalidSum += static_cast<uint64_t>(val);
        }
   }
   
   return mInvalidSum;

}

std::pair<uint64_t, uint64_t> InvalidDetector::parseRange(const std::string& entry)
{
    /** Should have the format x-y */
    size_t dashPos = entry.find('-');
    if (dashPos == std::string::npos)
    {
        throw std::runtime_error(std::string("Invalid Range Format: '") + entry + "'");   
    }

    try {
        uint64_t start = static_cast<uint64_t>(std::stoll(entry.substr(0, dashPos)));
        uint64_t end = static_cast<uint64_t>(std::stoll(entry.substr(dashPos + 1)));
        return std::make_pair(start, end);
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Error Parsing Range: '") + entry + "' - " + e.what());
    }
}

std::vector<uint64_t> InvalidDetector::getInvalidValues(uint64_t rangeStart, uint64_t rangeEnd)
{
    std::vector<uint64_t> invalidValues;
    for (uint64_t i = rangeStart; i <= rangeEnd; )
    {
        /** Count the number of digits */
        auto countDigits = std::to_string(i).length();
        if (countDigits % 2 == 0)
        {
            uint64_t pow10 = static_cast<uint64_t>(std::pow(10, countDigits / 2));
            uint64_t leftSide = i / pow10;
            uint64_t rightSide = i % pow10;

            if (leftSide == rightSide)
            {   
                invalidValues.push_back(i);
            }
            else if (leftSide > rightSide)
            {
                /** We can skip all the numbers where the right side is smaller than the left side */
                i += (leftSide - rightSide) - 1;
            }
        }
        i++;
    }
    return invalidValues;
}

std::vector<uint64_t> InvalidDetector::getInvalidValuesN(uint64_t rangeStart, uint64_t rangeEnd)
{
    std::vector<uint64_t> invalidValues;
    for (uint64_t i = rangeStart; i <= rangeEnd; i++)
    {
        /** This is a pattern matching problem hence convert the int to string */
        std::string numStr = std::to_string(i);

        /** Since all prefix substrings must start at 0 */
        int substringLeftIndex = 0;
        for (int subStringRightIndex = substringLeftIndex + 1; subStringRightIndex < numStr.length(); subStringRightIndex++)
        {
                int lengthOfSubString = subStringRightIndex - substringLeftIndex;
                /** Extract the substring */
                std::string subStringtoMatch = numStr.substr(substringLeftIndex, lengthOfSubString);

                /** Check if the string is composed of this substring repeated */
                std::string remainingStr = numStr.substr(subStringRightIndex);

                while(remainingStr.length() >= subStringtoMatch.length())
                {
                    std::string nextSubString = remainingStr.substr(0, lengthOfSubString);
                    if (nextSubString != subStringtoMatch)
                    {
                        break;
                    }
                    remainingStr = remainingStr.substr(lengthOfSubString);
                }

                if (remainingStr.empty())
                {   
                    invalidValues.push_back(i);                
                    break;  
                }
                
        }

    }
    return invalidValues;
}