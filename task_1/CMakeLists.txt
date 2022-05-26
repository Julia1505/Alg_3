cmake_minimum_required(VERSION 3.0)
project(task_1_Technopark)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror")

add_executable(task_1 main.cpp ListGraph.cpp MatrixGraph.cpp SetGraph.cpp ArcGraph.cpp)
