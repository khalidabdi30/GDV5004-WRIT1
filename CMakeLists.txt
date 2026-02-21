cmake_minimum_required(VERSION 3.16)
project(SceneFileVerifier)

set(CMAKE_CXX_STANDARD 17)

add_executable(SceneVerifier
    src/main.cpp
    src/Scene.cpp
    src/SceneNode.cpp
    external/tinyxml2/tinyxml2.cpp
)

target_include_directories(SceneVerifier PRIVATE
    src
    external/tinyxml2
)
