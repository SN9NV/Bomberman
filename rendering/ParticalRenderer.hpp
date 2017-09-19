//
// Created by Robert JONES on 2017/08/15.
//

#ifndef BOMBERMAN_PARTICALRENDERER_H
#define BOMBERMAN_PARTICALRENDERER_H


#include <map>
#include "../shared.hpp"
#include "../entites/RawModel.hpp"
#include "GLSLProgram.hpp"
#include "../entites/Partical.hpp"
#include "../entites/Camera.hpp"

typedef struct particle_s {
	glm::vec3	position;
	glm::vec3	positionTolerance;
	glm::vec3	velocity;
	glm::vec3	velocityTolerance;

	float		gravityEffect;
	float		gravityTolerance;
	float		lifetime;
	float		lifetimeTolerance;
	float		scale;
	float		scaleTolerance;
	float		rotation;
	float		rotationTolerance;
	float		spin;
	float		spinTolerance;

	size_t				numParticles;
	cge::TextureAtlas	texture;
	GLenum				specularFactor;
	GLenum				diffuseFactor;
} particle_t;

namespace cge {

	class ParticalRenderer {
	protected:
		struct s_ParticalBlend {
			std::vector<cge::Partical> partical;
			GLenum specFac;
			GLenum deffFac;
		};
		struct s_InctenceData {
			glm::mat4 modelview;
			glm::vec2 currTextureOff;
			glm::vec2 nextTextureOff;
			float blend;
			float row;
		};
		RawModel plane;
		GLSLProgram &_shader;
		GLuint _instanceVBO;
		std::map<GLuint, s_ParticalBlend> _partiacals;

	private:
		glm::mat4 viewModelMatrix(Partical partical, Camera camera);

	public:
		~ParticalRenderer() = default;

		explicit ParticalRenderer(GLSLProgram &shader);

		void prepare() const;

		void addPartical(cge::Partical partical, GLenum specFac, GLenum deffFac);

		void addParticalTexture(cge::TextureAtlas texture, GLenum specFac, GLenum deffFac);

		void particleEffect(particle_t p);

		void render(Partical &partical, Camera &camera);

		void render(Camera &camera);

		void update(unsigned lastframe, Camera camera);

		void updateRender(Camera &camera, unsigned lastframe);

		void clearParticals();
	};
}

#endif //BOMBERMAN_PARTICALRENDERER_H
