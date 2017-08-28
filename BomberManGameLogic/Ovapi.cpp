//
// Created by rojones on 2017/08/25.
//

#include "Ovapi.hpp"

static std::uniform_int_distribution<int> _n_disision(0, 1);
static std::uniform_int_distribution<int> _n_change(0, 3);
static std::default_random_engine _gen;

Ovapi::Ovapi(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader,
			 const Player &player, std::vector<std::vector<cge::Entity *>> &level, float hitBox) :
		Being(position, rotation, scale, model, loader, hitBox, 0.002f, 0, true),
		_changeDir(0),
		_player(player),
		_level(level)
{

}

bool Ovapi::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime)
{
	int moveDir;
	float pX, pZ;
	pX = static_cast<float>(round(_player.getPosition().x));
	pZ = static_cast<float>(round(_player.getPosition().z));
	float x;
	float z;
	static const int timeToRandom = 1000;
	/*if (_n_moveDir.x == 0 && _n_moveDir.z == 0) {
		if (_n_disision(_gen) == 1) {
			moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.x = ((int) _n_moveDir.x == moveDir) ? -moveDir : moveDir;
		} else {
			moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.z = ((int) _n_moveDir.z == moveDir) ? -moveDir : moveDir;
		}
	}
	else*/ if ((fmod(_position.x, 1) > 1 - _speed ||
				fmod(_position.x, 1) < _speed && pZ == roundf(this->getPosition().z) &&
				fabs(_player.getPosition().x - _position.x) < 6) && (_n_moveDir != glm::vec3({0, 0, 0})))
	{
		_n_moveDir.z = 0;
		_position.x = roundf(_position.x);
		if (pX > _position.x)
			_n_moveDir.x = 1;
		else if (pX < _position.x)
			_n_moveDir.x = -1;
	} else if ((fmod(_position.z, 1) > 1 - _speed ||
				fmod(_position.z, 1) < _speed && pX == roundf(this->getPosition().x) &&
				fabs(_player.getPosition().x - _position.x) < 6) && (_n_moveDir != glm::vec3({0, 0, 0})))
	{
		_n_moveDir.x = 0;
		_position.z = roundf(_position.z);
		if (pZ > _position.z)
			_n_moveDir.z = 1;
		else if (pZ < _position.z)
			_n_moveDir.z = -1;
	} else if (_changeDir >= timeToRandom && _n_change(_gen) == 1)
	{
		x = fmodf(_position.x, 1);
		z = fmodf(_position.z, 1);
		if ((z < 0.01 || z > 0.99))
		{
			_n_moveDir.x = 0;
			_n_moveDir.z = (_n_disision(_gen) == 1) ? -1 : 1;
			_position.z = static_cast<float>(round(_position.z));
		} else if ((x < 0.01 || x > 0.99))
		{
			_n_moveDir.z = 0;
			_n_moveDir.x = (_n_disision(_gen) == 1) ? -1 : 1;
			_position.x = static_cast<float>(round(_position.x));
		}
	} else if (_n_moveDir.x == 0 && _n_moveDir.z == 0)
	{
		if (_n_disision(_gen) == 1)
		{
			moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.x = ((int) _n_moveDir.x == moveDir) ? -moveDir : moveDir;
		} else
		{
			moveDir = (_n_disision(_gen) == 1) ? -1 : 1;
			_n_moveDir.z = ((int) _n_moveDir.z == moveDir) ? -moveDir : moveDir;
		}
	}
	_changeDir = (_changeDir >= timeToRandom) ? 0 : _changeDir + lastFrameTime;
	if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
		Being::setDirection();
	if (lastFrameTime < 500)
		return (Being::update(input, shader, lastFrameTime));
	return (true);
}

