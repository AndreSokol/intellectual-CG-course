cmake_minimum_required(VERSION 3.5)

project(stupid-render)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


if (WIN32)
    set(SDL2_DIR C:/MinGW/SDL)
endif ()
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp utils/vec3.cpp utils/vec3.hpp primitives/Sphere.hpp utils/Color.hpp PointLight.hpp primitives/Triangle.hpp primitives/BasePrimitive.hpp gl_const.hpp Material.hpp utils/geo_loaders.cpp utils/geo_loaders.hpp utils/task_queue.cpp utils/task_queue.hpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
