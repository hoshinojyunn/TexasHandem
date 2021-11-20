cmake_minimum_required(VERSION 3.20)
project(TexasHandem)
set(SRC_LIST judge.cpp main.cpp Poker.cpp)
set(CMAKE_CXX_STANDARD 14)



add_executable(TexasHandem ${SRC_LIST})