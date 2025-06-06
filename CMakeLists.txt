cmake_minimum_required(VERSION 3.10)
project(ogt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)

add_executable(ogt
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/renderer/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/fileio.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/buffers.cpp
    ${CMAKE_SOURCE_DIR}/src/renderer/texture.cpp
)
target_include_directories(ogt PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src
)


target_link_libraries(ogt
    OpenGL::GL
    glfw
)
