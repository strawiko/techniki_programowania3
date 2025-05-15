cmake_minimum_required(VERSION 3.15)
project(techniki_programowania3 VERSION 1.0)

# Pobierz Matplot++ jeśli nie masz vcpkg
include(FetchContent)
FetchContent_Declare(matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
    GIT_TAG origin/master
)
FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_MakeAvailable(matplotplusplus)
endif()

# Znajdź Python i pybind11 (pip)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
find_package(pybind11 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pybind11_add_module(example src/main.cpp)

target_link_libraries(example 
    PRIVATE
        Matplot++::matplot
        Python3::Python
)

target_include_directories(example 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${Python3_INCLUDE_DIRS}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(MSVC)
    target_compile_options(example PRIVATE /W4)
else()
    target_compile_options(example PRIVATE -Wall -Wextra)
endif()