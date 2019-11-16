cmake_minimum_required(VERSION 3.5)

project(stupid-render)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O1")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(GLEW 2.1 REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
###

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SOURCES "*/*.cpp")
file(GLOB HEADERS "*/*.hpp")

message(sources ${SOURCES})
message(headers ${HEADERS})

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} GL X11 Xrandr Xi)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} glfw)
