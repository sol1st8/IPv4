cmake_minimum_required(VERSION 3.11)

project(IPv4 CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(IPv4 main.cpp)

target_link_libraries(IPv4 -lstdc++)
