cmake_minimum_required(VERSION 3.10)
project (event_queues)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")

add_executable(app main.cpp "Logger.h" "Logger.cpp" "Thread.h" "Thread.cpp" "TasksQueue.h" "TasksQueue.cpp" "Task.h")

