cmake_minimum_required(VERSION 3.28)

project(TicTacToeSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_executable(SfmlTest
    sfml_test.cpp
)

target_link_libraries(SfmlTest PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_compile_features(SfmlTest PRIVATE cxx_std_17)