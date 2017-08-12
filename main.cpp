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

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;


int main()
{
	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::InputManager inputManager(window);
	cge::Loader loader;
	Player *player;
	cge::Model BomberMan;
	LevelRunner *level1Runner;
	cge::GameState gameState = cge::GameState::PLAY_MENU;

	std::vector<std::string> map = {
			"6",
			"wwwwwwwwwwwwwww",
			"w.............w",
			"w.wdwdwdwdwdw.w",
			"w..d.d...d....w",
			"w.wdwdwdwdwdw.w",
			"w....d........w",
			"w.wdwdwdwdwdw.w",
			"w..d.....d....w",
			"w.wdwdwdwdwdw.w",
			"w.............w",
			"w.wdwdwdwdwdw.w",
			"w..d...d...d..w",
			"w.wdwdwdwdwdw.w",
			"wp.d........d.w",
			"wwwwwwwwwwwwwww"
	};

	BomberMan = (cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							loader));
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, {0.5f ,0.0f, 0.5f}, 0.01f);
	level1Runner = new LevelRunner(loader,player, window);

	cge::GUI::MainMenuScreen mmScreen(window, &gameState);

	while (gameState != cge::WANTS_QUIT) {
		switch (gameState) {
			case (cge::PLAY_GAME):
				level1Runner->runLevel(map);
				break;
			case (cge::PLAY_MENU):
				mmScreen.setInputCallbacks();
				mmScreen.drawScreen();
				break;
			default:
				throw std::exception();
		}
	}


	level1Runner->runLevel(map);
	return 0;
}