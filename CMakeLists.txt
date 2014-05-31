cmake_minimum_required (VERSION 2.8)

set (CMAKE_VERBOSE_MAKEFILE ON)

option(STATIC "Build static library" OFF)
option(SHARED "Build shared library" ON)

set (PROJECT_NAME "ARCLib")

# Source directory
set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# Include directory
set (INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
# Source directory
set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
# Binary directory
set (EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
# LIbrary directory
set (LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

# Add includes
include_directories ("${INCLUDES_DIR}")

# Create library
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

# include(${EXAMPLE_DIR}/CMakeLists.txt)

# add_library(arc-object OBJECTS ${SOURCES});
if (SHARED)
    add_library(arc-shared SHARED ${SOURCES})
    SET_TARGET_PROPERTIES(arc-shared PROPERTIES
        OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
endif()

if (STATIC)
    add_library(arc-static STATIC ${SOURCES})
    SET_TARGET_PROPERTIES(arc-static PROPERTIES
       OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
endif()


file(GLOB_RECURSE TESTS ${TEST_DIR}/*.c)

foreach(TEST ${TESTS}) 
    GET_FILENAME_COMPONENT(TEST_EXEC ${TEST} NAME_WE)
    add_executable(${TEST_EXEC} ${TEST})
    TARGET_LINK_LIBRARIES(${TEST_EXEC} arc-shared)
    message(${TEST_EXEC}) 
endforeach(TEST) 
# set(LINK_LIBS StateChart cppunit gcov)

# ENABLE_TESTING()

# if (EXAMPLES)
# endif(EXAMPLES)

# if (OSH_EXAMPLES)
#  include(${OSH_DIR}/CMakeLists.txt)
# endif()

# if (SSRWIN_EXAMPLES)
#  include(${SSRWIN_DIR}/CMakeLists.txt)
# endif()

# if (UNIT_TEST)
 # include(${TEST_DIR}/CMakeLists.txt)
# endif(UNIT_TEST)
