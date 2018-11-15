cmake_minimum_required(VERSION 3.5)

project(stupid-render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


if (WIN32)
    set(SDL2_DIR C:/MinGW/SDL)
endif ()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp Vec3.cpp Vec3.h primitives/Sphere.h Color.h PointLight.h primitives/Triangle.h primitives/BasePrimitive.h gl_const.h Material.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
