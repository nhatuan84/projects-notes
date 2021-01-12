cmake_minimum_required(VERSION 2.8)

project(libtest_project)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(late SHARED test.cpp)


target_link_libraries(late ${CMAKE_CURRENT_SOURCE_DIR}/libtest.so ${CMAKE_CURRENT_SOURCE_DIR}/libhello.so)