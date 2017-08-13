cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-deprecated-declarations")

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui")
  message(FATAL_ERROR "The Bomberman dependency repositories (NanoGUI) are missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by calling \"git submodule update --init --recursive\"")
endif()

set(SOURCE_FILES shared.hpp
		tinyGLTF/picojson.h
		tinyGLTF/stb_image.h
        tinyGLTF/tiny_gltf.h
        BomberManGameLogic/MapLoader.cpp
        BomberManGameLogic/Being.cpp
        BomberManGameLogic/Being.h
		tinyGLTF/picojson.h
        tinyGLTF/stb_image.h
        tinyGLTF/tiny_gltf.h
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
		BomberManGameLogic/Being.cpp
		BomberManGameLogic/Being.h
		BomberManGameLogic/Player.cpp
		BomberManGameLogic/Player.hpp
		BomberManGameLogic/GameLogic.h
        BomberManGameLogic/Bomb.cpp
        BomberManGameLogic/Bomb.hpp
        BomberManGameLogic/LevelRunner.cpp
        BomberManGameLogic/LevelRunner.hpp BomberManGameLogic/DestructWall.cpp BomberManGameLogic/DestructWall.hpp BomberManGameLogic/Gate.cpp BomberManGameLogic/Gate.hpp BomberManGameLogic/Balloon.cpp BomberManGameLogic/Balloon.hpp
		#gui/GuiManager.cpp gui/GuiManager.hpp
		gui/MainMenuScreen.cpp gui/MainMenuScreen.hpp
		io/audio/AudioManager.cpp io/audio/AudioManager.hpp
		io/audio/AudioListener.cpp io/audio/AudioListener.hpp io/audio/AudioSource.cpp io/audio/AudioSource.hpp io/audio/AudioDevice.cpp io/audio/AudioDevice.hpp)

# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)	#> Linux => libopenal-dev
find_package(PkgConfig REQUIRED)

# Find the dependencies for the project				Mac				Linux
pkg_search_module(GLEW		REQUIRED glew)		#> 	glew			libglew-dev
pkg_search_module(GLM		REQUIRED glm)		#> 	glm				Install from source (https://github.com/g-truc/glm)
pkg_search_module(GLFW3		REQURIED glfw3)		#> 	glfw3			libglfw3-dev
#pkg_search_module(OPENAL	REQURIED openal)	#> 					libopenal-dev
pkg_search_module(SNDFILE	REQURIED sndfile)	#> 	sndfile?		libsndfile1-dev

# Directories to find the header files
include_directories(
        includes
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/include
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/nanovg/src
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/eigen
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIRS}
        ${SNDFILE_INCLUDE_DIRS}
)

# Directories to find the libraries
link_directories(
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/build
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
		${GLFW3_LIBRARY_DIRS}
		${OPENAL_LIBRARY_DIRS}
		${SNDFILE_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
		${GLFW3_LIBRARIES}
		${OPENAL_LIBRARIES}
		${SNDFILE_LIBRARIES}
		nanogui
)

if (NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/dependencies/nanogui/build")
	message("Building NanoGUI...")
	add_custom_command(
		TARGET ${PROJECT_NAME}
		PRE_BUILD
		COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/install_dependencies.sh
		WORKING_DIRECTORY 	${PROJECT_SOURCE_DIR}/dependencies/nanogui/
	)
endif()