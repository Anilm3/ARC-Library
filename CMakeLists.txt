cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME "ARCLib")

set (CMAKE_VERBOSE_MAKEFILE OFF)

option(STATIC "Build static library" OFF)
option(SHARED "Build shared library" ON)

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set (EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set (LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

include_directories ("${INCLUDES_DIR}")

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

if (SHARED)
    add_library(arc-shared SHARED ${SOURCES})
    set_target_properties(arc-shared PROPERTIES
        OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
endif()

if (STATIC)
    add_library(arc-static STATIC ${SOURCES})
    set_target_properties(arc-static PROPERTIES
       OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
endif()


file(GLOB_RECURSE TESTS ${TEST_DIR}/*.c)

foreach(TEST ${TESTS}) 
    get_filename_component(TEST_EXEC ${TEST} NAME_WE)
    add_executable(${TEST_EXEC} ${TEST})
    target_link_libraries(${TEST_EXEC} arc-shared)
endforeach(TEST) 
