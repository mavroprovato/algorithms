cmake_minimum_required(VERSION 3.5)

project(algorithms)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_library(algorithms STATIC ${SOURCES})
