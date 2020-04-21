cmake_minimum_required(VERSION 3.15)
project(FileSystem)

set(CMAKE_CXX_STANDARD 11)
add_executable(FileSystem TestFilesystemManager.cpp FilesystemManager.cpp FilesystemManager.h)
target_link_libraries(FileSystem stdc++fs)