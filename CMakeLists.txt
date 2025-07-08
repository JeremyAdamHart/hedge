cmake_minimum_required(VERSION 3.22)

project(hedge_proj VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD, 11)

message("Cmake standard ${CMAKE_CXX_STANDARD}")

add_library(hedge INTERFACE include/hedge.hpp)


add_library(hedge::hedge ALIAS hedge)
# find_package(range-v3 REQUIRED)
# target_link_libraries(hedge PUBLIC range-v3::range-v3)

target_sources(hedge PUBLIC FILE_SET hedge_headers TYPE HEADERS BASE_DIRS ./include/ FILES ./include/hedge.hpp)

target_include_directories(hedge INTERFACE ./include/)

add_executable(hedge_exe main.cpp)

target_link_libraries(hedge_exe PUBLIC hedge::hedge)


