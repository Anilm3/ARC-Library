cmake_minimum_required (VERSION 2.8)

set (CMAKE_PROJECT_NAME "ARC")
set (CMAKE_VERBOSE_MAKEFILE OFF)

option(STATIC "Build static library" OFF)
option(SHARED "Build shared library" ON)
option(ANSI "Compile with -ansi -pedantic" ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set (UNIT_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/unit_test")
set (PERF_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/perf_test")
set (DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/doc/")
set (EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set (LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

SET(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
SET(CPACK_PACKAGE_FILE_NAME "libarc")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Anil Mahtani")
SET(CPACK_SET_DESTDIR ON) 

include(CPack)

include_directories ("${INCLUDES_DIR}")
include_directories ("${SOURCE_DIR}")

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

if(NOT BUILD_TYPE)
    set(BUILD_TYPE Debug)
endif()

message("-- CMake build type: ${BUILD_TYPE}")


#-ansi, -pedantic : conform to ansi C
if(ANSI)
    set(CMAKE_C_FLAGS "-ansi -pedantic -D_POSIX_C_SOURCE=200112L")
else(ANSI)
    set(CMAKE_C_FLAGS "-D_POSIX_C_SOURCE=200112L")
endif()

if (BUILD_TYPE STREQUAL "Debug")
    
    # -g: debugging information.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftest-coverage")

    # -W, -Werror: , every warning is an error.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -W -Werror")

    # -Wextra, -Wall: essential.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall")

    # -Wfloat-equal: useful because usually testing floating-point 
    #                numbers for equality is bad.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-equal")

    # -Wundef: warn if an uninitialized identifier is evaluated in an 
    #          #if directive.
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


    # -Wstrict-overflow=5: warns about cases where the compiler optimizes based 
    #                      on the assumption that signed overflow does not occur
    #                      (The value 5 may be too strict, see the manual page).
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-overflow=5")


    # -Wwrite-strings: give string constants the type const char[length] so that 
    #                  copying the address of one into a non-const char * pointer
    #                  will get a warning.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wwrite-strings")


    # -Waggregate-return: warn if any functions that return structures or unions 
    #                     are defined or called.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Waggregate-return")

    # -Wcast-qual: warn whenever a pointer is cast to remove a type qualifier  
    #              from the target type*.
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
   set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -g -pg -lgcov")
else()
    #-ansi, -pedantic : conform to ansi C
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG")
    #set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()

# add a target to generate API documentation with Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
                      ${DOXYGEN_EXECUTABLE} 
                      ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
                      COMMENT "Generating documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

install(DIRECTORY ${INCLUDES_DIR}/arc 
        DESTINATION /usr/local/include)

if (NOT SHARED AND NOT STATIC)
    message( FATAL_ERROR "No library being generated")
endif()

if (SHARED)
    add_library(arc-shared SHARED ${SOURCES})
    target_link_libraries(arc-shared rt)
    set_target_properties(arc-shared PROPERTIES
                          OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
    install(TARGETS arc-shared
            LIBRARY DESTINATION /usr/local/lib)
endif()

if (STATIC)
    add_library(arc-static STATIC ${SOURCES})
    set_target_properties(arc-static PROPERTIES
                          OUTPUT_NAME arc CLEAN_DIRECT_OUTPUT 1)
    target_link_libraries(arc-static rt)
    install(TARGETS arc-static
            ARCHIVE DESTINATION /usr/local/lib
            LIBRARY DESTINATION /usr/local/lib)
endif()

file(GLOB_RECURSE TESTS ${UNIT_TEST_DIR}/*.c)
enable_testing()

foreach(TEST ${TESTS}) 
    get_filename_component(TEST_EXEC ${TEST} NAME_WE)
    add_executable(${TEST_EXEC} ${TEST})

    if (SHARED)
        target_link_libraries(${TEST_EXEC} arc-shared)
    else (SHARED)
        target_link_libraries(${TEST_EXEC} arc-static)
    endif()

    add_test(${TEST_EXEC} ${EXECUTABLE_OUTPUT_PATH}/${TEST_EXEC})
endforeach(TEST) 


if (BUILD_TYPE STREQUAL "Debug")
    find_program( GCOV_PATH gcov )
    find_program( LCOV_PATH lcov )
    find_program( GENHTML_PATH genhtml )
    find_program( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)

    if(GCOV_PATH AND LCOV_PATH AND GENHTML_PATH)
        set (COVERAGE_NAME coverage)

        add_custom_target(coverage
            # Capturing lcov counters and generating report
            COMMAND ${LCOV_PATH} --directory . --capture --output-file ${COVERAGE_NAME}.info
            COMMAND ${LCOV_PATH} --remove ${COVERAGE_NAME}.info 'tests/*' '/usr/*' --output-file ${COVERAGE_NAME}.info.cleaned
            COMMAND ${GENHTML_PATH} -o ${DOC_DIR}/${COVERAGE_NAME} ${COVERAGE_NAME}.info.cleaned --legend --show-details --demangle-cpp --num-spaces 3
            COMMAND ${CMAKE_COMMAND} -E remove ${COVERAGE_NAME}.info ${COVERAGE_NAME}.info.cleaned
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests.\nResetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
        )

        add_custom_command(TARGET coverage POST_BUILD
            COMMAND ${LCOV_PATH} --directory . --zerocounters
            COMMENT "Cleaning coverage data"
        )

        # Show info where to find the report
        add_custom_command(TARGET coverage POST_BUILD
            COMMAND ;
            COMMENT "Open ${DOC_DIR}/${COVERAGE_NAME}/index.html in your browser to view the coverage report."
        )
    endif() # 
endif()

file(GLOB_RECURSE TESTS ${PERF_TEST_DIR}/*.c ${PERF_TEST_DIR}/*.cpp)

foreach(TEST ${TESTS}) 
    get_filename_component(TEST_EXEC ${TEST} NAME_WE)
    add_executable(${TEST_EXEC} ${TEST})
    
    if (SHARED)
        target_link_libraries(${TEST_EXEC} arc-shared)
    else (SHARED)
        target_link_libraries(${TEST_EXEC} arc-static)
    endif()
endforeach(TEST) 

