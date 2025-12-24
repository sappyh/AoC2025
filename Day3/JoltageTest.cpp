#include "JoltageCalculator.hpp"

#include <stdexcept>
#include <fstream>
#include <iostream> 

int main()
{
    std::ifstream joltageFile("../../JoltageInput.txt");
    JoltageCalculator joltageCalculator(joltageFile);

    try {
        uint64_t outputJoltage = joltageCalculator.calculateOutputJoltage(12);
        std::cout << "Total Output Joltage: " << outputJoltage << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}