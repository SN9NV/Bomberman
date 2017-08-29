cmake_minimum_required(VERSION 2.8)
project(Bomberman)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
		shaders
		resources
		)

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui/build")
	message(INFO "The Bomberman dependency repositories (NanoGUI) are missing! "
			"You probably did not clone the project with --recursive.\n"
			"Automatically cloning submodules...")
	execute_process(COMMAND git submodule update --init --recursive)
	message(INFO "Build NanoGUI")
	execute_process(COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/install_dependencies.sh
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/dependencies/nanogui/)
endif ()

set(INSTALLED_PACKAGE FALSE)

function(installPkg pkgApple pkgLinux)
	if (APPLE AND pkgApple)
		message("Installing " ${pkgApple} "...")
		execute_process(COMMAND brew install ${pkgApple})
	elseif(LINUX AND pkgLinux)
		execute_process(COMMAND sudo apt install ${pkgLinux})
	endif()

	set(INSTALLED_PACKAGE TRUE)
endfunction()

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()


set(SOURCE_FILES
		main.cpp
#		Testmain.cpp

		shared.hpp
		tinyGLTF/picojson.h
		tinyGLTF/stb_image.h
		tinyGLTF/tiny_gltf.h

		BomberManGameLogic/PowerUPAbstract.hpp
		BomberManGameLogic/Being.cpp		BomberManGameLogic/Being.hpp
		BomberManGameLogic/Player.cpp		BomberManGameLogic/Player.hpp
		BomberManGameLogic/Bomb.cpp			BomberManGameLogic/Bomb.hpp
		BomberManGameLogic/LevelRunner.cpp	BomberManGameLogic/LevelRunner.hpp
		BomberManGameLogic/DestructWall.cpp	BomberManGameLogic/DestructWall.hpp
		BomberManGameLogic/Gate.cpp			BomberManGameLogic/Gate.hpp
		BomberManGameLogic/Balloon.cpp		BomberManGameLogic/Balloon.hpp
		BomberManGameLogic/Wall.cpp			BomberManGameLogic/Wall.hpp
		BomberManGameLogic/FireUp.cpp		BomberManGameLogic/FireUp.hpp
		BomberManGameLogic/FireDown.cpp		BomberManGameLogic/FireDown.hpp
		BomberManGameLogic/FullFire.cpp		BomberManGameLogic/FullFire.hpp
		BomberManGameLogic/WingBoot.cpp		BomberManGameLogic/WingBoot.hpp
		BomberManGameLogic/Onil.cpp			BomberManGameLogic/Onil.hpp
		BomberManGameLogic/AddBomb.cpp		BomberManGameLogic/AddBomb.hpp
		BomberManGameLogic/LevelFactory.cpp	BomberManGameLogic/LevelFactory.hpp
		BomberManGameLogic/Deternator.cpp	BomberManGameLogic/Deternator.hpp
		BomberManGameLogic/Ovapi.cpp		BomberManGameLogic/Ovapi.hpp
		BomberManGameLogic/WallPass.cpp		BomberManGameLogic/WallPass.hpp
		BomberManGameLogic/Floor.cpp		BomberManGameLogic/Floor.hpp

		entites/Camera.cpp			entites/Camera.hpp
		entites/Entity.cpp			entites/Entity.hpp
		entites/Model.cpp			entites/Model.hpp
		entites/Texture.cpp			entites/Texture.hpp
		entites/RawModel.cpp		entites/RawModel.hpp
		entites/TextureAtlas.cpp	entites/TextureAtlas.hpp
		entites/Partical.cpp		entites/Partical.hpp
		entites/Sprite.cpp			entites/Sprite.hpp

		error_handling/printError.cpp	error_handling/printError.hpp

		extras/Maths.cpp			extras/Maths.hpp
		extras/glmOstream.cpp		extras/glmOstream.hpp
		extras/SavedGame.cpp		extras/SavedGame.hpp
		extras/tinygltfOstream.cpp	extras/tinygltfOstream.hpp

		gui/GuiManager.cpp			gui/GuiManager.hpp
		gui/MainMenuScreen.cpp		gui/MainMenuScreen.hpp
		gui/SettingsScreen.cpp		gui/SettingsScreen.hpp
		gui/LoadGameScreen.cpp		gui/LoadGameScreen.hpp
		gui/SaveGameScreen.cpp		gui/SaveGameScreen.hpp
		gui/PauseGameScreen.cpp		gui/PauseGameScreen.hpp
		gui/CustomButton.cpp		gui/CustomButton.hpp
		gui/CustomTextbox.cpp		gui/CustomTextbox.hpp

		io/InputManager.cpp			io/InputManager.hpp
		io/Window.cpp				io/Window.hpp
		io/audio/AudioSource.cpp	io/audio/AudioSource.hpp
		io/audio/AudioDevice.cpp	io/audio/AudioDevice.hpp
		io/settings/Settings.cpp	io/settings/Settings.hpp

		loaders/IO.cpp				loaders/IO.hpp
		loaders/Loader.cpp			loaders/Loader.hpp
		loaders/picoPNG.cpp			loaders/picoPNG.hpp

		rendering/GLSLProgram.cpp		rendering/GLSLProgram.hpp
		rendering/Renderer.cpp			rendering/Renderer.hpp
		rendering/ParticalRenderer.cpp	rendering/ParticalRenderer.hpp
		rendering/SpriteRenderer.cpp	rendering/SpriteRenderer.hpp
		rendering/TextRenderer.cpp		rendering/TextRenderer.hpp)


# Find OpenGL (for Mac mostly, Linux didn't need this)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)	#> Linux => libopenal-dev
find_package(PkgConfig)

if (NOT PKG_CONFIG_EXECUTABLE)
	installPkg(pkg-config pkg-config)
	find_package(PkgConfig REQUIRED)
endif()

# Find the dependencies for the project						Mac				Linux
pkg_search_module(GLEW		REQUIRED	glew)			#>	glew			libglew-dev
pkg_search_module(GLM		REQUIRED	glm)			#>	glm				Install from source (https://github.com/g-truc/glm)
#pkg_search_module(GLFW3		REQUIRED	glfw3)		#>	glfw3			libglfw3-dev
pkg_search_module(SNDFILE	REQUIRED	sndfile)		#>	libsndfile		libsndfile1-dev
pkg_search_module(FT		REQUIRED	freetype2)

if (NOT GLEW_FOUND)
	installPkg(glew libglew-dev)
endif()

if (NOT GLM_FOUND)
	installPkg(glm FALSE)
endif()

if (NOT SNDFILE_FOUND)
	installPkg(libsndfile libsndfile1-dev)
endif()

if (NOT FT_FOUND)
	installPkg(freetype FALSE)
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
		${FT_LIBRARIES}
		nanogui
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