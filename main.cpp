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

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;


int main()
{
	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::InputManager inputManager;
	cge::Loader loader;
	Player *player;
	cge::Model BomberMan;
	LevelRunner *levelRunner;
	std::vector<std::string> map = {
			"wwwwwwwwwwwwwww",
			"w.............w",
			"w..d.d.d.d.d..w",
			"w.............w",
			"w..d.......d..w",
			"w......p......w",
			"w..d.......d..w",
			"w.............w",
			"w..d.d.d.d....w",
			"w.............w",
			"w.............w",
			"w.............w",
			"w.............w",
			"w...........d.w",
			"wwwwwwwwwwwwwww"
	};

	BomberMan = (cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							loader));
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, 0.01f);
	levelRunner = new LevelRunner(loader,player, window);
	levelRunner->runLevel(map);
	return 0;
}