cmake_minimum_required(VERSION 3.8)
project(lighthouse-desktop C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

set(SDK_ROOT "${CMAKE_BINARY_DIR}/SDK/")
set(ULTRALIGHT_INCLUDE_DIR "${SDK_ROOT}/include")
set(ULTRALIGHT_BINARY_DIR "${SDK_ROOT}/bin")
set(ULTRALIGHT_RESOURCES_DIR "${SDK_ROOT}/resources")
set(ULTRALIGHT_INSPECTOR_DIR "${SDK_ROOT}/inspector")
set(ULTRALIGHT_LIBRARY_DIR "${SDK_ROOT}/lib")

set(VERSION "1.3.0")
set(PLATFORM "win")
set(ARCHITECTURE "x64")

set(SDK_BASE_URL "github.com/ultralight-ux/Ultralight/releases/download")
ExternalProject_Add(UltralightSDK
  URL https://${SDK_BASE_URL}/v${VERSION}/ultralight-sdk-${VERSION}-${PLATFORM}-${ARCHITECTURE}.7z
  DOWNLOAD_EXTRACT_TIMESTAMP true
  SOURCE_DIR "${SDK_ROOT}"
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

file(GLOB SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)
set(APP_NAME ${CMAKE_PROJECT_NAME})

include_directories("${ULTRALIGHT_INCLUDE_DIR}")
link_directories("${ULTRALIGHT_LIBRARY_DIR}")
link_libraries(UltralightCore AppCore Ultralight WebCore)

add_executable(${APP_NAME} WIN32 ${SOURCES})

# Tell MSVC to use main instead of WinMain for Windows subsystem executables
set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")

# Copy all binaries to target directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_BINARY_DIR}" $<TARGET_FILE_DIR:${APP_NAME}>)

# Copy assets to assets path
set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets")
add_custom_command(TARGET ${APP_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/webapp/build/" "${ASSETS_PATH}")

# Copy inspector to assets directory
if(${ENABLE_INSPECTOR})
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_INSPECTOR_DIR}" "${ASSETS_PATH}/inspector")
endif ()

# Copy resources to assets directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_RESOURCES_DIR}" "${ASSETS_PATH}/resources")

add_dependencies(${APP_NAME} UltralightSDK)
