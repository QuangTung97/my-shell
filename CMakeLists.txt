cmake_minimum_required(VERSION 3.0)
project(shell)

include_directories(include)

add_definitions("-std=c++14")

add_executable(shell "")

add_subdirectory(src)

target_link_libraries(shell src)

