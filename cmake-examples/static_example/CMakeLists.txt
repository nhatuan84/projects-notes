cmake_minimum_required(VERSION 2.8)

project(libhello_project)

add_library(hello STATIC hello.cpp)

install(TARGETS hello DESTINATION lib)
install(FILES hello.h DESTINATION include)