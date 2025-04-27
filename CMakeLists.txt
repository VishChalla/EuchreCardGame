cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(CPP_Euchre)

add_executable(CPP_Euchre src/main.cpp)
include_directories(.)

set(UNIT_TESTS src/Test.cpp)
set(MAIN_FILE src/main.cpp)

add_executable(testlib-test src/Test.cpp src/Dealer.cpp src/Player.cpp src/Deck.cpp)
