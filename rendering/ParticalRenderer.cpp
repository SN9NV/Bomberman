//
// Created by Robert JONES on 2017/08/15.
//

#include <random>
#include "ParticalRenderer.hpp"
#include "../error_handling/printError.hpp"
#include "../extras/Maths.hpp"

const std::vector<float> vert = {
		// position             //UV
		1.0f, 1.0f, 0.0f, 1.0, 1.0,
		-1.0f, 1.0f, 0.0f, 0, 1,
		-1.0f, -1.0f, 0.0f, 0, 0,
		1.0f, -1.0f, 0.0f, 1, 0,
};

const std::vector<unsigned int> ind = {
		0, 1, 3,
		1, 2, 3
};

cge::ParticalRenderer::ParticalRenderer(cge::GLSLProgram &shader) :
		plane(vert, ind, true),
		_shader(shader)
{
	glBindVertexArray(plane.getVao());
	glGenBuffers(1, &_instanceVBO);

	glBindVertexArray(0);
}

void cge::ParticalRenderer::prepare() const {
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void cge::ParticalRenderer::render(Partical &partical, Camera &cam) {
	_shader.begin();
	prepare();
	cam.update();
	glBindVertexArray(plane.getVao());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, partical.getTexture().getID());
	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("modelview"), viewModelMatrix(partical, cam));
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

void cge::ParticalRenderer::addPartical(cge::Partical partical, GLenum specFac, GLenum deffFac) {
	auto find = _partiacals.find(partical.getTexture().getID());
	if (find != _partiacals.end()) {
		find->second.partical.push_back(partical);
		find->second.specFac = specFac;
		find->second.deffFac = deffFac;
	} else {
		s_ParticalBlend tmp = (s_ParticalBlend) {std::vector<Partical>({partical}), specFac, deffFac};
		_partiacals.emplace(partical.getTexture().getID(), tmp);
		std::cout << "partical texture not found\n";
	}
}

void cge::ParticalRenderer::render(cge::Camera &camera) {
	camera.update();
	_shader.begin();
	prepare();
	glBindVertexArray(plane.getVao());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);


	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("projection"),
								 camera.getProjectionMatrix());
	for (auto &particalList : _partiacals) {
		if (!particalList.second.partical.empty()) {
			glBindTexture(GL_TEXTURE_2D, particalList.first);
			glBlendFunc(particalList.second.specFac, particalList.second.deffFac);
			this->_shader.uploadFloat(this->_shader.getUniformLocation("row"),
									  particalList.second.partical[0].getTexture().getRow());
			std::vector<s_InctenceData> inctenceData(particalList.second.partical.size());
			size_t index = 0;
			for (auto &partical : particalList.second.partical) {
				glm::mat4 mv = viewModelMatrix(partical, camera);
				inctenceData[index].modelview = mv;
				inctenceData[index].currTextureOff = partical.get_currOff();
				inctenceData[index].nextTextureOff = partical.get_nextOff();
				inctenceData[index].blend = partical.get_blend();
				index++;
			}
			glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(s_InctenceData) * inctenceData.size(), inctenceData.data(),
						 GL_STREAM_DRAW);
			GLsizei dataSize = sizeof(struct s_InctenceData);
			GLsizei vec4Size = sizeof(glm::vec4);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) (offsetof(struct s_InctenceData, modelview)));
			glVertexAttribDivisor(2, 1);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) (offsetof(struct s_InctenceData, modelview) + vec4Size));
			glVertexAttribDivisor(3, 1);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) (offsetof(struct s_InctenceData, modelview) + 2 * vec4Size));
			glVertexAttribDivisor(4, 1);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) (offsetof(struct s_InctenceData, modelview) + 3 * vec4Size));
			glVertexAttribDivisor(5, 1);
			glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) offsetof(struct s_InctenceData, currTextureOff));
			glVertexAttribDivisor(6, 1);
			glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, dataSize,
								  (void *) offsetof(struct s_InctenceData, nextTextureOff));
			glVertexAttribDivisor(7, 1);
			glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, dataSize, (void *) offsetof(struct s_InctenceData, blend));
			glVertexAttribDivisor(8, 1);
			glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(vert.size()), GL_UNSIGNED_INT, 0,
									static_cast<GLsizei>(index));
			getGLError();

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glDisableVertexAttribArray(7);
	glDisableVertexAttribArray(8);

	glBindVertexArray(0);
	_shader.end();
}

