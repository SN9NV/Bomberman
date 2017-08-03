#include "Window.hpp"
#include "Loader.hpp"
#include "GLSLProgram.hpp"
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Maths.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "tinyGLTF/tiny_gltf.h"

static constexpr unsigned HEIGHT = 720;
static constexpr unsigned WIDTH = 1024;

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

std::ostream &operator<<(std::ostream &out, const std::vector<tinygltf::Mesh> &meshes) {
	unsigned i = 0;

	out << "Meshes: " << meshes.size();

	for (auto &mesh : meshes) {
		out << "Mesh: " << i++ << "\n";
		out << "Name: " << mesh.name << "\n";
//		out << "Primitives:\n" << mesh.primitives << "\n";
//		out << "Weights:\n" << mesh.weights << "\n";
//		out << ""
	}

	return out;
}

typedef struct { GLuint vb; } GLBufferState;

typedef struct {
	std::map<std::string, GLuint> attribs;
	std::map<std::string, GLuint> uniforms;
} GLProgramState;

std::map<int, GLBufferState> gBufferState;
GLProgramState gGLProgramState;

void	drawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh) {
	for (auto &primitive : mesh.primitives) {
		if (primitive.indices < 0)
			return;

		for (auto &attr : primitive.attributes) {
			assert(attr.second >= 0);

			const auto &accessor = model.accessors[attr.second];

			glBindBuffer(GL_ARRAY_BUFFER, gBufferState[accessor.bufferView].vb);

			int size;

			switch (accessor.type) {
				case TINYGLTF_TYPE_SCALAR:
					size = 1;
					break;
				case TINYGLTF_TYPE_VEC2:
					size = 2;
					break;
				case TINYGLTF_TYPE_VEC3:
					size = 3;
					break;
				case TINYGLTF_TYPE_VEC4:
					size = 4;
					break;
				default:
					size = 1;
			}

			if (attr.first == "POSITION" || attr.first == "NORMAL" || attr.first == "TEXCOORD_0") {
					glVertexAttribPointer(
							gGLProgramState.attribs[attr.first],
							size,
							(GLenum)accessor.componentType,
							(GLboolean)((accessor.normalized) ? GL_TRUE : GL_FALSE),
							(GLsizei)model.bufferViews[accessor.bufferView].byteStride,
							BUFFER_OFFSET(accessor.byteOffset)
					);

					glEnableVertexAttribArray(gGLProgramState.attribs[attr.first]);
			}
		}

		const auto &indexAssessor = model.accessors[primitive.indices];
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gBufferState[indexAssessor.bufferView].vb);

		GLenum mode;

		switch (primitive.mode) {
			case TINYGLTF_MODE_TRIANGLES:
				mode = GL_TRIANGLES;
				break;
			case TINYGLTF_MODE_TRIANGLE_STRIP:
				mode = GL_TRIANGLE_STRIP;
				break;
			case TINYGLTF_MODE_TRIANGLE_FAN:
				mode = GL_TRIANGLE_FAN;
				break;
			case TINYGLTF_MODE_POINTS:
				mode = GL_POINTS;
				break;
			case TINYGLTF_MODE_LINE:
				mode = GL_LINE;
				break;
			case TINYGLTF_MODE_LINE_LOOP:
				mode = GL_LINE_LOOP;
				break;
			default:
				mode = GL_TRIANGLES;
		}

		glDrawElements(mode, (GLsizei)indexAssessor.count, (GLenum)indexAssessor.componentType,
			BUFFER_OFFSET(indexAssessor.byteOffset));

		for (auto &attr : primitive.attributes) {
			if (attr.first == "POSITION" || attr.first == "NORMAL" || attr.first == "TEXCOORD_0") {
				glDisableVertexAttribArray(gGLProgramState.attribs[attr.first]);
			}
		}
	}
}

void	setupMeshState(tinygltf::Model &model, GLSLProgram &shader) {
	unsigned i = 0;

	for (const auto &view : model.bufferViews) {
		if (view.target == 0) {
			continue;
		}

		const tinygltf::Buffer &buffer = model.buffers[view.buffer];

		GLBufferState state = {};

		glGenBuffers(1, &state.vb);
		glBindBuffer((GLenum)view.target, state.vb);

		glBufferData((GLenum)view.target, view.byteLength, buffer.data.data() + view.byteOffset, GL_STATIC_DRAW);
		glBindBuffer((GLenum)view.target, 0);

		gBufferState[i++] = state;
	}

	shader.start();
//	gGLProgramState.uniforms["isCurvesLoc"] = (GLuint)shader.getUniformLocation("uIsCurves");
	shader.end();
}

void	drawNode(tinygltf::Model &model, const tinygltf::Node &node) {
	drawMesh(model, model.meshes[(node.mesh >= 0) ? node.mesh : 0]);
}

void	drawModel(tinygltf::Model &model) {
	const tinygltf::Scene &scene = model.scenes[model.defaultScene];
	for (auto &node : scene.nodes) {
		drawNode(model, model.nodes[node]);
	}
}

bool	processInput(InputManager &inputManager);

int main() {
	Window			window("Bomberman", WIDTH, HEIGHT, Window::Flags::VSYNC_ENABLED);
	GLSLProgram		shader;
	InputManager	inputManager;


	tinygltf::Model model;
	tinygltf::TinyGLTF glTFLoader;
	std::string err;

	bool ret = glTFLoader.LoadBinaryFromFile(&model, &err, "../resources/moddels/bomner2.glb");

	if (!err.empty()) {
		std::cout << "Err: " << err << "\n";
	}

	if (!ret) {
		std::cout << "Failed to parse glTF\n";
		return -1;
	}

	if (shader.compileShaders("../Testvertex.glsl", "../Textfragment.glsl")) {
		exit(1);
	}

	Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	enum GameState {
		PLAY,
		WANTS_QUIT
	};

	int gameState = GameState::PLAY;
	setupMeshState(model, shader);

	while (gameState != GameState::WANTS_QUIT) {
		if (processInput(inputManager)) {
			gameState = GameState ::WANTS_QUIT;
		}

		shader.start();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		camera.update(inputManager, shader);

		drawModel(model);

		shader.end();
		window.swapBuffers();
	}

	return 0;
}

bool processInput(InputManager &inputManager) {
	SDL_Event	event = {};

	while (SDL_PollEvent(&event) > 0) {
		switch (event.type) {
			case SDL_QUIT:
				return true;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					inputManager.pressKey(event.key.keysym.sym);
				}

				break;
			case SDL_KEYUP:
				inputManager.releaseKey(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}

	return inputManager.isKeyPressed(SDLK_ESCAPE);

}

