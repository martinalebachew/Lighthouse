# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.8)
project(server-core C CXX)

add_executable(server-core "src/server-core.cpp")
set_target_properties(server-core
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

find_package(Boost REQUIRED)
target_link_libraries(server-core Boost)