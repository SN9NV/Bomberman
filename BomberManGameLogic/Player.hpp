#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "Being.hpp"
#include "../io/InputManager.hpp"
#include "Bomb.hpp"

class Player : public Being {
public:
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float speed = 0.25f, float hitBoxRadius = 0.0f);

	int get_up() const;
	void set_up(int up);

	int get_down() const;
	void set_down(int down);

	int get_left() const;
	void set_left(int left);

	int get_right() const;
	void set_right(int right);

	int get_bomb() const;

	int get_special() const;

	int get_menue() const;
	bool isPauseMenue() const;
	void setPauseMenue(bool _pauseMenue);
	int getSpecial() const;
	void setSpecial(int _special);
	int getLives() const;
	void setLives(int lives);
	void addLives(int lives);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
	int loseLife();

	int getScore() const;
	void setScore(size_t score);
	void addScore(size_t addition);
	void subScore(size_t subtraction);
	bool isDetonator() const;
	void playSound(std::string sound);
	void setDetonator(bool _detonator);

private:
	int _lives;
	size_t _score;
	int _up = GLFW_KEY_W;
	int _down = GLFW_KEY_S;
	int _left = GLFW_KEY_A;
	int _right = GLFW_KEY_D;
	int _bomb = GLFW_KEY_SPACE;
	int _special = GLFW_KEY_V;
	int _menue = GLFW_KEY_ESCAPE;
	bool _pauseMenue;
	bool _detonator;

	void	_setEffects();
};

#endif //BOMBERMAN_PLAYER_HPP
