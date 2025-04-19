cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Development" "Release" "RelWithDebInfo" "MinSizeRel")
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} UPPER_config)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/lib")
endforeach()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
endif()

if(NOT TARGET Bount::Core)
    project(Bount-Core)

    # Extensions
    set(BOOST_VERSION 1.87.0)
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}.zip")
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            file(DOWNLOAD "https://github.com/Softloq/Boost-Binaries/releases/download/v${BOOST_VERSION}/boost-linux-clang.zip" "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}.zip" SHOW_PROGRESS)
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            file(DOWNLOAD "https://github.com/Softloq/Boost-Binaries/releases/download/v${BOOST_VERSION}/boost-win64-msvc.zip" "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}.zip" SHOW_PROGRESS)
        endif()
    endif()
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}.zip" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/external/boost-${BOOST_VERSION}/boost/config.cmake")
    cmake_policy(SET CMP0144 NEW)
    find_package(Boost REQUIRED)

    # Options
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(Bount_Core_COMPILE_OPTIONS -Wno-return-stack-address)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND Bount_Core_COMPILE_OPTIONS /wd4172 /wd4101)
    endif()

    # Includes
    set(Bount_Core_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include" ${Boost_INCLUDE_DIRS} "${CMAKE_CURRENT_LIST_DIR}/svg++/include" "${CMAKE_CURRENT_LIST_DIR}/svg++/third_party")

    # Sources
    file(GLOB_RECURSE Bount_Core_SRC
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cc")

    # Building
    add_library(Bount-Core SHARED ${Bount_Core_SRC})
    set_target_properties(Bount-Core PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
    target_compile_definitions(Bount-Core PRIVATE BOUNT_CORE_BUILD_API)
    target_compile_definitions(Bount-Core PUBLIC BOUNT_CORE_USE_API)
    target_include_directories(Bount-Core PUBLIC ${Bount_Core_INCLUDE_DIRS})
    target_compile_options(Bount-Core PRIVATE ${Bount_Core_COMPILE_OPTIONS})
    target_link_libraries(Bount-Core PUBLIC boost::all)
    target_precompile_headers(Bount-Core PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/Bount/Core/Precompiled.hpp")
    add_library(Bount::Core ALIAS Bount-Core)
endif()
