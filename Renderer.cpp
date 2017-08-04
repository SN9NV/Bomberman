#include "Renderer.hpp"
#include "Maths.hpp"

Renderer::Renderer(const GLSLProgram &shader) :
	_shader(shader) { }

void Renderer::prepare() const {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void Renderer::render(const Entity &entity) const {
	const Model	&model = entity.getModel();

	// Bind the model and texture
	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Upload the model's transformation matrix
	glm::mat4	transformation = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("transformation"), transformation);

	// Draw the triangles
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);

	// Unbind everything
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}