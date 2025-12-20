# cmake_minimum_required(VERSION 4.2)

# project(rguiicons LANGUAGES C)

option(PLATFORM_DESKTOP "Build for desktop platforms" ON)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(external)

set(target ${PROJECT_NAME})
add_executable(${target})
target_sources(${target} PRIVATE rguiicons.c)
target_link_libraries(${target} PRIVATE raylib)
target_link_libraries(${target} PRIVATE glfw)
target_link_libraries(${target} PRIVATE m)
if(PLATFORM_DESKTOP)
target_compile_definitions(${target} PRIVATE PLATFORM_DESKTOP=1)
target_link_libraries(${target} PRIVATE tinyfiledialogs)
endif()
target_link_libraries(${target} PRIVATE raygui rprand)