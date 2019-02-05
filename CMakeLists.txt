cmake_minimum_required(VERSION 3.12)
project(reppo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(REPPO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(REPPO_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(REPPO_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected (see CMAKE_BUILD_TYPE). Default Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${REPPO_INCLUDE_DIR})

add_subdirectory(tool)
