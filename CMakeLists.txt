cmake_minimum_required(VERSION 2.8)
project(Bomberman)

# Use C++ 14 Standard and Wall Wextra Werror flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
	shaders
	images
)

# Source files to be compiled
set(SOURCE_FILES
	src/main.cpp
	src/MainGame.cpp
	src/Sprite.cpp
	src/GLSLProgram.cpp
	src/IO.cpp
	src/picoPNG.cpp
	src/ImageLoader.cpp
	src/TextureCache.cpp
	src/ResourceManager.cpp
	src/Window.cpp
	src/Camera.cpp
	src/SpriteBatch.cpp
	src/FPSCounter.cpp
	src/Projectile.cpp
	src/Entity.cpp
	src/Model.cpp
)

# Header files to be compiled
set(HEADER_FILES
	includes/Exceptions.hpp
	includes/MainGame.hpp
	includes/Sprite.hpp
	includes/GLSLProgram.hpp
	includes/IO.hpp
	includes/picoPNG.hpp
	includes/ImageLoader.hpp
	includes/ResourceManager.hpp
	includes/TextureCache.hpp
	includes/Window.hpp
	includes/Structs.hpp
	includes/Camera.hpp
	includes/SpriteBatch.hpp
	includes/InputManager.hpp
	includes/FPSCounter.hpp
	includes/Projectile.hpp
	includes/Entity.hpp
	includes/Model.hpp
)

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

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

#### After compilation ####

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${GLM_LIBRARIES}
)

# Function to symbolically link the resources into the build directory
#	Won't work on Windows
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
	)
endforeach()
