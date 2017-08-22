//
// Created by rojones on 2017/08/09.
//

#include "Balloon.hpp"

std::uniform_int_distribution<int> _ndisision(0, 1);
std::uniform_int_distribution<int> _nchange(0, 3);
std::default_random_engine gen;

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader)
		: Being(position, rotation, scale, model, loader, 0.002f), _changeDir(0) {

}

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBox)
		: Being(position, rotation, scale, model, loader, hitBox, 0.002f), _changeDir(0) {

}

bool Balloon::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
	int moveDir;
	float x;
	float z;
	static const int timeToRandom = 1000;
	if (_changeDir >= timeToRandom && _nchange(gen) == 1) {
		x = fmodf(_position.x, 1);
		z = fmodf(_position.z, 1);
		if ((z < 0.01 || z > 0.99)) {
				_n_moveDir.x = 0;
				_n_moveDir.z = (_ndisision(gen) == 1) ? -1 : 1;
			_position.z = static_cast<float>(round(_position.z));
		}
		else if ((x < 0.01 || x > 0.99)) {
			_n_moveDir.z = 0;
			_n_moveDir.x = (_ndisision(gen) == 1) ? -1 : 1;
			_position.x = static_cast<float>(round(_position.x));
		}
	} else if (_n_moveDir.x == 0 && _n_moveDir.z == 0) {
		if (_ndisision(gen) == 1) {
			moveDir = (_ndisision(gen) == 1) ? -1 : 1;
			_n_moveDir.x = ((int) _n_moveDir.x == moveDir) ? -moveDir : moveDir;
		} else {
			moveDir = (_ndisision(gen) == 1) ? -1 : 1;
			_n_moveDir.z = ((int) _n_moveDir.z == moveDir) ? -moveDir : moveDir;
		}
	}
	_changeDir = (_changeDir >= timeToRandom) ? 0 : _changeDir + lastFrameTime;
	if (lastFrameTime < 500)
		return (Being::update(input, shader, lastFrameTime));
	return (true);
}
