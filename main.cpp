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

//static constexpr unsigned HEIGHT = 720;
//static constexpr unsigned WIDTH = 1024;

void	playAudio(cge::Audio::Source &audio, unsigned sleepMilliseconds = 100) {
	audio.setPlaying();

	while (audio.isPlaying()) {
		unsigned	offset = audio.getPlayOffset(cge::Audio::Source::Offset::MILLISECONDS);
		unsigned	size = audio.getFileSize(cge::Audio::Source::Offset::MILLISECONDS);
		double		percentage = static_cast<double>(offset) / static_cast<double>(size) * 100.0;

		std::cout << "Default device Playing: " << audio.getName() << " " << offset << "ms / " << size << "ms (" << percentage << "%)" << "\n";

		std::this_thread::sleep_for(std::chrono::milliseconds(sleepMilliseconds));
	}
}

int main()
{
//	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
//	cge::InputManager inputManager(window);
	cge::Loader loader;

	cge::Audio::Device	defaultDevice;
	cge::Audio::Source	Theme("resources/audio/MainTheme.ogg", loader);
	cge::Audio::Source	MenuClick("resources/audio/menu_click.wav", loader);
	cge::Audio::Source	explosion("resources/audio/sfx_explosion.wav", loader);

	playAudio(explosion);
	playAudio(MenuClick);
	playAudio(Theme);

	return 0;
}