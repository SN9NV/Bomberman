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
	BomberMan = (cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							loader));
	player = new Player({0, 0, 0}, {0, 0, 0}, 1, BomberMan, 0.25f, 0.01f);
	player->setDamage(3);
	levelRunner = new LevelRunner(loader,player, window);
	int exit_state = levelRunner->runLevel("../resources/Maps/Map1");
	std::cout << "level exit state " << exit_state << std::endl;
	return 0;
}