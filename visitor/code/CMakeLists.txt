cmake_minimum_required(VERSION 3.16)

project(visitor_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(VISITOR_BUILD_EXAMPLES "Build example programs" ON)
option(VISITOR_BUILD_TESTS "Build tests (reserved, no framework yet)" OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)

if(VISITOR_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(VISITOR_BUILD_TESTS)
  add_subdirectory(tests)
endif()
