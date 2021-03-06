#include "shared.hpp"

#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"
#include <glm/glm.hpp>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define FONTSTASH_IMPLEMENTATION
#define GLFONTSTASH_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"
#include "BomberManGameLogic/LevelRunner.hpp"
#include "shared.hpp"
#include "gui/MainMenuScreen.hpp"
#include "gui/GuiManager.hpp"

int main() {
	cge::Settings::Settings::Initialise("resources/settings/settings.data");
	cge::Settings::Settings *setts = cge::Settings::Settings::getSingleton();

	unsigned int winFlags = cge::Window::Flags::VSYNC_ENABLED;
	if (setts->getSettings().Fullscreen)
		winFlags |= cge::Window::Flags::FULLSCREEN;

	cge::Window window("Bomberman", setts->getSettings().Width, setts->getSettings().Height, winFlags);
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
		"../resources/Maps/Map3",
		"../resources/Maps/Map4",
		"../resources/Maps/Map5",
		"../resources/Maps/Map6"
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

	cge::Model BomberMan = cge::Model("resources/models/Bomber.glb", "resources/models/BomberManTextureDiffuseColor.png", loader, cge::Model::Type::STREAMING);
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, loader, 0.25f, 0.007);
	levelRunner = new LevelRunner(loader, player, window, &inputManager, defaultAudioDevice);

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
					else if (state == levelState::COMPLETE && (size_t)currMap < maps.size()) {
						currMap++;
						if ((size_t)currMap >= maps.size()) {
							levelRunner->DrawEOGCredits();
							gameState = cge::GameState::PLAY_MENU;
						}
						if (currMap % 2 == 0)
							player->addLives(1);
					}
				} else {
					levelRunner->DrawEOGCredits();
					gameState = cge::PLAY_MENU;
				}
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
