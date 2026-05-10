cmake_minimum_required(VERSION 3.20)

project(lab9_stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab9
    src/main.cpp
)

# Помірні попередження (працює для MSVC та GCC/Clang)
if (MSVC)
    target_compile_options(lab9 PRIVATE /W4 /permissive-)
else()
    target_compile_options(lab9 PRIVATE -Wall -Wextra -Wpedantic)
endif()