cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui")
	message(ERROR "The Bomberman dependency repositories (NanoGUI) are missing! "
			"You probably did not clone the project with --recursive.\n"
			"Automatically cloning submodules...")
	execute_process(COMMAND git submodule update --init --recursive)
endif ()


function(installPkg pkgApple pkgLinux)
	if (APPLE AND ${pkgApple})
		execute_process(COMMAND brew install ${pkgApple})
	elseif(LINUX AND ${pkgLinux})
		execute_process(COMMAND sudo apt install ${pkgLinux})
	endif()
endfunction()

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()


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
		error_handling/printError.cpp error_handling/printError.hpp
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
		io/audio/AudioSource.cpp io/audio/AudioSource.hpp
		io/audio/AudioDevice.cpp io/audio/AudioDevice.hpp
		gui/CustomButton.cpp gui/CustomButton.hpp)


# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)	#> Linux => libopenal-dev
find_package(PkgConfig REQUIRED)

if (NOT PKG_CONFIG_FOUND)
	installPkg(pkg-config pkg-config)
endif()

# Find the dependencies for the project				Mac				Linux
pkg_search_module(GLEW		REQUIRED glew)			#> 	glew			libglew-dev
pkg_search_module(GLM		REQUIRED glm)			#> 	glm				Install from source (https://github.com/g-truc/glm)
#pkg_search_module(GLFW3		REQURIED glfw3)		#> 	glfw3			libglfw3-dev
pkg_search_module(SNDFILE	REQURIED sndfile)		#> 	libsndfile		libsndfile1-dev
pkg_search_module(FT REQUIRED freetype2)

if (NOT GLEW_FOUND)
	installPkg(glew libglew-dev)
endif()

if (NOT GLM_FOUND)
	installPkg(glm FALSE)
endif()

if (NOT FT_FOUND)
	installPkg(freetype)
endif()

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
		${OPENAL_INCLUDE_DIR}
		${SNDFILE_INCLUDE_DIRS}
)

# Directories to find the libraries
link_directories(
		${PROJECT_SOURCE_DIR}/dependencies/nanogui/build
		${GLEW_LIBRARY_DIRS}
		${GLM_LIBRARY_DIRS}
		${FT_LIBRARY_DIRS}
		${SNDFILE_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
		${OPENGL_LIBRARIES}
		${OPENAL_LIBRARY}
		${GLEW_LIBRARIES}
		${GLM_LIBRARIES}
		${SNDFILE_LIBRARIES}
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