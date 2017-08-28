//
// Created by Owen EXALL on 2017/08/22.
//

#include <random>
#include "Onil.hpp"

std::uniform_int_distribution<int> _n_disision(0, 1);
std::uniform_int_distribution<int> _n_change(0, 3);
std::default_random_engine _gen;

Onil::Onil(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, const Player& player, std::vector<std::vector<cge::Entity *>> &level, float hitBox) :
		Being(position, rotation, scale, model, loader, hitBox, 0.002f),
		_changeDir(0),
		_player(player),
		_level(level)
{

}

bool Onil::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
	auto pX = static_cast<float>(round(_player.getPosition().x));
	auto pZ = static_cast<float>(round(_player.getPosition().z));
	static const int timeToRandom = 1000;

	if (pX == round(this->getPosition().x) && !somethingInTheWayX(_player.getPosition(), this->getPosition())) {
		_n_moveDir.x = 0;

		if (pZ < round(this->getPosition().z))
			_n_moveDir.z = -1;
		else if (pZ > round(this->getPosition().z))
			_n_moveDir.z = 1;
	} else if (pZ == round(this->getPosition().z) && !somethingInTheWayY(_player.getPosition(), this->getPosition())){
		_n_moveDir.z = 0;

		if (pX < round(this->getPosition().x))
			_n_moveDir.x = -1;
		else if (pX > round(this->getPosition().x))
			_n_moveDir.x = 1;
	} else if (_changeDir >= timeToRandom && _n_change(_gen) == 1) {
		float x = fmodf(_position.x, 1);
		float z = fmodf(_position.z, 1);

		if (z < 0.01 || z > 0.99) {
				_n_moveDir.x = 0;
				_n_moveDir.z = (_n_disision(_gen) == 1) ? -1 : 1;
			_position.z = static_cast<float>(round(_position.z));
		} else if ((x < 0.01 || x > 0.99)) {
			_n_moveDir.z = 0;
			_n_moveDir.x = (_n_disision(_gen) == 1) ? -1 : 1;
			_position.x = static_cast<float>(round(_position.x));
		}
	} else if (_n_moveDir.x == 0 && _n_moveDir.z == 0) {
		if (_n_disision(_gen) == 1) {
			int moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.x = ((int) _n_moveDir.x == moveDir) ? -moveDir : moveDir;
		} else {
			int moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.z = ((int) _n_moveDir.z == moveDir) ? -moveDir : moveDir;
		}
	}

	_changeDir = (_changeDir >= timeToRandom) ? 0 : _changeDir + lastFrameTime;

	if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
		Being::setDirection();
	if (lastFrameTime < 500)
		return (Being::update(input, shader, lastFrameTime));

	return true;
}

bool Onil::somethingInTheWayX(const glm::vec3 &pPos, const glm::vec3 &onilPos) {
	float sZ = (pPos.z > onilPos.z) ? onilPos.z : pPos.z;
	float eZ = (pPos.z < onilPos.z) ? onilPos.z : pPos.z;

	sZ++;
	while (sZ < eZ) {
		if (_level[sZ][pPos.x] != nullptr)
			return true;
		sZ++;
	}

	return false;
}

bool Onil::somethingInTheWayY(const glm::vec3 &pPos, const glm::vec3 &onilPos) {
	float sX = (pPos.x > onilPos.x) ? onilPos.x : pPos.x;
	float eX = (pPos.x < onilPos.x) ? onilPos.x : pPos.x;

	sX++;
	while (sX < eX) {
		if (_level[pPos.z][sX] != nullptr)
			return true;
		sX++;
	}

	return false;
}
