cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(RESOURCE_DIRS
	shaders
)

set(RESOURCE_FILES
	shaders/fragmentshader.fsh
	shaders/vertexshader.vsh
)

set(SOURCES
	src/main.cpp
	src/MainGame.cpp
	src/Sprite.cpp
	src/GLSLProgram.cpp
	src/Position2D.cpp
	src/Colour.cpp
	src/Vertex.cpp

	includes/MainGame.hpp
	includes/Sprite.hpp
	includes/GLSLProgram.hpp
	includes/Position2D.hpp
	includes/Colour.hpp
	includes/Vertex.hpp
)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLEW	REQUIRED glew)
pkg_search_module(GLM	REQUIRED glm)
pkg_search_module(SDL2	REQUIRED sdl2)

include_directories(
	includes
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
)

link_directories(
	${GLEW_LIBRARY_DIRS}
	${SDL2_LIBRARY_DIRS}
	${GLM_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${GLM_LIBRARIES}
)

foreach(RESOURCE_DIR ${RESOURCE_DIRS})
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
	)
endforeach()
