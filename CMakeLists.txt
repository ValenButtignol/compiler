cmake_minimum_required(VERSION 3.10)

project(Compiler)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Compiler_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Compiler_SOURCE_DIR}/lib)
set(test_dir ${Compiler_SOURCE_DIR}/tests)

#add_executable(Compiler apps/)
#add_library(..)
#target_link_libraries(...)

#enable_testing()
#add_test(...)