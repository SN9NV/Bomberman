//
// Created by rojones on 2017/08/07.
//

#ifndef BOMBERMAN_BEING_HPP
#define BOMBERMAN_BEING_HPP


#include "../entites/Entity.hpp"
#include "../io/InputManager.hpp"
#include "../rendering/Renderer.hpp"

class Being : public cge::Entity
{
private:
	glm::vec2 _n_moveDir;
	float _speed;
	cge::GLSLProgram	_shader;
	cge::Renderer		_renderer;
public:
	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, std::string &modlePath, std::string &texturePath, cge::Loader &loader,
		  float speed, std::string fragmenPath, std::string vertexPath);
	void update(unsigned lastFrameTime);
	void render();
};


#endif //BOMBERMAN_BEING_HPP
