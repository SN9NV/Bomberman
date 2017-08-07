cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES
		main.cpp
		Camera.cpp Camera.hpp
		InputManager.cpp InputManager.hpp
		Entity.cpp Entity.hpp
		Model.cpp Model.hpp
		Texture.cpp Texture.hpp
		Window.cpp Window.hpp
		Exceptions.hpp
		GLSLProgram.cpp GLSLProgram.hpp
		IO.cpp IO.hpp
		Renderer.cpp Renderer.hpp
		Maths.cpp Maths.hpp
		Loader.cpp Loader.hpp
		picoPNG.cpp picoPNG.hpp
		Vertex.hpp
		glmOstream.cpp glmOstream.hpp
		glError.cpp glError.hpp

		tinyGLTF/picojson.h tinyGLTF/stb_image.h tinyGLTF/tiny_gltf.h
		Player.cpp Player.hpp)



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