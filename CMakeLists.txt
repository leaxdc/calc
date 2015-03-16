set(CO_CMAKE_MIN_VERSION 3.0.2)
  
cmake_minimum_required(VERSION ${CO_CMAKE_MIN_VERSION})

project (calc)

add_definitions(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

file(GLOB SOURCES
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})