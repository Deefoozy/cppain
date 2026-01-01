cmake_minimum_required(VERSION 4.0)
project(cppain VERSION 0.0.69)

set(CMAKE_CXX_STANDARD 20)

add_executable(cppain main.cpp)

find_package(Vulkan)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

target_link_libraries(cppain PRIVATE glfw)
target_link_libraries(cppain PRIVATE glm)
target_link_libraries(cppain PRIVATE Vulkan::Vulkan)
