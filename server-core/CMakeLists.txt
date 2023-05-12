# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.8)
project(server-core C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system)  # thread regex

set(used_libs ${Boost_SYSTEM_LIBRARY})  # ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY}

file(GLOB SOURCES src/*.cpp)
add_executable(server-core ${SOURCES})

target_link_libraries(server-core ${used_libs})
