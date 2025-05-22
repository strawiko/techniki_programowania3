cmake_minimum_required(VERSION 3.15)
project(techniki_programowania3 VERSION 1.0)
include(FetchContent)
# Add subdirectories for local libraries
#add_subdirectory(lib/matplotplusplus)
#add_subdirectory(lib/pybind11)

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

FetchContent_MakeAvailable(matplotplusplus)

FetchContent_MakeAvailable(pybind11)
#FetchContent_GetProperties(matplotplusplus)
#if(NOT matplotplusplus_POPULATED)
 #   FetchContent_Populate(matplotplusplus)
  #  add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()
#FetchContent_GetProperties(pybind11)
#if(NOT pybind11_POPULATED)
 #   FetchContent_Populate(pybind11)
#    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

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