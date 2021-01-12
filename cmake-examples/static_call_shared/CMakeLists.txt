cmake_minimum_required(VERSION 2.8)

project(libtest_project)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(test STATIC test.cpp)


target_link_libraries(test ${CMAKE_CURRENT_SOURCE_DIR}/libhello.so)