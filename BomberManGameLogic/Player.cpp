
#include "Player.hpp"

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float speed, float hitBoxRadius) :
		Being(position, rotation, scale, model, loader, speed, hitBoxRadius),
		_lives(3),
		_pauseMenue(false),
		_score(0),
		_detonator(false)
{

}

bool Player::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
	_placeBomb = false;
	_playAnimation = false;

	static unsigned bombBounce = 0;
	static unsigned detonateBounce = 0;

	if (input.isKeyPressed(_up)) {
		_playAnimation = true;
		this->_n_moveDir.z = -1;
	} else if (input.isKeyPressed(_down)) {
		_playAnimation = true;
		this->_n_moveDir.z = 1;
	} else {
		this->_n_moveDir.z = 0;
	}

	if (input.isKeyPressed(_right)) {
		_playAnimation = true;
		this->_n_moveDir.x = 1;
	} else if (input.isKeyPressed(_left)) {
		_playAnimation = true;
		this->_n_moveDir.x = -1;
	} else {
		this->_n_moveDir.x = 0;
	}

	bombBounce = (lastFrameTime > bombBounce) ? 0 : bombBounce - lastFrameTime;

	if (input.isKeyPressed(_bomb) && _bombs.size() < _maxBomb && bombBounce == 0) {
		_placeBomb = true;
		bombBounce = 300;
	}

	detonateBounce = (lastFrameTime > detonateBounce) ? 0 : detonateBounce - lastFrameTime;
	if (input.isKeyPressed(_special)) {
		if (detonateBounce == 0) {
			int i = 0;
			while (i < _bombs.size() && _bombs[i]->isDeternate())
			{
				i++;
			}
			_bombs[i]->setDetonate(true);
			detonateBounce = 300;
		}
	}
	if (input.isKeyPressed(_menue)) {
		_pauseMenue = true;
	}

	if (_n_moveDir.x != 0 || _n_moveDir.z != 0) {
		Being::setDirection();
	}

	return Being::update(input, shader, lastFrameTime);
}

int Player::getLives() const {
	return _lives;
}

int Player::loseLife() {
	return --_lives;
}

bool Player::isPauseMenue() const {
	return _pauseMenue;
}

void Player::setPauseMenue(bool _pauseMenue) {
	Player::_pauseMenue = _pauseMenue;
}

int Player::getSpecial() const {
	return _special;
}

void Player::setSpecial(int _special) {
	Player::_special = _special;
}

void Player::setLives(int lives) {
	Player::_lives = lives;
}

void Player::addLives(int lives) {
	Player::_lives += lives;
}

int Player::get_up() const {
	return _up;
}

int Player::get_down() const {
	return _down;
}

int Player::get_left() const {
	return _left;
}

int Player::get_right() const {
	return _right;
}

int Player::get_bomb() const {
	return _bomb;
}

int Player::get_special() const {
	return _special;
}

int Player::get_menue() const {
	return _menue;
}

int Player::getScore() const {
	return this->_score;
}

void Player::setScore(int score) {
	this->_score = score;
}

void Player::addScore(int addition) {
	this->_score += addition;
}

void Player::subScore(int subtraction) {
	this->_score -= subtraction;
}

void Player::set_up(int up) {
	this->_up = up;
}

void Player::set_down(int down) {
	this->_down = down;
}

void Player::set_left(int left) {
	this->_left = left;
}

void Player::set_right(int right) {
	this->_right = right;
}

bool Player::isDetonator() const {
	return _detonator;
}

void Player::setDetonator(bool _detonator) {
	Player::_detonator = _detonator;
}
