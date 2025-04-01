file(GLOB_RECURSE SHURLX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SHURLX_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_executable(shurlx ${SHURLX_SOURCES} ${SHURLX_HEADERS})

target_include_directories(shurlx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(
    shurlx
    PRIVATE httplib::httplib
    PRIVATE sqlite_orm::sqlite_orm
    PRIVATE ada::ada
)

set(OPTIONS_WARNINGS -Wall -Wpedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPTIONS_OPTIMIZATION -O2)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIONS_OPTIMIZATION -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(OPTIONS_OPTIMIZATION -O2 -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(OPTIONS_OPTIMIZATION -Os)
endif()

message(STATUS "Compiler options: ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION}")

target_compile_options(shurlx PRIVATE ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION})

if(DEFINED ENV{MAX_URL_TIME})
    target_compile_definitions(shurlx PRIVATE MAX_URL_TIME=ENV{MAX_URL_TIME})
endif()

if(DEFINED ENV{MAX_RAND_LEN_STR})
    target_compile_definitions(shurlx PRIVATE MAX_RAND_LEN_STR=ENV{MAX_RAND_LEN_STR})
endif()

if(DEFINED ENV{ORIGIN})
    target_compile_definitions(shurlx PRIVATE ORIGIN=ENV{ORIGIN})
endif()
