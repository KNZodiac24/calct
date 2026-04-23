cmake_minimum_required(VERSION 3.15)

project(calct VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ctre CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

target_link_libraries(${PROJECT_NAME} PRIVATE ctre::ctre)

target_include_directories(${PROJECT_NAME} PUBLIC include)
