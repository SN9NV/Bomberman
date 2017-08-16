#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"
#include "BomberManGameLogic/GameLogic.h"
#include "BomberManGameLogic/Player.hpp"
#include "BomberManGameLogic/LevelRunner.hpp"
#include "shared.hpp"
#include "gui/MainMenuScreen.hpp"
#include "gui/GuiManager.hpp"

#if defined(NANOGUI_GLAD)
#if defined(NANOGUI_SHARED) && !defined(GLAD_GLAPI_EXPORT)
#define GLAD_GLAPI_EXPORT
#endif

#include <glad/glad.h>
#else
#if defined(__APPLE__)
#define GLFW_INCLUDE_GLCOREARB
#else
#define GL_GLEXT_PROTOTYPES
#endif
#endif

#include <GLFW/glfw3.h>

#include <nanogui/nanogui.h>
#include <iostream>

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;


int main() {
	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GameState gameState = cge::GameState::PLAY_MENU;
	cge::InputManager inputManager(window);
	cge::Loader loader;
	Player *player;
	cge::Model BomberMan;
	LevelRunner *levelRunner;

	BomberMan = (cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							loader));
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, 0.25f, 0.007);
	//player->setDamage(3);
	levelRunner = new LevelRunner(loader, player, window, &inputManager);

	cge::GuiManager::initialise(window, &gameState, player);
int state;
	while (gameState != cge::WANTS_QUIT) {
		switch (gameState) {
			case (cge::PLAY_GAME):
				if (player->getLives() > 0) {
					glfwSetInputMode(window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					state = levelRunner->runLevel("../resources/Maps/Map1");
					if (state == levelState::PAUSE)
						gameState = cge::PLAY_PAUSE;
					std::cout << "level exit state " << state << std::endl;
					std::cout << "Player Lives: " << player->getLives() << std::endl;
				} else
					gameState = cge::PLAY_MENU;
				break;
			case (cge::PLAY_PAUSE):
				cge::GuiManager::getSingleton()->drawScreen(cge::GameState::PLAY_PAUSE);
				break;
			case (cge::RESUME):
				player->setPauseMenue(false);
				glfwSetInputMode(window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				inputManager.pollKeyEvnt();
				std::cout << "esc is pressed: " << inputManager.isKeyPressed(GLFW_KEY_ESCAPE) << std::endl;
					state = levelRunner->resumeLevel();
					if (state == levelState::PAUSE)
						gameState = cge::PLAY_PAUSE;
					std::cout << "level exit state " << state << std::endl;
					std::cout << "Player Lives: " << player->getLives() << std::endl;
				break;
			default:
				cge::GuiManager::getSingleton()->drawScreen(gameState);
				break;
		}
	}
	return 0;
}