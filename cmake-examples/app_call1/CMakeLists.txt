cmake_minimum_required(VERSION 2.8)

project(myapp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myapp app.cpp)


target_link_libraries(myapp ${CMAKE_CURRENT_SOURCE_DIR}/liblate.so)

install(TARGETS myapp DESTINATION bin)


