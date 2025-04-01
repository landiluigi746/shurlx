cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(shurlx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include(FetchContent)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG master
)

FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG master
)

FetchContent_Declare(
    ada
    GIT_REPOSITORY https://github.com/ada-url/ada.git
    GIT_TAG main
)

FetchContent_MakeAvailable(httplib)
FetchContent_MakeAvailable(sqlite_orm)
FetchContent_MakeAvailable(ada)

add_subdirectory(src)
