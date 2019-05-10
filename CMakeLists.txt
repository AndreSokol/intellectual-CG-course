cmake_minimum_required(VERSION 3.5)

project(stupid-render)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Og")

if (WIN32)
    set(SDL2_DIR C:/MinGW/SDL)
endif ()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SOURCES "*/*.cpp")
file(GLOB HEADERS "*/*.hpp")

message(sources ${SOURCES})
message(headers ${HEADERS})

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES} settings.cpp settings.hpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
