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
#include "io/audio/AudioManager.hpp"
#include "io/audio/AudioDevice.hpp"
#include "error_handling/printError.hpp"

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
	(void)gameState; ///> TODO remove

	std::vector<std::string> map = {
			"6",
			"w w w w w w w w w w w w w w w",
			"w . . . . . . . . . . . . . w",
			"w . w d w d w d w d w d w . w",
			"w . . d . d . . . d . . . . w",
			"w . w d w d w d w d w d w . w",
			"w . . . . d . . . . . . . . w",
			"w . w d w d w d w d w d w . w",
			"w . . d . . . . . d . . . . w",
			"w . w d w d w d w d w d w . w",
			"w . . . . . . . . . . . . . w",
			"w . w d w d w d w d w d w . w",
			"w . . d . . . d . . . d . . w",
			"w . w d w d w d w d w d w . w",
			"w p . d . . . . . . . . d . w",
			"w w w w w w w w w w w w w w w"
	};

	for (auto &mapStr : map)
		mapStr.erase(std::remove(mapStr.begin(), mapStr.end(), ' '), mapStr.end());

	BomberMan = cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png", loader);
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, {0.5f ,0.0f, 0.5f}, 0.01f);
	level1Runner = new LevelRunner(loader,player, window);

	cge::GUI::MainMenuScreen mmScreen(window);

//	while (gameState != cge::WANTS_QUIT) {
//		switch (gameState) {
//			case cge::PLAY_GAME:
//				level1Runner->runLevel(map);
//				break;
//			case cge::PLAY_MENU:
//				break;
//			default:
//				mmScreen.setInputCallbacks();
//				mmScreen.drawScreen();
//				//level1Runner->runLevel(map);
//				break;
//		}
//	}

	auto devices = cge::Audio::Device::listDevices();

	std::cout << "Number of devices: " << devices.size() << "\n";

	for (auto &device : devices) {
		std::cout << device << "\n";
	}

	ALCdevice	*device = alcOpenDevice(nullptr);
		getALError();

	(void)device;

	ALboolean enumeration;

	enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");

	std::cout << (enumeration == AL_FALSE ? "FALSE" : "TRUE") << "\n";
	getALError();

	std::cout << "Default device: " << alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER) << "\n";

//	audioManager.setDevice(devices[0]);

//	level1Runner->runLevel(map);
	return 0;
}