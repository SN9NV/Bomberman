//
// Created by Robert JONES on 2017/08/15.
//

#ifndef BOMBERMAN_PARTICALRENDERER_H
#define BOMBERMAN_PARTICALRENDERER_H


#include <map>
#include "../entites/RawModel.hpp"
#include "GLSLProgram.hpp"
#include "../entites/Partical.hpp"
#include "../entites/Camera.hpp"

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
		//ParticalRenderer();

		~ParticalRenderer() = default;

		explicit ParticalRenderer(GLSLProgram &shader);

		void prepare() const;

		void addPartical(cge::Partical partical, GLenum specFac, GLenum deffFac);

		void addParticalTexture(cge::TextureAtlas texture, GLenum specFac, GLenum deffFac);

		void partivalEffect(glm::vec3 position, glm::vec3 positionTolorence,
							glm::vec3 verlocity, glm::vec3 verlocityTolorence,
							float gravityeffect, float gravertyTolerance,
							float lifetime, float lifetimeTolorence,
							float scale, float scaleTolorence,
							float rotation, float rotationTolorence,
							float spin, float spinTolorencce,
							size_t numParticals,
							TextureAtlas texture,
							GLenum specFac, GLenum deffFac);

		void render(Partical &partical, Camera &camera);

		void render(Camera &camera);

		void update(unsigned lastframe, Camera camera);

		void updateRender(Camera &camera, unsigned lastframe);

		void clearParticals();
	};
}

#endif //BOMBERMAN_PARTICALRENDERER_H
