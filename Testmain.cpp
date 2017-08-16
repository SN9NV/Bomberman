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

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

int main()
{
	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GameState gameState = cge::GameState::PLAY_MENU;
	cge::InputManager inputManager(window);
	cge::GLSLProgram shader("../shaders/particalVertex.glsl", "../shaders/particalFragment.glsl");
	cge::Camera camera(glm::vec3(0.0f, 0.0f, 10.0f),
					   glm::vec3(0.0f, 0.0f, 0.0f), window);
	cge::ParticalRenderer prender(shader);
	prender.addPartical(cge::Partical({0,0,0},{0,0,0}, 0, 10000, 1));
	prender.addPartical(cge::Partical({1,0,0},{0,0,0}, 0, 10000, 4));
	prender.addPartical(cge::Partical({-1,0,0},{0,0,0}, 0, 10000, 0.5));
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

		if (inputManager.isKeyPressed(GLFW_KEY_SPACE))
			prender.partivalEffect({0, 0, 0},{2,2,2}, {0, 0, 0},{0.01,0.0,0}, 0.1,0.00, 5000, 500, 1,1, 5);
		if (inputManager.isKeyPressed(GLFW_KEY_P))
			prender.addPartical(cge::Partical({0, 0, 0}, {0, .25f, 0}, 0.1, 5000, 1));

		if (inputManager.isKeyPressed(GLFW_KEY_KP_7))
		{
			camera.setRotation({camera.getRotation().x + 0.01, camera.getRotation().y, camera.getRotation().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_KP_4))
		{
			camera.setRotation({camera.getRotation().x - 0.01, camera.getRotation().y, camera.getRotation().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_KP_8))
		{
			camera.setRotation({camera.getRotation().x, camera.getRotation().y + 0.01, camera.getRotation().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_KP_5))
		{
			camera.setRotation({camera.getRotation().x, camera.getRotation().y - 0.01, camera.getRotation().z});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_KP_9))
		{
			camera.setRotation({camera.getRotation().x, camera.getRotation().y, camera.getRotation().z + 0.01});
		}
		if (inputManager.isKeyPressed(GLFW_KEY_KP_6))
		{
			camera.setRotation({camera.getRotation().x, camera.getRotation().y, camera.getRotation().z - 0.01});
		}
		prender.prepare();
		prender.updateRender(camera, window.getFrameTime());
		window.swapBuffers();
	}


	return 0;
}