cmake_minimum_required(VERSION 3.15)
project(techniki_programowania3 VERSION 1.0)
include(FetchContent)

# Configure Matplot++ before fetching
set(MATPLOT_BUILD_EXAMPLES OFF CACHE BOOL "")
set(MATPLOT_BUILD_TESTS OFF CACHE BOOL "")
set(MATPLOTPP_BACKEND "gnuplot" CACHE STRING "")
set(MATPLOT_GNUPLOT_TERM "png" CACHE STRING "")
set(MATPLOT_GNUPLOT_INTERACTIVE OFF CACHE BOOL "")
set(MATPLOT_GNUPLOT_COMMANDLINE_FLAGS "-e" CACHE STRING "")  # Add this line
set(MATPLOT_GNUPLOT_PIPE OFF CACHE BOOL "")                  # Add this line

# Find Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/lib)



FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    GIT_TAG master
)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG master
)

FetchContent_MakeAvailable(matplotplusplus pybind11)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create Python module
pybind11_add_module(example 
    src/main.cpp
    src/generator.cpp
    src/plot.cpp
)

# Link libraries
target_link_libraries(example 
    PRIVATE
        Matplot++::matplot
        Python3::Python
)

# Include directories
#target_include_directories(example 
    #PRIVATE 
        #${PROJECT_SOURCE_DIR}/include
        #${Python3_INCLUDE_DIRS}
        #${PROJECT_SOURCE_DIR}/lib/matplotplusplus/include
        #${PROJECT_SOURCE_DIR}/lib/pybind11/include
#)

# Set output directory for the compiled module
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# Add compiler warnings
if(MSVC)
    target_compile_options(example PRIVATE /W4)
else()
    target_compile_options(example PRIVATE -Wall -Wextra)
endif()