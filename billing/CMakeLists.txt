cmake_minimum_required(VERSION 3.5)

project(billing LANGUAGES CXX)

set (CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}/usr/include/c++/9")

#set (INCLUDEPATH "${INCLUDEPATH}/usr/include/c++/9")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(billing main.cpp)
