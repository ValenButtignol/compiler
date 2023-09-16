cmake_minimum_required(VERSION 3.12)
project(Compiler)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)

# Set the output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include directories for header files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/utils/include
)

# Link "SOURCES" name to every .c file in the src directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

# Create a custom target command for generating lex and yacc output files
add_custom_target(generate_parser
    COMMAND flex lexicon.l
    COMMAND bison -d syntax.y
    COMMAND gcc ../main.c lex.yy.c syntax.tab.c ${SOURCES} -o ../output/output.out
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern
    COMMENT "\n\n--------------------- Generating lex and yacc output files ---------------------\n\n"
)

# Create a custom target command for running the compiler
add_custom_target(run_language
    COMMAND ${CMAKE_SOURCE_DIR}/output/output.out ${CMAKE_SOURCE_DIR}/input/input.txt
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "\n\n----------------------------- Running the compiler -----------------------------\n\n"
)
# Make "run_language" depend on "generate_parser"
add_dependencies(run_language generate_parser)


# Link names to every .c in the determined directories
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.c)
file(GLOB TEST_UTILS_SOURCES ${CMAKE_SOURCE_DIR}/tests/utils/src/*.c)


# Create a custom target command for running the compiler
add_custom_target(run_tests
    COMMENT "\n\n----------------------------- Running the compiler for testing -----------------------------\n\n"
)

# Create a custom target command for generating lex and yacc output files
add_custom_target(generate_parser_for_testing
    COMMAND flex lexicon.l
    COMMAND bison -d syntax.y
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/extern
    COMMAND gcc ../testRunner.c lex.yy.c syntax.tab.c ${SOURCES} ${TEST_SOURCES} ${TEST_UTILS_SOURCES} -o ../output/output.out
    COMMENT "\n\n--------------------- Generating lex and yacc output files for testing ---------------------\n\n"
)

# Make "run_language" depend on "generate_parser"
add_dependencies(run_tests generate_parser_for_testing)

# Set the directory where the input files for testing are located
set(TEST_INPUT_DIR ${CMAKE_SOURCE_DIR}/tests/inputs)

# Set names to every .txt file in the input directory
file(GLOB TEST_INPUT_FILES ${TEST_INPUT_DIR}/*.txt)

# Make a custom target command for every testing input file
foreach(TEST_INPUT_FILE ${TEST_INPUT_FILES})
    get_filename_component(TEST_NAME ${TEST_INPUT_FILE} NAME_WE)  # Get the name of the input file without .txt
    add_custom_target(${TEST_NAME}
        COMMAND ${CMAKE_SOURCE_DIR}/output/output.out ${TEST_INPUT_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running test: ${TEST_NAME}\n"
    )
    add_dependencies(run_tests ${TEST_NAME})
endforeach()
