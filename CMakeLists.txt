cmake_minimum_required(VERSION 3.10)
project(prog VERSION 0.1)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE MY_SOURCES "${SOURCE_DIR}/*.cpp")

configure_file(
                "${PROJECT_SOURCE_DIR}/inc/config.h.in"
                "${PROJECT_SOURCE_DIR}/inc/config.h"
)


add_definitions(${NCURSES_CFLAGS})
add_definitions(-D_XOPEN_SOURCE_EXTENDED=1)

add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    "${PROJECT_SOURCE_DIR}/inc" 
    ${NCURSES_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} 
    ${NCURSES_LIBRARIES}
    ncursesw
)
#target_link_libraries(${PROJECT_NAME} ncursesw)