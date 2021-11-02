cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(libutilities)

add_library(
    ${PROJECT_NAME}
    include/${PROJECT_NAME}/badge.h
    include/${PROJECT_NAME}/concepts.h
    include/${PROJECT_NAME}/in_stream.h
    include/${PROJECT_NAME}/non_null.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC include)