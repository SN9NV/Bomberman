//
// Created by Robert JONES on 2017/08/14.
//

#ifndef BOMBERMAN_PARTICAL_H
#define BOMBERMAN_PARTICAL_H


#include "../rendering/GLSLProgram.hpp"
#include "TextureAtlas.h"
#include "Camera.hpp"
#include <glm/simd/platform.h>

namespace cge {
	class Partical {
	protected:
		glm::vec3 _position;
		glm::vec3 _verlocity;
		float _gravityeffect;
		float _lifrtime;
		float _scale;
		float _elapsedtime;
		float _distCamSqur;
		TextureAtlas _texture;
		glm::vec2 _currOff;
		glm::vec2 _nextOff;
		float _blend;

	public:
		virtual ~Partical();

		Partical(const glm::vec3 &_position, const glm::vec3 &_verlocity, float _gravityeffect, float _lifrtime,
				 float _scale, TextureAtlas &texture);

		Partical(Partical const &cpy);

		//Partical();
		bool update(unsigned lastFrameTime, Camera camera);

		float getScale() const;

		const glm::vec3 &getPosition() const;

		const TextureAtlas &getTexture() const;

		const glm::vec2 &get_currOff() const;

		const glm::vec2 &get_nextOff() const;

		float get_blend() const;

		float getDistCamSqur() const;

		Partical &operator=(Partical const &cpy);
	};
}

#endif //BOMBERMAN_PARTICAL_H
