# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.8)
project(lighthouse-core C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system)

add_executable(core src/core.cpp)
target_sources(core PRIVATE src/rpc/control.cpp)
target_link_libraries(core ${Boost_SYSTEM_LIBRARY})
