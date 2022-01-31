cmake_minimum_required(VERSION 3.10)
project (cards)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")

add_executable(app main.cpp Card.cpp Deck.cpp)

