cmake_minimum_required(VERSION 3.21)
option(AOC24_BUILD_TESTS "Build Tests" OFF)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

project(AdventOfCode24 VERSION 0.1.0 LANGUAGES CXX)
add_library(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

if(AOC24_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  set(TEST_PROJECT ${PROJECT_NAME}_Test)
  find_package(GTest REQUIRED)
  enable_testing()
  file(GLOB AOC24_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_*.cxx)
  add_executable(${TEST_PROJECT} ${AOC24_TEST_SOURCES})
  target_link_libraries(${TEST_PROJECT} GTest::gtest_main)
  target_link_libraries(${TEST_PROJECT} ${PROJECT_NAME})
  target_include_directories(${TEST_PROJECT} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
  target_compile_definitions(${TEST_PROJECT} PRIVATE ADVENT_OF_CODE_DATA="${CMAKE_CURRENT_SOURCE_DIR}/tests/data")
  include(GoogleTest)
  gtest_discover_tests(${TEST_PROJECT})
endif()

