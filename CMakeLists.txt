cmake_minimum_required(VERSION 3.1)
project(IbmFlu)

set(CMAKE_CXX_STANDARD 17)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

if (WIN32)
  add_subdirectory(${EXT_PROJECTS_DIR}/yaml-cpp)
  add_subdirectory(${EXT_PROJECTS_DIR}/gsl)
else ()
  find_package(GSL REQUIRED)
  find_package(yaml-cpp REQUIRED)
endif ()
add_subdirectory("src")