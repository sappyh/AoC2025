add_library(PasswordDecoder PasswordDecoder.cpp)

add_executable(test test.cpp)
target_link_libraries(test PasswordDecoder)