cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
	shaders
	resources
)

# Source files to be compiled
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
		entites/Player.cpp entites/Player.hpp
		sounds/Sounds.cpp sounds/Sounds.hpp extras/tinygltfOstream.cpp extras/tinygltfOstream.hpp)


# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# Find the dependencies for the project
pkg_search_module(GLEW	REQUIRED glew)
pkg_search_module(GLM	REQUIRED glm)
pkg_search_module(SDL2	REQUIRED sdl2)

# Find SDL2 Mixer
if (NOT WIN32)
	if (PKG_CONFIG_FOUND)
		pkg_check_modules(_SDL2_MIXER SDL2_mixer)
		set(SDL2_MIXER_STRING ${_SDL2_MIXER_VERSION})
	endif ()
endif ()
find_path(SDL2_MIXER_INCLUDE_DIR
		SDL_mixer.h
		HINTS
		${_SDL2_MIXER_INCLUDEDIR}
		ENV SDL2MIXERDIR
		ENV SDL2DIR
		PATH_SUFFIXES
		SDL2
		include/SDL2
		include
		)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(VC_LIB_PATH_SUFFIX lib/x64)
else()
	set(VC_LIB_PATH_SUFFIX lib/x86)
endif()
find_library(SDL2_MIXER_LIBRARY
		NAMES
		SDL2_mixer
		HINTS
		${_SDL2_MIXER_LIBDIR}
		ENV SDL2MIXERDIR
		ENV SDL2DIR
		PATH_SUFFIXES
		lib
		${VC_LIB_PATH_SUFFIX}
		)
if(SDL2_MIXER_INCLUDE_DIR AND EXISTS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" AND NOT SDL2_MIXER_STRING)
	file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+[0-9]+$")
	file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+[0-9]+$")
	file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+[0-9]+$")
	string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MAJOR "${SDL2_MIXER_VERSION_MAJOR_LINE}")
	string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MINOR "${SDL2_MIXER_VERSION_MINOR_LINE}")
	string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_PATCH "${SDL2_MIXER_VERSION_PATCH_LINE}")
	set(SDL2_MIXER_VERSION_STRING ${SDL2_MIXER_VERSION_MAJOR}.${SDL2_MIXER_VERSION_MINOR}.${SDL2_MIXER_VERSION_PATCH})
	unset(SDL2_MIXER_VERSION_MAJOR_LINE)
	unset(SDL2_MIXER_VERSION_MINOR_LINE)
	unset(SDL2_MIXER_VERSION_PATCH_LINE)
	unset(SDL2_MIXER_VERSION_MAJOR)
	unset(SDL2_MIXER_VERSION_MINOR)
	unset(SDL2_MIXER_VERSION_PATCH)
endif()
set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_mixer
		REQUIRED_VARS SDL2_MIXER_LIBRARIES SDL2_MIXER_INCLUDE_DIRS
		VERSION_VAR SDL2_MIXER_VERSION_STRING)
# End SDL2 Mixer

# Directories to find the header files
include_directories(
        includes
        ${GLEW_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
		${SDL2_MIXER_INCLUDE_DIRS}
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
		${SDL2_MIXER_LIBRARIES}
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