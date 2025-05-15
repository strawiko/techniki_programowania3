cmake_minimum_required(VERSION 3.15)
project(techniki_programowania3 VERSION 1.0)

include(FetchContent)

# Try to find Matplot++ locally first
find_package(Matplot++ QUIET)
if(NOT Matplot++_FOUND)
    message(STATUS "Matplot++ not found locally, fetching from repository...")
    FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master
    )
    FetchContent_MakeAvailable(matplotplusplus)
endif()

# Try to find Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Try to find pybind11 locally first
find_package(pybind11 CONFIG QUIET)
if(NOT pybind11_FOUND)
    message(STATUS "pybind11 not found locally, fetching from repository...")
    FetchContent_Declare(pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v2.11.1
    )
    FetchContent_MakeAvailable(pybind11)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create Python module
pybind11_add_module(example src/main.cpp)

# Link libraries
target_link_libraries(example 
    PRIVATE
        Matplot++::matplot
        Python3::Python
)

# Include directories
target_include_directories(example 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${Python3_INCLUDE_DIRS}
)

# Set output directory for the compiled module
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add compiler warnings
if(MSVC)
    target_compile_options(example PRIVATE /W4)
else()
    target_compile_options(example PRIVATE -Wall -Wextra)
endif()