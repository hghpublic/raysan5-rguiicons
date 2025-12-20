cmake_minimum_required(VERSION 4.2)

project(external LANGUAGES C)


# tinyfiledialogs

set(target tinyfiledialogs)
add_library(${target} STATIC tinyfiledialogs.c)
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# raygui

set(target raygui)
add_library(${target} INTERFACE)
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# rprand
set(target rprand)
add_library(${target} INTERFACE)
target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_LIST_DIR})
