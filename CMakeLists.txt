cmake_minimum_required(VERSION 3.5)
project(particle_sim)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
set(CMAKE_CXX_FLAGS         "-Wpedantic")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(packages/glfw)
add_subdirectory(packages/glad)
add_subdirectory(packages/glm)

add_executable(particle_sim
    src/opengl.cpp
    src/main.cpp
)

target_link_libraries(particle_sim PRIVATE glfw)
target_link_libraries(particle_sim PRIVATE glad)
target_link_libraries(particle_sim PRIVATE glm::glm)