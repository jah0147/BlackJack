cmake_minimum_required(VERSION 3.22)
project(BlackJack)

set(CMAKE_CXX_STANDARD 17)
#for Exe to work
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(BlackJack main.cpp console.cpp console.h game.cpp game.h config.h globals.cpp globals.h)
