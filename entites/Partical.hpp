//
// Created by Robert JONES on 2017/08/14.
//

#ifndef BOMBERMAN_PARTICAL_H
#define BOMBERMAN_PARTICAL_H


#include "../rendering/GLSLProgram.hpp"
#include <glm/simd/platform.h>

namespace cge
{
	class Partical
	{
	protected:
		glm::vec3 _position;
		glm::vec3 _verlocity;
		float	_gravityeffect;
		float 	_lifrtime;
		float 	_scale;
		float 	_elapsedtime;

	public:
		virtual ~Partical();
		Partical(const glm::vec3 &_position, const glm::vec3 &_verlocity, float _gravityeffect, float _lifrtime,
				 float _scale);
		//Partical();
		bool update(unsigned lastFrameTime);

		float getScale() const;

		const glm::vec3 &getPosition() const;
	};
}

#endif //BOMBERMAN_PARTICAL_H
