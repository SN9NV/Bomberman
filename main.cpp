#include <chrono>
#include <thread>
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
#include "io/audio/AudioSource.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;


int main()
{
//	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
//	cge::InputManager inputManager(window);
	cge::Loader loader;
//	Player *player;
//	cge::Model BomberMan;
//	LevelRunner *level1Runner;
//	cge::GameState gameState = cge::GameState::PLAY_MENU;
//	(void)gameState; ///> TODO remove
//
//	std::vector<std::string> map = {
//			"6",
//			"w w w w w w w w w w w w w w w",
//			"w . . . . . . . . . . . . . w",
//			"w . w d w d w d w d w d w . w",
//			"w . . d . d . . . d . . . . w",
//			"w . w d w d w d w d w d w . w",
//			"w . . . . d . . . . . . . . w",
//			"w . w d w d w d w d w d w . w",
//			"w . . d . . . . . d . . . . w",
//			"w . w d w d w d w d w d w . w",
//			"w . . . . . . . . . . . . . w",
//			"w . w d w d w d w d w d w . w",
//			"w . . d . . . d . . . d . . w",
//			"w . w d w d w d w d w d w . w",
//			"w p . d . . . . . . . . d . w",
//			"w w w w w w w w w w w w w w w"
//	};
//
//	for (auto &mapStr : map)
//		mapStr.erase(std::remove(mapStr.begin(), mapStr.end(), ' '), mapStr.end());
//
//	BomberMan = cge::Model("resources/models/Bomber.glb", "resources/models/BomberManTextureDiffuseColor.png", loader);
//	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, {0.5f ,0.0f, 0.5f}, 0.01f);
//	level1Runner = new LevelRunner(loader,player, window);
//	(void)level1Runner; ///> TODO remove
//
//	cge::GUI::MainMenuScreen mmScreen(window);

	cge::Audio::Device	defaultDevice;
	cge::Audio::Source	source("resources/audio/MainTheme.ogg", loader);

	source.setPlay(true);
	while (source.isPlaying()) {
		unsigned	offset = source.getPlayOffset(cge::Audio::Source::Offset::MILLISECONDS);
		unsigned	size = source.getFileSize(cge::Audio::Source::Offset::MILLISECONDS);
		double		percentage = offset / size * 100.0;

		std::cout << "Playing " << source.getName() << " " << offset << "ms (" << percentage << "%)" << "\n\r";

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}