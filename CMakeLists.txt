cmake_minimum_required(VERSION 3.9)
project(CGProject)
include_directories("/opt/local/include")
link_directories("/opt/local/lib")
include_directories("utils")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -w -framework OpenGL -g -Dsprintf_s=sprintf")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_executable(CGProject WormholeDash.cpp src/engine/GameObject.cpp src/engine/GameObject.h src/OpenGLWrapper.cpp src/OpenGLWrapper.h src/engine/GameContext.cpp src/engine/GameContext.h src/engine/Scene.cpp src/engine/Scene.h src/engine/SceneManager.cpp src/engine/SceneManager.h)
target_link_libraries(CGProject GLUT glew)
