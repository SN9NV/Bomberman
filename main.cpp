#include <iostream>

#include "MainGame.hpp"

constexpr unsigned	WIDTH = 1024;
constexpr unsigned	HEIGHT = 768;

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	MainGame	mainGame(std::string("Bomberman"), WIDTH, HEIGHT);

	mainGame.startGameLoop();

/*	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	GLuint	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint	ProgramID = LoadShaders("../shaders/vertexshader.vsh", "../shaders/fragmentshader.fsh");

	do {
		// Clear screen
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw something
		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   0,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,			// size
		   GL_FLOAT,	// type
		   GL_FALSE,	// normalized?
		   0,			// stride
		   (void*)0		// array buffer offset
		);

		glUseProgram(ProgramID);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
	} while ();

	glfwTerminate();

	return 0; */
}
