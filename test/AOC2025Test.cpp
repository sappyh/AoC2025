#include <catch2/catch_test_macros.hpp>

#include "PasswordDecoder.hpp"
#include "JoltageCalculator.hpp"
#include "InvalidDetector.hpp"

#include <fstream>
#include <iostream> 

constexpr uint32_t DAY1_PART2_ANSWER = 5657U;
constexpr uint64_t DAY2_PART2_ANSWER = 43872163557UL;
constexpr uint64_t DAY3_PART2_ANSWER = 172787336861064UL;


TEST_CASE("Password Decoder", "[decoder]")
{   
    std::ifstream rotations("./Inputs/Rotations.txt");

    PassWordDecoder decoder(rotations);

    try
    {
      REQUIRE(decoder.getPassword() == DAY1_PART2_ANSWER);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST_CASE("Invalid Detector", "[detector]")
{
    std::ifstream dataFile("./Inputs/DataEntries.txt");

    InvalidDetector detector(dataFile);

    try{
        auto invalidSum = detector.calculateInvalidSum(); 
        REQUIRE(invalidSum == DAY2_PART2_ANSWER);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}



TEST_CASE("Joltage Calculator", "[calculator]")
{  
    std::ifstream joltageFile("./Inputs/JoltageInput.txt");
    JoltageCalculator joltageCalculator(joltageFile);

    try {
        uint64_t outputJoltage = joltageCalculator.calculateOutputJoltage(12);
        REQUIRE(outputJoltage == DAY3_PART2_ANSWER);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    
    }

}




