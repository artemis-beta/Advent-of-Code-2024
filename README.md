# Advent of Code 2024
[![Advent of Code 2024](https://github.com/artemis-beta/Advent-of-Code-2024/actions/workflows/build_test.yaml/badge.svg)](https://github.com/artemis-beta/Advent-of-Code-2024/actions/workflows/build_test.yaml)

This repository contains solutions to the challenges set as part of the [Advent of Code 2024](https://adventofcode.com/2024).
The solutions have been created in the C++ programming language as a library.

| | ||||||
|-|-|-|-|-|-|-|
||1|2|3|4|5|6|
||:x: |:x:|:x:|| | |
|7|8|9|10|11|12|13|
| | | | | | | | |
|14|15|16|17|18|19|20|
| | | | | | | |
|21|22|23|24|25| | |
| | | | | | | |

The code is written as an AdventOfCode24 library which is built using CMake, the code of which is found in `src/` with headers present in `include/`. Solutions to the problems
then use this library and are found in `solutions/`. The project is carried out using test driven development using the examples for each problem to create tests built using GTest and found in `tests/`.

## Building

Firstly clone this repository ensuring all sub-modules are cloned also:

```sh
git clone --recurse-submodules https://github.com/artemis-beta/Advent-of-Code-2024.git
```

You will need CMake, note also that the project assumes C++23 is available:

```sh
cmake -Bbuild [-DAOC24_BUILD_TESTS=ON] [-DAOC24_BUILD_SOLUTIONS=ON]
cmake --build build
```

## Execute

Run the tests using the GTest executable:

```sh
./build/tests/AdventOfCode24_Test
```

Run the solutions from the relevant executable pointing to the applicable data file:

```sh
./build/solutions/day_1 ./solutions/data/day_1.txt
```
