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
	cge::Audio::Source	defaultTheme("resources/audio/MainTheme.ogg", loader);
	cge::Audio::Source	defaultMenuClick("resources/audio/menu_click.wav", loader);

	cge::Audio::Device	secondDevice(cge::Audio::Device::listDevices()[2]);
	cge::Audio::Source	secondTheme("resources/audio/MainTheme.ogg", loader);
	cge::Audio::Source	secondMenuClick("resources/audio/menu_click.wav", loader);

	defaultDevice.setToCurrentContext();
	defaultTheme.setPlaying();

	secondDevice.setToCurrentContext();
	secondTheme.setPlaying();

	bool playing = true;

	while (playing) {
		defaultDevice.setToCurrentContext();

		bool defaultThemePlaying = defaultTheme.isPlaying();

		if (defaultThemePlaying) {
			unsigned	offset = defaultTheme.getPlayOffset(cge::Audio::Source::Offset::MILLISECONDS);
			unsigned	size = defaultTheme.getFileSize(cge::Audio::Source::Offset::MILLISECONDS);
			double		percentage = static_cast<double>(offset) / static_cast<double>(size) * 100.0;

			std::cout << "Default device Playing: " << defaultTheme.getName() << " " << offset << "ms / " << size << "ms (" << percentage << "%)" << "\n";
		}

		secondDevice.setToCurrentContext();
		bool secondMenuClickPlaying = secondTheme.isPlaying();

		if (secondMenuClickPlaying) {
			unsigned	offset = secondTheme.getPlayOffset(cge::Audio::Source::Offset::MILLISECONDS);
			unsigned	size = secondTheme.getFileSize(cge::Audio::Source::Offset::MILLISECONDS);
			double		percentage = static_cast<double>(offset) / static_cast<double>(size) * 100.0;

			std::cout << "USB device Playing: " << secondTheme.getName() << " " << offset << "ms / " << size << "ms (" << percentage << "%)" << "\n";
		}

		playing = defaultThemePlaying || secondMenuClickPlaying;


		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}