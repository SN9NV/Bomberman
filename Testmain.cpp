#include "io/Window.hpp"
#include "loaders/Loader.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"
#include "shared.hpp"
#include "rendering/ParticalRenderer.hpp"
#include "BomberManGameLogic/Player.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

int main()
{
	cge::Window			window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GameState		gameState = cge::GameState::PLAY_MENU;
	cge::InputManager	inputManager(window);
	cge::GLSLProgram	shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	cge::Camera 		camera(glm::vec3(0.8f, 1.6f, 1.75f), glm::vec3(0.5f, -0.4f, 0.0f), window);
	cge::Renderer		renderer(shader);
	cge::Loader			loader;

	cge::Model	bomberModel = cge::Model("resources/models/Bomber.glb", "resources/models/BomberManTextureDiffuseColor.png", loader);
	Player		player({ 0, 0, 0 }, { 0, 90, 0 }, 1, bomberModel, 1.0f);
	Player		player1({ 0, 0, -5 }, { 0, 0, 0 }, 1, bomberModel, 1.0f);
	Player		player2({ 0, 0, -10 }, { 0, 0, 0 }, 1, bomberModel, 1.0f);


	while (gameState != cge::WANTS_QUIT)
	{
		inputManager.pollKeyEvnt();
		if (inputManager.isExitCase())
			gameState = cge::WANTS_QUIT;
		if (inputManager.isKeyPressed(GLFW_KEY_W))
		{
			camera.setPosition({camera.getPosition().x, camera.getPosition().y + .5, camera.getPosition().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_S))
		{
			camera.setPosition({camera.getPosition().x, camera.getPosition().y - .5, camera.getPosition().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_D))
		{
			camera.setPosition({camera.getPosition().x + .5, camera.getPosition().y, camera.getPosition().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_A))
		{
			camera.setPosition({camera.getPosition().x - .5, camera.getPosition().y, camera.getPosition().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_Q))
		{
			camera.setPosition({camera.getPosition().x, camera.getPosition().y, camera.getPosition().z + .5});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_E))
		{
			camera.setPosition({camera.getPosition().x, camera.getPosition().y, camera.getPosition().z - .5});
		}

		shader.start();
			player.update(inputManager, shader, window.getFrameTime());
			player1.update(inputManager, shader, window.getFrameTime());
			player2.update(inputManager, shader, window.getFrameTime());

			renderer.prepare();
			camera.update(shader);

			renderer.render(player);
			renderer.render(player1);
			renderer.render(player2);
		shader.end();

		window.swapBuffers();
	}


	return 0;
}