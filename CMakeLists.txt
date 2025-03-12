cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Bount-Core)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
endif()

set(Bount_Core_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

file(GLOB_RECURSE Bount_Core_SRC "${CMAKE_CURRENT_LIST_DIR}/src/**.cpp")
add_library(Bount-Core SHARED ${Bount_Core_SRC})
add_library(Bount::Core ALIAS Bount-Core)
target_include_directories(Bount-Core PUBLIC ${Bount_Core_INCLUDE_DIRS})