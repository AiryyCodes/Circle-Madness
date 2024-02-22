cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

find_package(glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(ext/glad)
target_link_libraries(${PROJECT_NAME} glad)
