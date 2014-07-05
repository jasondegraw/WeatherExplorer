cmake_minimum_required(VERSION 2.8.11)

project(WeatherExplorer)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

add_subdirectory(qdecnumber)
add_subdirectory(src)
