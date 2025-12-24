#include <fstream>
#include <cstdint>
#include <string>
#include <iostream>

class JoltageCalculator {
    public:
        JoltageCalculator(std::ifstream& inputJoltageFile): mJoltageFile{std::move(inputJoltageFile)}, mOutputJoltage{0} {};
        uint64_t calculateOutputJoltage(int nBatteries = 2);

    private:
        std::ifstream mJoltageFile;
        uint64_t mOutputJoltage;

        /** Function for calculating the maximum output joltage for a given string
         * The joltage string is larger than what can be stored in uint64_t, hence the need for string processing
         * Although the function at max will only return a uint8_t value, it will be summed into a uint64_t total
         * @param joltageString The string representing the joltage configuration
         * @return The maximum output joltage as a uint64_t
         */
        uint64_t calculateOutputJoltage(const std::string& joltageString, int nBatteries= 2);
};
