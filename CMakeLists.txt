cmake_minimum_required(VERSION 3.10)

# Projektets navn
project(hero)

# Sæt standard C++-version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gør headers tilgængelige for alle kildefiler
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Find alle .cpp filer i src/ folderen
file(GLOB SOURCES "src/*.cpp")

# Opret exe fil fra main.cpp og andre cpp-filer
add_executable(hero ${SOURCES})