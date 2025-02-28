cmake_minimum_required(VERSION 3.10)

# Project name and version
project(INS_Calibration VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard (can be 14, 17, 20, etc.)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# If you want to use the Eigen library you have in eigen-3.4.0,
# you can treat it as a header-only library by just adding its path:
include_directories(${CMAKE_SOURCE_DIR}/eigen-3.4.0)

# Also include your own headers from the include/ folder
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all .cpp files in src/ into a list
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(ins_calibration ${SOURCES})


