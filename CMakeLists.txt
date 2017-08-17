cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui")
	message(FATAL_ERROR "The Bomberman dependency repositories (NanoGUI) are missing! "
			"You probably did not clone the project with --recursive. It is possible to recover "
			"by calling \"git submodule update --init --recursive\"")
endif ()


set(SOURCE_FILES
		shared.hpp
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
        BomberManGameLogic/Being.cpp
		BomberManGameLogic/Being.h
		BomberManGameLogic/Player.cpp
		BomberManGameLogic/Player.hpp
		BomberManGameLogic/GameLogic.h
		BomberManGameLogic/Bomb.cpp
		BomberManGameLogic/Bomb.hpp
		BomberManGameLogic/LevelRunner.cpp
		BomberManGameLogic/LevelRunner.hpp
		BomberManGameLogic/DestructWall.cpp
		BomberManGameLogic/DestructWall.hpp
		BomberManGameLogic/Gate.cpp
		BomberManGameLogic/Gate.hpp
		BomberManGameLogic/Balloon.cpp
		BomberManGameLogic/Balloon.hpp
		BomberManGameLogic/Wall.cpp
		BomberManGameLogic/Wall.h
		gui/GuiManager.cpp
		gui/GuiManager.hpp
		gui/MainMenuScreen.cpp
		gui/MainMenuScreen.hpp
		gui/SettingsScreen.cpp
		gui/SettingsScreen.hpp
		gui/LoadGameScreen.cpp
		gui/LoadGameScreen.hpp
        entites/Partical.cpp
		entites/Partical.hpp
		rendering/ParticalRenderer.cpp
		rendering/ParticalRenderer.hpp
		entites/RawModel.cpp
		entites/RawModel.hpp
        entites/Partical.cpp
		gui/SaveGameScreen.cpp
		gui/SaveGameScreen.h
		gui/PauseGameScreen.cpp
		gui/PauseGameScreen.h
		entites/TextureAtlas.cpp
		entites/TextureAtlas.h
		gui/SaveGameScreen.cpp
		gui/SaveGameScreen.h
		gui/PauseGameScreen.cpp
		gui/PauseGameScreen.h
		rendering/SpriteRenderer.cpp
		rendering/SpriteRenderer.hpp
		rendering/TextRenderer.cpp
		rendering/TextRenderer.hpp
		)


# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# Find the dependencies for the project
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(FT REQUIRED freetype2)
#pkg_search_module(GLFW3	REQURIED glfw3)

# Directories to find the header files
include_directories(
		includes
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/include
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/nanovg/src
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/eigen
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/glfw/include
		${GLEW_INCLUDE_DIRS}
		${GLM_INCLUDE_DIRS}
		${FT_INCLUDE_DIRS}
)

# Directories to find the libraries
link_directories(
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/build
		${GLEW_LIBRARY_DIRS}
		${GLM_LIBRARY_DIRS}
		${FT_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES}
		${GLM_LIBRARIES}
		nanogui
		${FT_LIBRARIES}
		)

if (NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/dependencies/nanogui/build")
	message("Building NanoGUI...")
	add_custom_command(
			TARGET ${PROJECT_NAME}
			PRE_BUILD
			COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/install_dependencies.sh
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/dependencies/nanogui/
	)
endif ()