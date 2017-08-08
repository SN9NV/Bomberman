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

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;


int main() {
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::InputManager	inputManager;
	cge::Loader			loader;

	runLevel((std::string &) "recources/Level", loader, window);
	return 0;
}