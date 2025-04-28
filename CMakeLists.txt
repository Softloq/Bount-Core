cmake_minimum_required(VERSION 4.0.1)
project(Bount-Core-Project LANGUAGES CXX)

option(BUILD_BOUNT_CORE_EXAMPLES "BUILD BOUNT CORE EXAMPLES" OFF)
option(BUILD_BOUNT_EXAMPLES "BUILD ALL BOUNT EXAMPLES" OFF)

include("${CMAKE_CURRENT_LIST_DIR}/.cmake/config.cmake")

load_env_cmake()

update_bount_git_module(svg++ master)

load_github_binaries(Boost 1.87.0)

if(NOT TARGET Bount-Core-Library)
    project(Bount-Core-Library)

    create_bount_library_vars(BOUNT_CORE)
    add_library(Bount-Core SHARED)
    target_sources(Bount-Core
    PRIVATE
        ${BOUNT_CORE_CXX_SRC}
        ${BOUNT_CORE_CXX_MODULE_SRC}
    PUBLIC
        FILE_SET bount_core_cxx_headers TYPE HEADERS
        BASE_DIRS ${BOUNT_CORE_CXX_INCLUDE_DIR}
        FILES ${BOUNT_CORE_CXX_HEADER_FILES}
    PUBLIC
        FILE_SET bount_core_cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${BOUNT_CORE_CXX_MODULE_DIR}
        FILES ${BOUNT_CORE_CXX_MODULE_FILES}
    )
    target_precompile_headers(Bount-Core PRIVATE "${BOUNT_CORE_CXX_INCLUDE_DIR}/Bount/Core/Precompiled.hpp")
    target_compile_options(Bount-Core
        PRIVATE
            $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-return-stack-address>
            $<$<CXX_COMPILER_ID:MSVC>:/wd4172 /wd4101>
    )
    target_include_directories(Bount-Core
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.module/svg++/include"
            "${CMAKE_CURRENT_LIST_DIR}/.module/svg++/third_party")
    target_link_libraries(Bount-Core PUBLIC boost::all)
    target_boost_link_libraries(Bount-Core boost_filesystem)
    set_bount_library_api_macros(Bount-Core BOUNT_CORE)
    set_bount_library_common_properties(Bount-Core)
    add_library(Bount::Core ALIAS Bount-Core)
    copy_bount_resources(Bount-Core-Resources Bount-Core)
endif()

if((BUILD_BOUNT_CORE_EXAMPLES OR BUILD_BOUNT_EXAMPLES) AND (NOT TARGET Bount-Core-Examples))
    project(Bount-Core-Examples)

    list(APPEND BOUNT_CORE_EXAMPLES Singleton Subsystem)
    foreach(example ${BOUNT_CORE_EXAMPLES})
        file(GLOB_RECURSE BOUNT_CORE_EXAMPLE_${example}_SRC
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cc"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cxx"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.c++"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cpp"
        )
        add_executable(Bount-Core-Example-${example} ${BOUNT_CORE_EXAMPLE_${example}_SRC})
        target_include_directories(Bount-Core-Example-${example} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/include")
        target_link_libraries(Bount-Core-Example-${example} PRIVATE Bount::Core)
        set_bount_example_common_properties(Bount-Core-Example-${example} ${example})
    endforeach()
endif()