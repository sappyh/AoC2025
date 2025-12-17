#include "InvalidDetector.hpp"

int main()
{
    std::ifstream dataFile("../../DataEntries.txt");

    InvalidDetector detector(dataFile);

    try{
        auto invalidSum = detector.calculateInvalidSum();
        std::cout << "Invalid Sum: " << invalidSum <<std::endl;
    }

    catch(const std::exception& e)
    {
        std::cout << e.what() <<std::endl;
        exit(0);
    }
   
    return 0;
}