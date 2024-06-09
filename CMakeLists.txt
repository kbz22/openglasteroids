cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)

project(OpenGLAsteroids C CXX ASM)

add_executable(OpenGLAsteroids
    src/main.cpp
    
    src/glad/glad.c

    src/OpenGLEngine/Camera.cpp
    src/OpenGLEngine/GLFWWindowDestructorClass.cpp
    src/OpenGLEngine/Mesh.cpp
    src/OpenGLEngine/Model.cpp
    src/OpenGLEngine/Shader.cpp
    src/OpenGLEngine/Sprite.cpp
    src/OpenGLEngine/Texture.cpp
    src/OpenGLEngine/TextureContainer.cpp
    src/OpenGLEngine/UserPreferences.cpp
    src/OpenGLEngine/Window.cpp

    src/Game/Asteroid.cpp
    src/Game/CollisionBox.cpp
    src/Game/dir.txt
    src/Game/Game.cpp
    src/Game/GameObject.cpp
    src/Game/Spaceship.cpp
)

target_include_directories(OpenGLAsteroids PUBLIC 
    inc/
)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(  
  assimp URL https://github.com/assimp/assimp/archive/refs/tags/v5.4.1.zip
)
FetchContent_MakeAvailable(assimp)

target_link_libraries(OpenGLAsteroids PUBLIC assimp)

target_link_libraries(OpenGLAsteroids PUBLIC glfw3)

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLAsteroids PUBLIC OpenGL::GL)