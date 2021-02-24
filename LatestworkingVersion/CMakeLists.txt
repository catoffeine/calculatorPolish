cmake_minimum_required(VERSION 3.11)

if (NOT CMAKE_BUILD_TYPE STREQUAL RELEASE)
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

include(FetchContent)

set(build_static_lib TRUE)

FetchContent_Declare(
    easylogging
    GIT_REPOSITORY https://github.com/amrayn/easyloggingpp.git
    GIT_TAG v9.97.0
    )
FetchContent_GetProperties(easylogging)
if(NOT easylogging_POPULATED)
    FetchContent_Populate(easylogging)
    add_subdirectory(${easylogging_SOURCE_DIR} ${easylogging_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(prog_012)

set(SOURCE_main ${CMAKE_SOURCE_DIR}/src/main.cpp)
set(SOURCE_calc ${CMAKE_SOURCE_DIR}/src/calc.cpp)
set(SOURCE_list ${CMAKE_SOURCE_DIR}/src/list.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_main} ${SOURCE_calc} ${SOURCE_list})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC easyloggingpp)
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${easylogging_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)
