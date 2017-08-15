//
// Created by Robert JONES on 2017/08/14.
//

#include "Partical.hpp"
#include "../extras/Maths.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cge
{
	const float GRAVE = 0.00098;
	/*Partical::Partical()
	{}*/

	Partical::~Partical()
	{

	}

	Partical::Partical(const glm::vec3 &_position, const glm::vec3 &_verlocity, float _gravityeffect, float _lifrtime,
					   float _scale) : _position(_position), _verlocity(_verlocity), _gravityeffect(_gravityeffect),
									   _lifrtime(_lifrtime), _scale(_scale), _elapsedtime(0)
	{}

	bool Partical::update(unsigned lastFrameTime)
	{
		_verlocity.y -= (GRAVE* _gravityeffect * lastFrameTime);
		_position += Maths::scaleVec3(_scale, _verlocity);
		_elapsedtime += lastFrameTime;
		return  (_elapsedtime < _lifrtime);
	}

	const glm::vec3 &Partical::getPosition() const
	{
		return _position;
	}

	float Partical::getScale() const
	{
		return _scale;
	}
}
