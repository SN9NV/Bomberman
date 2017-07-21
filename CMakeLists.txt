cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES
	main.cpp
	loadshaders.cpp
	MainGame.cpp
)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLEW	REQUIRED glew)
pkg_search_module(GLM	REQUIRED glm)
pkg_search_module(SDL	REQUIRED sdl2)

include_directories(
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	${SDL_INCLUDE_DIRS}
)

link_directories(
	${GLEW_LIBRARY_DIRS}
	${GLM_LIBRARY_DIRS}
	${SDL_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLM_LIBRARIES}
	${SDL_LIBRARIES}
)
