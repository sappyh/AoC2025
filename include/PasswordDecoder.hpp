#include <fstream>
#include <utility>
#include <cstdint>

constexpr int MAX_POS = 100;
constexpr int START_POS = 50;

using namespace std;
class PassWordDecoder{
    public:
    PassWordDecoder(ifstream& rotations): mRotations(std::move(rotations)), mPosition(START_POS), mZeroCount(0){};
    uint32_t getPassword();

    private:
    std::ifstream mRotations;
    uint32_t mZeroCount;
    int mPosition;
    int getNextRotation();
    void updatePosition(int rotationStep);
};