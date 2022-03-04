cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(four_guys_one_problem)

option(VERBOSE "Print execution information" OFF)
if (${VERBOSE})
    add_compile_definitions(VERBOSE)
endif()

# Compilation for the project, compiles to the file named 'mcp'
FILE(GLOB SOURCE src/*.cpp src/*.h)
FILE(COPY intpufiles/input_data/ DESTINATION input)
FILE(COPY solutions/ DESTINATION solution)

make_directory(output)
add_executable(hashcode ${SOURCE})
