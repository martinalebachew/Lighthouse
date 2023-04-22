# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.8)
project(server-core C CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system)  # thread regex

set(used_libs ${Boost_SYSTEM_LIBRARY})  # ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY}

add_executable(server-core "src/server-core.cpp")
target_link_libraries(server-core ${used_libs})