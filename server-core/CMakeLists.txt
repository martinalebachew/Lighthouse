# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.8)
project(core C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

file(GLOB CORE_SOURCES src/core.cpp src/*/*.cpp src/*/*/*.cpp)
add_executable(core ${CORE_SOURCES})

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system)  # thread
target_link_libraries(core ${Boost_SYSTEM_LIBRARY})

target_precompile_headers(core PUBLIC src/core.hpp PRIVATE <iostream> <vector> <bit> <cstring> <cstdint> <iomanip> <cstdlib> <boost/asio.hpp>)
