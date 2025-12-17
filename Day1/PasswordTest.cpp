#include "PasswordDecoder.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

int main()
{
    std::ifstream rotations("../../Rotations.txt");

    PassWordDecoder decoder(rotations);

    try{
        auto password = decoder.getPassword();
        std::cout << "Password: " << password <<std::endl;
    }

    catch(const std::exception& e)
    {
        std::cout << e.what() <<std::endl;
        exit(0);
    }
   
    return 0;
}