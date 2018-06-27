cmake_minimum_required(VERSION 3.2)

project(algorithms)

# Set up directories
include_directories(include)

file(GLOB LIB_SOURCES src/*.c)
file(GLOB PROGRAMS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} programs/*.c)
file(GLOB TESTS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.c)

# Compile flags
if(CMAKE_COMPILER_IS_GNUCC)
    # Standard flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L")
    # Warning flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Waggregate-return")
endif()

# Build the library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
add_library(algorithms STATIC ${LIB_SOURCES})

# The executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the tests
foreach(TEST_SOURCE ${TESTS_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} algorithms)
endforeach()

# Build the programs
foreach(PROGRAM_SOURCE ${PROGRAMS_SOURCES})
    get_filename_component(PROGRAM_NAME ${PROGRAM_SOURCE} NAME_WE)
    add_executable(${PROGRAM_NAME} ${PROGRAM_SOURCE})
    target_link_libraries(${PROGRAM_NAME} algorithms)
endforeach()
