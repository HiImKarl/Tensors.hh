cmake_minimum_required(VERSION 3.1)
project(Tensors LANGUAGES CXX)

include_directories(
    ${PROJECT_SOURCE_DIR}/external 
    ${PROJECT_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fmax-errors=4")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ferror-limit=4")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(benchmark QUIET)
find_package(X11 QUIET)
find_package(Threads QUIET)
find_package(OpenCL QUIET)

if (OpenCL_FOUND)
  include_directories(${OpenCL_INCLUDE_DIRS})
  link_directories(${OpenCL_LIBRARY})
endif()

if (benchmark_FOUND AND Threads_FOUND)
    add_subdirectory(${PROJECT_SOURCE_DIR}/benchmark/)
endif ()

if (X11_FOUND AND Threads_FOUND)
    add_subdirectory(${PROJECT_SOURCE_DIR}/example/)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)

