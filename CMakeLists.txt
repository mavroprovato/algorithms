cmake_minimum_required(VERSION 3.5)

project(algorithms)

# Compile flags
include_directories("include")
file(GLOB LIB_SOURCES "src/*.c")
file(GLOB RELATIVE PROGRAMS_SOURCES "programs/*.c")
file(GLOB TEST_SOURCES "tests/*.c")

# Compile flags
if (CMAKE_COMPILER_IS_GNUCC)
    # Standard flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L")
    # Warning flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Waggregate-return")
endif()

# Build the library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")
add_library(algorithms STATIC ${LIB_SOURCES})
