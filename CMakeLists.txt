cmake_minimum_required (VERSION 3.10)
project (CacheArt)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-march=native -O3 -Wall -Wextra")

add_executable(CacheArt main.cpp Utils.cpp)