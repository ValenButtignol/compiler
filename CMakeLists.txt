cmake_minimum_required(VERSION 3.12)
project(Compiler)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Set the output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include directories for header files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/utils/include
)

# Add source files for your project
file(GLOB SOURCES src/*.c)

# Create a library for your data structures
add_library(ast ${SOURCES})
add_library(nodeInfo ${SOURCES})
add_library(symbolTable ${SOURCES})

# Create a custom target for running the script
add_custom_target(run_language
    COMMAND ${CMAKE_SOURCE_DIR}/output/output.out ${CMAKE_SOURCE_DIR}/input/input.txt
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "\n\n----------------------------- Running the compiler -----------------------------\n\n"
)

# Define a custom target for generating lex and yacc output files
add_custom_target(generate_parser
    COMMAND flex lexicon.l
    COMMAND bison -d syntax.y
    COMMAND gcc lex.yy.c syntax.tab.c ${CMAKE_SOURCE_DIR}/src/*.c -o ${CMAKE_SOURCE_DIR}/output/output.out
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern
    COMMENT "\n\n--------------------- Generating lex and yacc output files ---------------------\n\n"
)

# Set the output directory for a.out
set_target_properties(generate_parser PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# Make "run_language" depend on "generate_parser"
add_dependencies(run_language generate_parser)







# Create an executable for your tests
add_executable(tests ${CMAKE_SOURCE_DIR}/tests/runTests.c)

file(GLOB TESTS_SOURCES tests/*.c)
file(GLOB TESTS_UTILS_SOURCES tests/utils/src/*.c)

# Add dependencies for your tests (testCheckType.c, testSymbolTable.c, and utils)
target_sources(tests PRIVATE
    ${TESTS_SOURCES}
    ${TESTS_UTILS_SOURCES}
)

# Link the required libraries to your tests executable
target_link_libraries(tests ast nodeInfo symbolTable)

# Create a custom target for running the tests
add_custom_target(run_tests
    COMMAND ./tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "\n\n----------------------------- Running the tests -----------------------------\n\n"
)

# Make "run_tests" depend on "tests" and "main_project"
add_dependencies(run_tests tests)