#include <SDL_keycode.h>
#include "Player.hpp"

void Player::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	_plaseBomb = false;
	if (input.isKeyPressed(_up))
			this->_n_moveDir.z = -1;
	else if (input.isKeyPressed(_down))
		this->_n_moveDir.z = 1;
	else
		this->_n_moveDir.z = 0;
	if (input.isKeyPressed(_right))
		this->_n_moveDir.x = 1;
	else if (input.isKeyPressed(_left))
		this->_n_moveDir.x = -1;
	else
		this->_n_moveDir.x = 0;

	if (input.isKeyPressed(_bomb) && _bombs.size() < _maxBomb)
	{
		_plaseBomb = true;
	}
	if (input.isKeyPressed(_menue))
		_pauseMenue = true;
	if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
		Being::setRotation();
	Being::update(input, lastFrameTime);
}

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed)
		: Being(position, rotation, scale, model, speed), _lives(3)
{}

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox, float speed)
		: Being(position, rotation, scale, model, hitBox, speed), _lives(3), _pauseMenue(false)
{}

int Player::getLives() const
{
	return _lives;
}

int Player::loseLife()
{
	return --_lives;
}

bool Player::is_pauseMenue() const
{
	return _pauseMenue;
}

void Player::set_pauseMenue(bool _pauseMenue)
{
	Player::_pauseMenue = _pauseMenue;
}

int Player::get_special() const
{
	return _special;
}

void Player::set_special(int _special)
{
	Player::_special = _special;
}


