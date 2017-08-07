//
// Created by rojones on 2017/08/07.
//

#include "Being.h"

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, std::string &modelPath,
			 std::string &texturePath, cge::Loader &loader, float speed, std::string fragmenPath, std::string vertexPath):
		Entity(position, rotation, scale, (cge::Model(modelPath, texturePath, loader))),
		_speed(speed),
		_shader(fragmenPath, vertexPath),
		_renderer(_shader)
{
	this->_n_moveDir = glm::vec2(0,0);
}

void Being::update( unsigned lastFrameTime)
{
	_position = _position + (lastFrameTime * _speed * _n_moveDir);
}

void Being::render() {
	_shader.start();
	_renderer.prepare();
	_renderer.render((cge::Entity&)this->getModel());
	_shader.end();
}
