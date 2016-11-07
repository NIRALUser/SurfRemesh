project(SurfRemesh)
cmake_minimum_required(VERSION 2.8)

find_package(SlicerExecutionModel REQUIRED)
find_package(MeshLib REQUIRED)

#include_directories(/System/Library/Frameworks/Accelerate.framework/Headers)
#include_directories(Mesh)
include(${CMAKE_CURRENT_SOURCE_DIR}/Common.cmake)
include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} )
include(${SlicerExecutionModel_USE_FILE})
#include(${GenerateCLP_USE_FILE})
#include_directories(/System/Library/Frameworks/Accelerate.framework/Headers)

include_directories(src)
add_subdirectory(src)
add_subdirectory(wrapper)