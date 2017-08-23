#include "io/Window.hpp"
#include "rendering/GLSLProgram.hpp"
#include "rendering/Renderer.hpp"
#include "entites/Camera.hpp"
#include "extras/Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "shared.hpp"
#include "rendering/ParticalRenderer.hpp"
#include "BomberManGameLogic/Player.hpp"
#include "rendering/TextRenderer.hpp"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

int main() {
	cge::Window window("Bomberman", WIDTH, HEIGHT, cge::Window::Flags::VSYNC_ENABLED);
	cge::GameState gameState = cge::GameState::PLAY_MENU;
	cge::InputManager inputManager(window);
	cge::GLSLProgram shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	cge::GLSLProgram pshader("shaders/particalVertex.glsl", "shaders/particalFragment.glsl");
	cge::Camera camera(glm::vec3(0.8f, 1.6f, 1.75f), glm::vec3(0.5f, -0.4f, 0.0f), window);
	cge::Renderer renderer(shader);
	cge::Loader loader;
	cge::ParticalRenderer prender(pshader);
	cge::Model bomberModel = cge::Model("resources/models/Bomber.glb",
										"resources/models/BomberManTextureDiffuseColor.png", loader);
	cge::TextRenderer textrender;
	//Player player({0, 0, 0}, {0, 90, 0}, 1, bomberModel,loader, 1.0f);

	inputManager.setInputCallBacks();
	cge::TextureAtlas t = loader.loadTextureAtlas("resources/TextureAtlas/FireBallAtlas.png", 4);
	glm::vec3 camOff = {0, 1, 5};
	//player.update(inputManager, shader, window.getFrameTime());
	//camera.setTrackEntity(player);
//	prender.partivalEffectPos({0, 0, 0}, {0.5, .5, 0.5},
//						   {0, 0, 0.00}, {0, 0.01, 0}, 0, 0.00, 5000, 5000, 0.4, 0.1, 0, 0, 0.0,
//						   0.0, 20, t, GL_SRC_ALPHA, GL_ONE);
	prender.addPartical(cge::Partical({0,0,0},{0,0,0}, 0,100000,1,0,0,t), GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	prender.addPartical(cge::Partical({0,0,0.005},{0,0.001,0}, 0,100000,1,0,0,t), GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (gameState != cge::WANTS_QUIT) {
		inputManager.pollKeyEvnt();
		if (inputManager.isExitCase() || inputManager.isKeyPressed(GLFW_KEY_ESCAPE))
			gameState = cge::WANTS_QUIT;
		if (inputManager.isKeyPressed(GLFW_KEY_W)) {
			//camera.setPosition({camera.getPosition().x, camera.getPosition().y + .5, camera.getPosition().z});
			camOff.y += .5;
		}
		if (inputManager.isKeyPressed(GLFW_KEY_S)) {
			//camera.setPosition({camera.getPosition().x, camera.getPosition().y - .5, camera.getPosition().z});
			camOff.y -= .5;
		}
		if (inputManager.isKeyPressed(GLFW_KEY_D)) {
			//camera.setPosition({camera.getPosition().x + .5, camera.getPosition().y, camera.getPosition().z});
			camOff.x += .5;
		}
		if (inputManager.isKeyPressed(GLFW_KEY_A)) {
			//camera.setPosition({camera.getPosition().x - .5, camera.getPosition().y, camera.getPosition().z});
			camOff.x -= .5;
		}
		if (inputManager.isKeyPressed(GLFW_KEY_Q)) {
			//camera.setPosition({camera.getPosition().x, camera.getPosition().y, camera.getPosition().z + .5});
			camOff.z += .5;
		}
		if (inputManager.isKeyPressed(GLFW_KEY_E)) {
			//camera.setPosition({camera.getPosition().x, camera.getPosition().y, camera.getPosition().z - .5});
			camOff.z -= .5;
		}
//std::cout << camOff.x << " " << camOff.y << " " << camOff.z << std::endl;
		shader.start();


		camera.setTrackOffset(camOff);
		renderer.prepare();
		camera.update(shader);

	//	renderer.render(player);
		shader.end();
//		prender.render(camera);
		prender.updateRender(camera, window.getFrameTime());
		textrender;
		window.swapBuffers();
	}


	return 0;
}