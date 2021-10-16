cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(lib_utilities)

set(
    PUBLIC_HEADERS
    include/${PROJECT_NAME}/badge.h
    include/${PROJECT_NAME}/in_stream.h)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME})
