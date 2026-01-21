Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.11.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(AOC2025Test AOC2025Test.cpp)
target_link_libraries(AOC2025Test PasswordDecoder InvalidDetector JoltageCalculator Catch2::Catch2WithMain)

add_test(NAME AOC2025Test
        COMMAND AOC2025Test
     )