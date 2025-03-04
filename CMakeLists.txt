cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Bount-Core)

file(GLOB_RECURSE Bount_Core_SRC src/**.cpp)
add_library(Bount-Core SHARED ${Bount_Core_SRC})
add_library(Bount::Core ALIAS Bount-Core)
target_include_directories(Bount-Core PRIVATE include)