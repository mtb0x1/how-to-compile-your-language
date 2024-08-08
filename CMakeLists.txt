cmake_minimum_required(VERSION 3.2)

project(how-to-compile-your-language)

find_package(LLVM REQUIRED CONFIG)

if (NOT LLVM_FOUND)
    message(FATAL_ERROR "LLVM not found!")
else()
    message(STATUS "LLVM found: ${LLVM_DIR}")
    message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
    message(STATUS "LLVM_DEFINITIONS: ${LLVM_DEFINITIONS}")
endif()

include_directories(include "${LLVM_INCLUDE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(COVERAGE_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage -fno-exceptions")
SET(CMAKE_CXX_FLAGS_COVERAGE "${COVERAGE_FLAGS}")
SET(CMAKE_C_FLAGS_COVERAGE "${COVERAGE_FLAGS}")

add_definitions(${LLVM_DEFINITIONS})
add_definitions(-DLLVM_ENABLE_DUMP) # Ensure dump is enabled

add_subdirectory(src)
add_subdirectory(test)