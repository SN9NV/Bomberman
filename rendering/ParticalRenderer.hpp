//
// Created by Robert JONES on 2017/08/15.
//

#ifndef BOMBERMAN_PARTICALRENDERER_H
#define BOMBERMAN_PARTICALRENDERER_H


#include "../entites/RawModel.hpp"
#include "GLSLProgram.hpp"
#include "../entites/Partical.hpp"
#include "../entites/Camera.hpp"

namespace cge
{

	class ParticalRenderer
	{
	protected:
		RawModel plane;
		GLSLProgram &_shader;
		std::vector<Partical> _partiacals;
	public:
		//ParticalRenderer();

		~ParticalRenderer() = default;

		explicit ParticalRenderer(GLSLProgram &shader);

		void prepare() const;
		void addPartical(Partical partical);
		void partivalEffect(glm::vec3 position, glm::vec3 positionTolorence,
							glm::vec3 verlocity, glm::vec3 verlocityTolorence,
							float gravityeffect, float gravertyTolerance, float lifetime,
							float lifetimeTolorence, float scale, float scaleTolorence, int numParticals);
		void render(Partical &partical, Camera &camera);
		void render(Camera &camera);
		void update(unsigned lastframe);
		void updateRender(Camera &camera, unsigned lastframe);
	};
}

#endif //BOMBERMAN_PARTICALRENDERER_H
