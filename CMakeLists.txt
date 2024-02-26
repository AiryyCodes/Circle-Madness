cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "g++")

project(CircleMadness C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-6 -pthread")

file(GLOB SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/components/*.cpp"
    "src/components/*.h"
)

file(GLOB INCLUDES
    "src/*.h"
    "src/components/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(ext/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(ext/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(ext/freetype)
target_link_libraries(${PROJECT_NAME} freetype)

add_subdirectory(ext/glad)
target_link_libraries(${PROJECT_NAME} glad)
