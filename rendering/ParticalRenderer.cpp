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

cge::ParticalRenderer::ParticalRenderer(cge::GLSLProgram &shader) : plane(vert, ind, true),
																	_shader(shader) {
	glBindVertexArray(plane.getVao());
	glGenBuffers(1, &_instanceVBO);

	glBindVertexArray(0);
}

void cge::ParticalRenderer::prepare() const {
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void cge::ParticalRenderer::render(Partical &partical, Camera &cam) {
	_shader.start();
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
	_shader.start();
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
				std::cout << "Partical: " << index << std::endl;
				glm::mat4 mv = viewModelMatrix(partical, camera);
				inctenceData[index].modelview = mv;
				inctenceData[index].currTextureOff = partical.get_currOff();
				std::cout << "coff: " << partical.get_currOff().x << " " << partical.get_currOff().y << std::endl;
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

	glBindVertexArray(0);
	_shader.end();
}

void cge::ParticalRenderer::update(unsigned lastframe, Camera camera) {
	camera.update();
	for (auto &particalList : _partiacals) {
		for (std::vector<cge::Partical>::iterator partical = particalList.second.partical.begin();
			 partical != particalList.second.partical.end();) {
			if (partical->update(lastframe, camera)) {
				partical++;
			} else {
				particalList.second.partical.erase(partical);
			}
		}
		std::sort(particalList.second.partical.begin(), particalList.second.partical.end(),
				  [](cge::Partical p1, cge::Partical p2) {
					  return (p1.getDistCamSqur() > p2.getDistCamSqur());
				  });
	}
}

void cge::ParticalRenderer::updateRender(cge::Camera &camera, unsigned lastframe) {
	update(lastframe, camera);
	render(camera);
}

void cge::ParticalRenderer::partivalEffect(glm::vec3 position, glm::vec3 positionTolorence,
										   glm::vec3 verlocity, glm::vec3 verlocityTolorence,
										   float gravityeffect, float gravertyTolerance,
										   float lifetime, float lifetimeTolorence,
										   float scale, float scaleTolorence,
										   float rotation, float rotationTolorence,
										   float spin, float spinTolorence,
										   size_t numParticals,
										   TextureAtlas texture, GLenum specFac, GLenum deffFac) {

	/*std::random_device rd;
	std::mt19937 gen(rd());*/
	std::default_random_engine gen;
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
	std::uniform_real_distribution<float> disrot(rotation - rotationTolorence, rotation + rotationTolorence);
	std::uniform_real_distribution<float> disspin(spin - spinTolorence, spin + spinTolorence);

	/*std::normal_distribution<float> dispx(position.x - positionTolorence.x, position.x + positionTolorence.x);
	std::normal_distribution<float> dispy(position.y - positionTolorence.y, position.y + positionTolorence.y);
	std::normal_distribution<float> dispz(position.z - positionTolorence.z, position.z + positionTolorence.z);
	std::normal_distribution<float> disvx(verlocity.x - verlocityTolorence.x, verlocity.x + verlocityTolorence.x);
	std::normal_distribution<float> disvy(verlocity.y - verlocityTolorence.y, verlocity.y + verlocityTolorence.y);
	std::normal_distribution<float> disvz(verlocity.z - verlocityTolorence.z, verlocity.z + verlocityTolorence.z);
	gravertyTolerance = (gravertyTolerance < 0) ? 0 : ((gravertyTolerance > 1) ? 1 : gravertyTolerance);
	std::normal_distribution<float> disgrv(gravityeffect - gravertyTolerance, gravityeffect + gravertyTolerance);
	std::normal_distribution<float> dislife(lifetime - lifetimeTolorence, lifetime + lifetimeTolorence);
	std::normal_distribution<float> disscale(scale - scaleTolorence, scale + scaleTolorence);
	std::normal_distribution<float> disrot(rotation - rotationTolorence, rotation + rotationTolorence);
	std::normal_distribution<float> disspin(spin - spinTolorence, spin + spinTolorence);*/

	for (size_t i = 0; i < numParticals; ++i) {
		position.x = dispx(gen);
		position.y = dispy(gen);
		position.z = dispz(gen);

		verlocity.x = disvx(gen);
		verlocity.y = disvy(gen);
		verlocity.z = disvz(gen);

		gravityeffect = disgrv(gen);
		lifetime = dislife(gen);
		scale = disscale(gen);
		rotation = disrot(gen);
		spin = disspin(gen);
		addPartical(Partical(position, verlocity, gravityeffect, lifetime, scale, rotation, spin, texture), specFac,
					deffFac);

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
