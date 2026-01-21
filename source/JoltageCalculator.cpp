#include "JoltageCalculator.hpp"

uint64_t JoltageCalculator::calculateOutputJoltage(int nBatteries) {
    std::string joltageString;

    if (!mJoltageFile.is_open()) {
        throw std::runtime_error("Error Opening Joltage File");
    }

    while(mJoltageFile.peek() != EOF) {
        std::getline(mJoltageFile, joltageString);
        mOutputJoltage += calculateOutputJoltage(joltageString, nBatteries);
    }
    return mOutputJoltage;
}

uint64_t JoltageCalculator::calculateOutputJoltage(const std::string& joltageString, int nBatteries)
{    
    auto remainningString = joltageString;
    uint64_t maxNumber = 0;

    while(nBatteries > 0)
    {
        nBatteries--;
        char largestDigit = '\0';
        char largestDigitIndex = 0;

        for (size_t i = 0; i < remainningString.size() - nBatteries; i++)
        {
            if (remainningString[i] > largestDigit) {
                largestDigit = remainningString[i];
                largestDigitIndex = i;
            }
        }
        remainningString = remainningString.substr(largestDigitIndex+1);
        maxNumber = maxNumber * 10 + static_cast<uint64_t>(largestDigit - '0');
    }
    return maxNumber;
}