cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(lib_utilities)

add_library(
    ${PROJECT_NAME} 
    include/${PROJECT_NAME}/in_stream.h)

target_include_directories(${PROJECT_NAME} PRIVATE include)
