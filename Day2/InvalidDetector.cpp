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

        auto invalidValues = getInvalidValues(rangeStart, rangeEnd);
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
    } catch (const std::invalid_argument&) {
        throw std::runtime_error(std::string("Invalid number in range: '") + entry + "'");
    } catch (const std::out_of_range&) {
        throw std::runtime_error(std::string("Number out of range in: '") + entry + "'");
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