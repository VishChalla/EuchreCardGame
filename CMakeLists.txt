cmake_minimum_required(VERSION 3.14)
project(EuchreCardGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(euchre_lib src/Deck.cpp src/Player.cpp src/Dealer.cpp)
target_include_directories(euchre_lib PUBLIC src)
if(NOT MSVC)
    target_compile_options(euchre_lib PRIVATE -Wall -Wextra)
endif()

add_executable(euchre src/main.cpp)
target_link_libraries(euchre PRIVATE euchre_lib)

enable_testing()
add_executable(euchre_tests tests/Test.cpp)
target_link_libraries(euchre_tests PRIVATE euchre_lib)
add_test(NAME euchre_tests COMMAND euchre_tests)
