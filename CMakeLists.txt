cmake_minimum_required(VERSION 3.21)
option(AOC24_BUILD_TESTS "Build Tests" OFF)
option(AOC24_BUILD_SOLUTIONS "Build Solutions" ON)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AOC24_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(AdventOfCode24 VERSION 0.1.0 LANGUAGES CXX)
file(GLOB AOC24_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx )
add_library(${PROJECT_NAME} ${AOC24_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${AOC24_HEADERS}>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/include)

if(AOC24_BUILD_SOLUTIONS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/solutions)
endif()

if(AOC24_BUILD_TESTS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

