# CMakeLists.txt


########################################################################
# Setup
########################################################################

cmake_minimum_required(VERSION 2.6)

project(cps)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -O3")
include_directories("include")


########################################################################
# Main executable (cps_main.out)
########################################################################

# Define main source which does not get included in the testing
set(SOURCE_MAIN
    source/main.cpp
)

# Define all sources which may get included in the testing
set(SOURCE_FILES
    source/Shape.cpp
    source/BasicShapes.cpp
    source/CompoundShapes.cpp
)

# Define sources and main executable
set(EXECUTABLE_NAME cps_main.out)
add_executable(${EXECUTABLE_NAME} ${SOURCE_MAIN} ${SOURCE_FILES})


########################################################################
# Alternate Main executable (alt_main.out)
########################################################################

# Define main source which does not get included in the testing
set(SOURCE_MAIN
    source/alt_main.cpp
)

# Define all sources which may get included in the testing
set(SOURCE_FILES
    source/Shape.cpp
    source/BasicShapes.cpp
    source/CompoundShapes.cpp
    source/TextParser.cpp
)

# Define sources and main executable
set(ALT_EXECUTABLE_NAME alt_main.out)
add_executable(${ALT_EXECUTABLE_NAME} ${SOURCE_MAIN} ${SOURCE_FILES})



########################################################################
# Testing executable (catch_tests.out)
########################################################################

if(EXISTS "${CMAKE_SOURCE_DIR}/include/catch.hpp")
    set(TEST_SOURCE_FILES
        tests/cps_test_main.cpp
        tests/cps_test_suites.cpp
        ${SOURCE_FILES}
    )

    # Define sources and executable
    set(TEST_EXECUTABLE_NAME catch_tests.out)
    add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES})

    enable_testing()
    add_test(NAME TheOneTrueTest COMMAND catch_tests.out)

else()
    message("Unable to create Testing Framework (include/catch.hpp does not exist)")
endif()
