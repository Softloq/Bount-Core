cmake_minimum_required(VERSION 3.10)
include("${CMAKE_CURRENT_LIST_DIR}/Utils.cmake")

option(BUILD_BOUNT_CORE_EXAMPLES "BUILD BOUNT CORE EXAMPLES" OFF)

# Load Environment Variables
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/.env.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/.env.cmake")
endif()

if(NOT TARGET Bount-Core-Library)
    project(Bount-Core-Library)

    # Load Required Libraries
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

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(BOUNT_CORE_PRIVATE_COMPILE_OPTIONS -Wno-return-stack-address)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND BOUNT_CORE_PRIVATE_COMPILE_OPTIONS /wd4172 /wd4101)
    endif()

    set(BOUNT_CORE_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/include" ${Boost_INCLUDE_DIRS} "${CMAKE_CURRENT_LIST_DIR}/svg++/include" "${CMAKE_CURRENT_LIST_DIR}/svg++/third_party")
    file(GLOB_RECURSE BOUNT_CORE_SRC
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cc")

    # Building
    add_library(Bount-Core SHARED ${BOUNT_CORE_SRC})
    set_target_properties(Bount-Core PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
    target_compile_definitions(Bount-Core PRIVATE BOUNT_CORE_BUILD_API)
    target_compile_definitions(Bount-Core PUBLIC BOUNT_CORE_USE_API)
    target_include_directories(Bount-Core PUBLIC ${BOUNT_CORE_INCLUDES})
    target_compile_options(Bount-Core PRIVATE ${BOUNT_CORE_PRIVATE_COMPILE_OPTIONS})
    target_link_libraries(Bount-Core PUBLIC boost::all)
    target_precompile_headers(Bount-Core PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/Bount/Core/Precompiled.hpp")
    add_library(Bount::Core ALIAS Bount-Core)
endif()

if(BUILD_BOUNT_CORE_EXAMPLES AND (NOT TARGET Bount-Core-Examples))
    project(Bount-Core-Examples)

    list(APPEND BOUNT_CORE_EXAMPLES DesignPatterns Subsystem)
    foreach(example ${BOUNT_CORE_EXAMPLES})
        file(GLOB_RECURSE BOUNT_CORE_EXAMPLE_${example}_SRC
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cpp"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cxx"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cc")
        add_executable(Bount-Core-Example-${example} ${BOUNT_CORE_EXAMPLE_${example}_SRC})
        set_target_properties(Bount-Core-Example-${example} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            OUTPUT_NAME "${example}")
        target_include_directories(Bount-Core-Example-${example} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/include")
        target_link_libraries(Bount-Core-Example-${example} PRIVATE Bount::Core)
    endforeach()

    list(GET BOUNT_CORE_EXAMPLES 0 SOME_BOUNT_CORE_EXAMPLE)
    add_custom_command(TARGET Bount-Core-Example-${SOME_BOUNT_CORE_EXAMPLE}
        POST_BUILD
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/__run_always"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_BINARY_DIR}/$<CONFIG>/bin" "${CMAKE_BINARY_DIR}/$<CONFIG>/examples")
endif()