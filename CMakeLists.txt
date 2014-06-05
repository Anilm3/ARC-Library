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

# set(CMAKE_BUILD_TYPE Release)

# -g: debugging information
set(CMAKE_C_FLAGS "-g")

# -Wextra, -Wall: essential.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall")

# -Wfloat-equal: useful because usually testing floating-point 
#                numbers for equality is bad.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-equal")

# -Wundef: warn if an uninitialized identifier is evaluated in an #if directive.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wundef")

# -Wshadow: warn whenever a local variable shadows another local 
#           variable, parameter or global variable or whenever a 
#           built-in function is shadowed.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")

# -Wpointer-arith: warn if anything depends upon the size of a 
#                  function or of void.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith")

# -Wcast-align: warn whenever a pointer is cast such that the required 
#               alignment of the target is increased. For example, warn 
#               if a char * is cast to an int * on machines where integers 
#               can only be accessed at two- or four-byte boundaries.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align")


# -Wstrict-prototypes: warn if a function is declared or defined without 
#                      specifying the argument types.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-prototypes")


# -Wstrict-overflow=5: warns about cases where the compiler optimizes based on 
#                      the assumption that signed overflow does not occur. 
#                      (The value 5 may be too strict, see the manual page.)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-overflow=5")


# -Wwrite-strings: give string constants the type const char[length] so that 
#                  copying the address of one into a non-const char * pointer
#                  will get a warning.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wwrite-strings")


# -Waggregate-return: warn if any functions that return structures or unions 
#                     are defined or called.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Waggregate-return")

# -Wcast-qual: warn whenever a pointer is cast to remove a type qualifier from 
#              the target type*.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-qual")

# -Wswitch-default: warn whenever a switch statement does not have a default 
#                   case*.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-default")

# -Wswitch-enum: warn whenever a switch statement has an index of enumerated 
#                type and lacks a case for one or more of the named codes 
#                of that enumeration*.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-enum")

# -Wconversion: warn for implicit conversions that may alter a value*.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion")

# -Wunreachable-code: warn if the compiler detects that code will 
#                     never be executed*.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunreachable-code")

# Those marked * sometimes give too many spurious warnings, so I use them 
# on as-needed basis:
# http://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c


# set(CMAKE_EXE_LINKER_FLAGS "-s")

if (SHARED)
    add_library(arc-shared SHARED ${SOURCES})
    set_target_properties(arc-shared PROPERTIES
        OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
endif()

# set(CMAKE_C_FLAGS "-O3")
# set(CMAKE_EXE_LINKER_FLAGS "-s")

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
