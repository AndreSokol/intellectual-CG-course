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

file(GLOB SOURCES "*/*.cpp")
file(GLOB HEADERS "*/*.hpp")

message(sources ${SOURCES})
message(headers ${HEADERS})

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES} primitives/Triangle.cpp utils/bounding_box.cpp)
#add_executable(${PROJECT_NAME} main.cpp utils/vec3.cpp utils/vec3.hpp primitives/Sphere.hpp utils/Color.hpp PointLight.hpp primitives/Triangle.hpp primitives/BasePrimitive.hpp gl_const.hpp Material.hpp utils/geo_loaders.cpp utils/geo_loaders.hpp utils/task_queue.cpp utils/task_queue.hpp utils/bvh.cpp utils/bvh.hpp utils/bounding_box.cpp utils/bounding_box.hpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
