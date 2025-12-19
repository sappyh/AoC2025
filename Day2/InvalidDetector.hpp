#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

class InvalidDetector {
public:
    InvalidDetector(std::ifstream& dataFile) : mDataFile(std::move(dataFile)), mInvalidSum(0) {};

    uint64_t calculateInvalidSum();

    private:
    std::ifstream mDataFile;
    uint64_t mInvalidSum;
    
    std::pair<uint64_t, uint64_t> parseRange(const std::string& line);
    std::vector<uint64_t> getInvalidValues(uint64_t rangeStart, uint64_t rangeEnd);
    std::vector<uint64_t> getInvalidValuesN(uint64_t rangeStart, uint64_t rangeEnd);
};

