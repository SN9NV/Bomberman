cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES
		tinyGLTF/picojson.h tinyGLTF/stb_image.h tinyGLTF/tiny_gltf.h

		main.cpp
		entites/Camera.cpp entites/Camera.hpp
		io/InputManager.cpp io/InputManager.hpp
		entites/Entity.cpp entites/Entity.hpp
		entites/Model.cpp entites/Model.hpp
		entites/Texture.cpp entites/Texture.hpp
		io/Window.cpp io/Window.hpp
		error_handling/Exceptions.hpp
		rendering/GLSLProgram.cpp rendering/GLSLProgram.hpp
		loaders/IO.cpp loaders/IO.hpp
		rendering/Renderer.cpp rendering/Renderer.hpp
		extras/Maths.cpp extras/Maths.hpp
		loaders/Loader.cpp loaders/Loader.hpp
		loaders/picoPNG.cpp loaders/picoPNG.hpp
		extras/glmOstream.cpp extras/glmOstream.hpp
		error_handling/glError.cpp error_handling/glError.hpp
		entites/Player.cpp entites/Player.hpp)


# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# Find the dependencies for the project
pkg_search_module(GLEW	REQUIRED glew)
pkg_search_module(GLM	REQUIRED glm)
pkg_search_module(SDL2	REQUIRED sdl2)

# Directories to find the header files
include_directories(
        includes
        ${GLEW_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)

# Directories to find the libraries
link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${SDL2_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${GLM_LIBRARIES}
)