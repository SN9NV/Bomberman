//
// Created by Robert JONES on 2017/08/08.
//

#include <string>
#include <iostream>
#include <vector>
#include "../entites/Entity.hpp"
#include "../io/Window.hpp"
#include "../rendering/Renderer.hpp"
#include "../entites/Camera.hpp"
#include "Player.hpp"

void loadModls(std::map<std::string, cge::Model> &models, cge::Loader &loader)
{
	models.emplace("Wall",
				   cge::Model("../resources/models/Wall.glb", "../resources/models/SolidWallDiffuseColor.png", loader));
	models.emplace("DestructWall", cge::Model("../resources/models/DestructWall.glb",
											  "../resources/models/DestructWallDiffuseColor.png", loader));
	models.emplace("Bomb",
				   cge::Model("../resources/models/Bomb.glb", "../resources/models/BombDiffuseColor.png", loader));
	models.emplace("Bomber",
				   cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							  loader));
}

cge::Model *getModel(std::map<std::string, cge::Model> &models, std::string name)
{
	auto found = models.find(name);
	if (found != models.end())
		return (&found->second);
	return (nullptr);
}

void runLevel(std::string &levelPath, cge::Loader &loader, cge::Window window)
{
	//std::cout << levelPath << "\n";
	(void) levelPath;
	std::vector<cge::Entity *> entities;
	std::map<std::string, cge::Model> models;
	loadModls(models, loader);
	cge::Model *tmpmdl;
	Player *player;

	cge::GLSLProgram shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	cge::InputManager inputManager;
	cge::Renderer renderer(shader);
	cge::Camera camera(glm::vec3(0.0f, 5.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), window);
	enum GameState
	{
		PLAY,
		WANTS_QUIT
	};

	int levelState = GameState::PLAY;
	if ((tmpmdl = getModel(models, "Wall")) != nullptr)
	{
		entities.push_back(new cge::Entity({0, 0, 0}, {0, 0, 0}, 1, *tmpmdl));
		entities.push_back(new cge::Entity({4, 0, 0}, {0, 0, 0}, 1, *tmpmdl));
		entities.push_back(new cge::Entity({-4, 0, 0}, {0, 0, 0}, 1, *tmpmdl));
		entities.push_back(new cge::Entity({0, 0, -4}, {0, 0, 0}, 1, *tmpmdl));
	}
	if ((tmpmdl = getModel(models, "Bomber")) != nullptr)
	{
		player = new Player({0, 0, 4}, {0, 0, 0}, 1, *tmpmdl, 0.04f);
		entities.push_back(player);
	}
std::cout << "loaded bomber" << std::endl;
	while (levelState != GameState::WANTS_QUIT)
	{
		inputManager.poolKeyEvnt();
		if (inputManager.isExitCase() || inputManager.isKeyPressed(SDLK_ESCAPE))
		{
			levelState = GameState::WANTS_QUIT;
		}
		player->update(inputManager, 1);
		shader.start();
		renderer.prepare();
		camera.update(shader);
		for (auto &entitie : entities)
		{
			renderer.render(*entitie);
		}
		shader.end();
		window.swapBuffers();
	}
}