void cge::ParticalRenderer::update(unsigned lastframe, Camera camera) {
	camera.update();

	for (auto &particleList : _partiacals) {
		for (auto particle = particleList.second.partical.begin();
			 particle != particleList.second.partical.end();) {
			if (particle->update(lastframe, camera)) {
				particle++;
			} else {
				particleList.second.partical.erase(particle);
			}
		}

		std::sort(particleList.second.partical.begin(), particleList.second.partical.end(),
			[](cge::Partical p1, cge::Partical p2) {
				return (p1.getDistCamSqur() > p2.getDistCamSqur());
			}
		);
	}
}

void cge::ParticalRenderer::updateRender(cge::Camera &camera, unsigned lastframe) {
	update(lastframe, camera);
	render(camera);
}

void cge::ParticalRenderer::particleEffect(particle_t p) {

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dispx(p.position.x - p.positionTolerance.x, p.position.x + p.positionTolerance.x);
	std::uniform_real_distribution<float> dispy(p.position.y - p.positionTolerance.y, p.position.y + p.positionTolerance.y);
	std::uniform_real_distribution<float> dispz(p.position.z - p.positionTolerance.z, p.position.z + p.positionTolerance.z);
	std::uniform_real_distribution<float> disvx(p.velocity.x - p.velocityTolerance.x, p.velocity.x + p.velocityTolerance.x);
	std::uniform_real_distribution<float> disvy(p.velocity.y - p.velocityTolerance.y, p.velocity.y + p.velocityTolerance.y);
	std::uniform_real_distribution<float> disvz(p.velocity.z - p.velocityTolerance.z, p.velocity.z + p.velocityTolerance.z);
	p.gravityTolerance = cge::Maths::clamp(p.gravityTolerance, 0.0f, 1.0f);
	std::uniform_real_distribution<float> disgrv(p.gravityEffect - p.gravityTolerance, p.gravityEffect + p.gravityTolerance);
	std::uniform_real_distribution<float> dislife(p.lifetime - p.lifetimeTolerance, p.lifetime + p.lifetimeTolerance);
	std::uniform_real_distribution<float> disscale(p.scale - p.scaleTolerance, p.scale + p.scaleTolerance);
	std::uniform_real_distribution<float> disrot(p.rotation - p.rotationTolerance, p.rotation + p.rotationTolerance);
	std::uniform_real_distribution<float> disspin(p.spin - p.spinTolerance, p.spin + p.spinTolerance);

	for (size_t i = 0; i < p.numParticles; i++) {
		p.position.x = dispx(gen);
		p.position.y = dispy(gen);
		p.position.z = dispz(gen);

		p.velocity.x = disvx(gen);
		p.velocity.y = disvy(gen);
		p.velocity.z = disvz(gen);

		p.gravityEffect = disgrv(gen);
		p.lifetime = dislife(gen);
		p.scale = disscale(gen);
		p.rotation = disrot(gen);
		p.spin = disspin(gen);
		addPartical(Partical(p.position, p.velocity, p.gravityEffect, p.lifetime, p.scale, p.rotation, p.spin, p.texture), p.specularFactor, p.diffuseFactor);
	}
}

glm::mat4 cge::ParticalRenderer::viewModelMatrix(cge::Partical partical, Camera camera) {
	glm::mat4 model(1.0f);

	model = glm::translate(model, partical.getPosition());
	glm::mat4 view = camera.getViewMatrix();
	model[0][0] = view[0][0];
	model[0][1] = view[1][0];
	model[0][2] = view[2][0];
	model[1][0] = view[0][1];
	model[1][1] = view[1][1];
	model[1][2] = view[2][1];
	model[2][0] = view[0][2];
	model[2][1] = view[1][2];
	model[2][2] = view[2][2];
	model = glm::rotate(model, partical.getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(partical.getScale(), partical.getScale(), partical.getScale()));
	return glm::mat4(view * model);
}

void cge::ParticalRenderer::clearParticals() {
	for (auto &pstruct : _partiacals) {
		pstruct.second.partical.clear();
		pstruct.second.partical.resize(0);
	}

}

void cge::ParticalRenderer::addParticalTexture(cge::TextureAtlas texture, GLenum specFac, GLenum deffFac) {
	auto find = _partiacals.find(texture.getID());
	if (find == _partiacals.end()) {
		s_ParticalBlend tmp = (s_ParticalBlend) {std::vector<Partical>({}), specFac, deffFac};
		_partiacals.emplace(texture.getID(), tmp);
	}
}
