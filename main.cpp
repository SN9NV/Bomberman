#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define FONTSTASH_IMPLEMENTATION
#define GLFONTSTASH_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"
#include "BomberManGameLogic/GameLogic.h"
#include "BomberManGameLogic/LevelRunner.hpp"
#include "shared.hpp"
#include "gui/MainMenuScreen.hpp"
#include "gui/GuiManager.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1280;


int main() {
	cge::Settings::Settings::Initialise("resources/settings/settings.data");
	cge::Settings::Settings *setts = cge::Settings::Settings::getSingleton();

	cge::Window window("Bomberman", setts->getSettings().Width, setts->getSettings().Height, cge::Window::Flags::VSYNC_ENABLED);
	cge::GameState		gameState = cge::GameState::PLAY_MENU;
	cge::GameState		prevGameState = gameState;
	cge::InputManager	inputManager(window);
	cge::Loader			loader;
	Player				*player;
	LevelRunner			*levelRunner;
	cge::Audio::Device	defaultAudioDevice;


	int currMap = 0;
	std::vector<std::string> maps = {
			"../resources/Maps/Map1",
			"../resources/Maps/Map2",
			"../resources/Maps/Map3"
	};
	cge::Audio::Source* menuSound = new cge::Audio::Source("../resources/audio/MainTheme.ogg", loader);
	menuSound->setLooping(true);
	menuSound->setGain(setts->getMusicVolume());
	std::vector<cge::Audio::Source *> levelSounds = {
			new cge::Audio::Source("../resources/audio/Area 1.ogg", loader),
			new cge::Audio::Source("../resources/audio/Area 2.ogg", loader),
			new cge::Audio::Source("../resources/audio/Area 3.ogg", loader),
			new cge::Audio::Source("../resources/audio/Area 4.ogg", loader),
			new cge::Audio::Source("../resources/audio/Area 5.ogg", loader),
			new cge::Audio::Source("../resources/audio/Area 6.ogg", loader),
	};

	cge::Model BomberMan = (cge::Model("resources/models/Bomber.glb", "resources/models/BomberManTextureDiffuseColor.png", loader));
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, 0.25f, 0.007);
	levelRunner = new LevelRunner(loader, player, window, &inputManager);

	cge::GuiManager::initialise(window, &gameState, &prevGameState, player, &currMap, loader);
	int state;
	while (gameState != cge::WANTS_QUIT) {
		switch (gameState) {
			case (cge::PLAY_GAME):
				if (player->getLives() > 0) {
					menuSound->setPlaying(false);
					levelSounds[currMap]->setGain(setts->getMusicVolume());
					levelSounds[currMap]->setLooping(true);
					levelSounds[currMap]->setPlaying();
					state = levelRunner->runLevel(maps[currMap]);
					levelSounds[currMap]->setPlaying(false);
					if (state == levelState::FAIL_MAP_LOAD) {
						std::cout << "Failed to load map: " << maps[currMap++] << std::endl;
						gameState = cge::GameState::PLAY_MENU;
					} else if (state == levelState::PAUSE)
						gameState = cge::PLAY_PAUSE;
					else if (state == levelState::COMPLEAT && (size_t)currMap < maps.size()) {
						currMap++;
						if ((size_t)currMap >= maps.size())
							state = cge::GameState::PLAY_MENU;
					}

					std::cout << "level exit state " << state << std::endl;
					std::cout << "Player Lives: " << player->getLives() << std::endl;
				} else
					gameState = cge::PLAY_MENU;
				break;
			case (cge::PLAY_PAUSE):
				menuSound->setGain(setts->getMusicVolume());
				if (!menuSound->isPlaying()) {
					menuSound->setPlaying();
				}
				cge::GuiManager::getSingleton()->drawScreen(cge::GameState::PLAY_PAUSE);
				break;
			case (cge::RESUME):
				menuSound->setPlaying(false);
				gameState = cge::GameState::PLAY_GAME;
				player->setPauseMenue(false);
				inputManager.pollKeyEvnt();
				levelSounds[currMap]->setGain(setts->getMusicVolume());
				levelSounds[currMap]->setLooping(false);
				levelSounds[currMap]->setPlaying();
				state = levelRunner->resumeLevel();
				levelSounds[currMap]->setPlaying(false);
				if (state == levelState::PAUSE)
					gameState = cge::PLAY_PAUSE;
				std::cout << "level exit state " << state << std::endl;
				std::cout << "Player Lives: " << player->getLives() << std::endl;
				break;
			default:
				menuSound->setGain(setts->getMusicVolume());
				if (!menuSound->isPlaying()) {
					menuSound->setPlaying();
				}
				cge::GuiManager::getSingleton()->drawScreen(gameState);
				break;
		}
	}
	for (auto iter : levelSounds) {
		delete iter;
	}
	return 0;
}