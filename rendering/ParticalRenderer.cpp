//
// Created by Robert JONES on 2017/08/15.
//

#include <random>
#include "ParticalRenderer.hpp"
#include "../error_handling/printError.hpp"
#include "../extras/Maths.hpp"

const std::vector<float> vert = {
        // position             //UV
		1.0f, 1.0f, 0.0f,     1.0,1.0,
		-1.0f, 1.0f, 0.0f,    0, 1,
		-1.0f, -1.0f, 0.0f,   0,0,
		1.0f, -1.0f, 0.0f,    1, 0,
};

const std::vector<unsigned int> ind = {
		0, 1, 3,
		1, 2, 3
};

cge::ParticalRenderer::ParticalRenderer(cge::GLSLProgram &shader) : plane(vert, ind, true),
																	_shader(shader)
{}

void cge::ParticalRenderer::prepare() const
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void cge::ParticalRenderer::render(Partical &partical, Camera &cam)
{
	_shader.start();
	prepare();
	cam.update();
	glBindVertexArray(plane.getVao());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, partical.getTexture().getID());
	glm::mat4	model(1.0f);

	model = glm::translate(model, partical.getPosition());
	glm::mat4 view = cam.getViewMatrix();
	model[0][0] = view[0][0];
	model[0][1] = view[1][0];
	model[0][2] = view[2][0];
	model[1][0] = view[0][1];
	model[1][1] = view[1][1];
	model[1][2] = view[2][1];
	model[2][0] = view[0][2];
	model[2][1] = view[1][2];
	model[2][2] = view[2][2];
	model = glm::scale(model, glm::vec3(partical.getScale(), partical.getScale(), partical.getScale()));
	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("modelview"), view * model);
	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("projection"), cam.getProjectionMatrix());
	this->_shader.uploadvec2d(this->_shader.getUniformLocation("currTextureOff"), partical.get_currOff());
	this->_shader.uploadvec2d(this->_shader.getUniformLocation("nextTextureOff"), partical.get_nextOff());
	this->_shader.uploadFloat(this->_shader.getUniformLocation("blend"), partical.get_blend());
	this->_shader.uploadFloat(this->_shader.getUniformLocation("row"), partical.getTexture().getRow());
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vert.size()), GL_UNSIGNED_INT, 0);
	getGLError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	_shader.end();
}

void cge::ParticalRenderer::addPartical(cge::Partical partical)
{
	_partiacals.push_back(partical);
}

void cge::ParticalRenderer::render(cge::Camera &camera)
{
	for (auto &partical : _partiacals)
	{
		render(partical, camera);
	}
}

void cge::ParticalRenderer::update(unsigned lastframe)
{
	for (std::vector<cge::Partical>::iterator partical = _partiacals.begin(); partical != _partiacals.end();)
	{
		if (!partical->update(lastframe))
		{
			_partiacals.erase(partical);
		} else
			partical++;
	}
}

void cge::ParticalRenderer::updateRender(cge::Camera &camera, unsigned lastframe)
{
	for (std::vector<cge::Partical>::iterator partical = _partiacals.begin(); partical != _partiacals.end();)
	{
		if (!partical->update(lastframe))
		{
			_partiacals.erase(partical);
		} else
		{
			render(*partical, camera);
			partical++;
		}
	}

}

void cge::ParticalRenderer::partivalEffect(glm::vec3 position, glm::vec3 positionTolorence,
										   glm::vec3 verlocity, glm::vec3 verlocityTolorence,
										   float gravityeffect, float gravertyTolerance, float lifetime,
										   float lifetimeTolorence, float scale, float scaleTolorence, int numParticals, TextureAtlas texture)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dispx(position.x - positionTolorence.x, position.x + positionTolorence.x);
	std::uniform_real_distribution<float> dispy(position.y - positionTolorence.y, position.y + positionTolorence.y);
	std::uniform_real_distribution<float> dispz(position.z - positionTolorence.z, position.z + positionTolorence.z);
	std::uniform_real_distribution<float> disvx(verlocity.x - verlocityTolorence.x, verlocity.x + verlocityTolorence.x);
	std::uniform_real_distribution<float> disvy(verlocity.y - verlocityTolorence.y, verlocity.y + verlocityTolorence.y);
	std::uniform_real_distribution<float> disvz(verlocity.z - verlocityTolorence.z, verlocity.z + verlocityTolorence.z);
	gravertyTolerance = (gravertyTolerance < 0) ? 0 : ((gravertyTolerance > 1) ? 1 : gravertyTolerance);
	std::uniform_real_distribution<float> disgrv(gravityeffect - gravertyTolerance, gravityeffect + gravertyTolerance);
	std::uniform_real_distribution<float> dislife(lifetime - lifetimeTolorence, lifetime + lifetimeTolorence);
	std::uniform_real_distribution<float> disscale(scale - scaleTolorence, scale + scaleTolorence);

	for (int i = 0; i < numParticals ; ++i)
	{
		position.x = dispx(gen);
		position.y = dispy(gen);
		position.z = dispz(gen);

		verlocity.x = disvx(gen);
		verlocity.y = disvy(gen);
		verlocity.z = disvz(gen);

		gravityeffect = disgrv(gen);

		lifetime = dislife(gen);

		scale = disscale(gen);

		_partiacals.emplace_back(position, verlocity, gravityeffect, lifetime, scale, texture);

	}


}