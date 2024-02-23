cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

find_package(glfw)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(ext/glad)
target_link_libraries(${PROJECT_NAME} glad)
