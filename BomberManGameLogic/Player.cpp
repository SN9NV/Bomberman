
#include "Player.hpp"

bool Player::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
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

	/// TODO remove
	if (input.isKeyPressed(GLFW_KEY_KP_ADD)) {
		this->_animationSpeed += 0.01;
		std::cout << "Animation speed: " << this->_animationSpeed << "\n";
	}
	if (input.isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
		this->_animationSpeed -= 0.01;
		std::cout << "Animation speed: " << this->_animationSpeed << "\n";
	}
	/// TODO remove

	if (input.isKeyPressed(_bomb) && _bombs.size() < _maxBomb) {
		_plaseBomb = true;
	}
	if (input.isKeyPressed(_menue))
		_pauseMenue = true;
	if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
		Being::setDirection();
	return (Being::update(input, shader, lastFrameTime));
}

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed)
		: Being(position, rotation, scale, model, speed), _lives(3), _score(0) {}

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox,
			   float speed)
		: Being(position, rotation, scale, model, hitBox, speed), _lives(3), _pauseMenue(false), _score(0) {}

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
	return (this->_score);
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


