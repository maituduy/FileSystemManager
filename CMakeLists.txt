cmake_minimum_required(VERSION 3.15)
project(FileSystem)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp")

find_package (Threads)

add_executable(FileSystem ${SOURCES})
target_link_libraries(FileSystem stdc++fs Threads::Threads)