# CMake version
cmake_minimum_required(VERSION 3.30)

# Project name
project(EventHandler)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Add library
add_library(EventHandler include/sigslot.h src/sigslot.cpp)