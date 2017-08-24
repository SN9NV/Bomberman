#include "Renderer.hpp"
#include "../extras/Maths.hpp"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

cge::Renderer::Renderer(GLSLProgram &shader) :
		_shader(shader)
{
	bool programInUse = shader.isInUse();

	if (!programInUse) shader.begin();
		this->_uniformIsAnimated = this->_shader.getUniformLocation("isAnimated");
		this->_uniformTransformation = this->_shader.getUniformLocation("transformation");
		this->_uniformView = this->_shader.getUniformLocation("view");

		for (unsigned i = 0; i < this->__MAX_JOINTS; i++) {
			this->_uniformJointTransforms[i] = this->_shader.getUniformLocation("jointTransforms[" + std::to_string(i) + "]");
		}
	if (!programInUse) shader.end();
}

void	cge::Renderer::prepare() const {
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void	cge::Renderer::drawMesh(const tinygltf::Model &model, const tinygltf::Mesh &mesh, const std::vector<GLuint> &vboMap) const {
	for (auto &primitive : mesh.primitives) {
		if (primitive.indices < 0)
			continue;

		for (auto &attr : primitive.attributes) {
			const auto &accessor = model.accessors[attr.second];

			glBindBuffer(GL_ARRAY_BUFFER, vboMap[accessor.bufferView]);

			GLint size;

			switch (accessor.type) {
				case TINYGLTF_TYPE_VEC2:
					size = 2;
					break;
				case TINYGLTF_TYPE_VEC3:
					size = 3;
					break;
				case TINYGLTF_TYPE_VEC4:
					size = 4;
					break;
				default:
					size = 1;
			}

			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
				glVertexAttribPointer(
						index,
						size,
						(GLenum)accessor.componentType,
						(GLboolean)((accessor.normalized) ? GL_TRUE : GL_FALSE),
						(GLsizei)model.bufferViews[accessor.bufferView].byteStride,
						BUFFER_OFFSET(accessor.byteOffset)
				);

				glEnableVertexAttribArray(index);
			}
		}

		const auto &indexAssessor = model.accessors[primitive.indices];
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboMap[indexAssessor.bufferView]);

		glDrawElements(
				(GLenum)primitive.mode,
				(GLsizei)indexAssessor.count,
				(GLenum)indexAssessor.componentType,
				BUFFER_OFFSET(indexAssessor.byteOffset)
		);

		for (auto &attr : primitive.attributes) {
			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
				glDisableVertexAttribArray(index);
			}
		}
	}
}

void	cge::Renderer::render(Entity &entity) const {
	Model &entityModel = entity.getModel();

	/// Bind the model and texture
	glBindVertexArray(entityModel.getVaoID());

	/// Upload the model's transformation matrix
	this->uploadTransformation(Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale()));

	/// Upload if the model has an animation or not
	this->uploadIsAnimated(entity.isAnimated());

	/// Upload animations
	if (entity.isAnimated()) {
		this->uploadJointTransforms(entity.getJointTransforms());
	}

	/// Draw the triangles
	glBindTexture(GL_TEXTURE_2D, entityModel.getTexture().getID());

	const tinygltf::Model	&model = entityModel.getTinygltfModel();
	const tinygltf::Scene &scene = model.scenes[model.defaultScene];

	for (auto &nodeIndex : scene.nodes) {
		const tinygltf::Node	&node = model.nodes[nodeIndex];
		drawMesh(model, model.meshes[(node.mesh >= 0) ? node.mesh : 0], entityModel.getVBOs());
	}
}

GLuint	cge::Renderer::attrType::convert(const std::string &type) {
	if (type == "POSITION") return attrType::POSITION;
	if (type == "NORMAL") return attrType::NORMAL;
	if (type == "TEXCOORD_0") return attrType::UV;
	if (type == "JOINTS_0") return attrType::JOINTS;
	if (type == "WEIGHTS_0") return attrType::WEIGHTS;

	return attrType::UNKNOWN;
}

void	cge::Renderer::uploadIsAnimated(bool isAnimated) const {
	this->_shader.uploadBool(this->_uniformIsAnimated, isAnimated);
}

void	cge::Renderer::uploadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const {
	unsigned i = 0;

	for (auto &jointTransform : jointTransforms) {
		this->_shader.uploadMatrix4f(this->_uniformJointTransforms[i++], jointTransform);
	}

	while (i < this->__MAX_JOINTS) {
		this->_shader.uploadMatrix4f(this->_uniformJointTransforms[i++], glm::mat4());
	}
}

void	cge::Renderer::uploadTransformation(const glm::mat4 &transformation) const {
	this->_shader.uploadMatrix4f(this->_uniformTransformation, transformation);
}

void	cge::Renderer::uploadView(const glm::mat4 &view) const {
	this->_shader.uploadMatrix4f(this->_uniformView, view);
}

void	cge::Renderer::render(std::vector<Entity *> &entities) const {
	std::sort(entities.begin(), entities.end(), [](cge::Entity *e1, cge::Entity *e2) -> bool {
		const auto &m1 = e1->getModel();
		const auto &m2 = e2->getModel();

		/// Sort by render type, then model (using memory address as identifier), then by texture ID.
		/// Render type
		if (m1.getType() > m2.getType()) return true;
		if (m1.getType() < m2.getType()) return false;

		/// Model address
		if (&m1.getTinygltfModel() > &m2.getTinygltfModel()) return true;
		if (&m1.getTinygltfModel() < &m2.getTinygltfModel()) return false;

		/// Texture ID
		if (m1.getTexture().getID() < m2.getTexture().getID()) return true;
		if (m1.getTexture().getID() > m2.getTexture().getID()) return false;

		/// Don't swap. Entities are identical
		return false;
	});

	auto &model = entities[0]->getModel();
//	auto vao = model.getVaoID();
//	auto textureID = model.getTexture().getID();
//	auto isAnimated = entities[0]->isAnimated();

	for (auto &entity : entities) {
		model = entity->getModel();

		glBindVertexArray(model.getVaoID());
		/// Upload the model's transformation matrix
		this->uploadTransformation(Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()));
//		this->uploadTransformation(entity->getTransformation());

		/// Upload animations
		if (entity->isAnimated()) {
			this->uploadJointTransforms(entity->getJointTransforms());
		}

		/// Bind the model and texture
//		if (vao != model.getVaoID() || entity == entities[0]) {
//			glBindVertexArray(model.getVaoID());
//			vao = model.getVaoID();
//		}

		/// Upload if the model has an animation or not
//		if (isAnimated != entity->isAnimated() || entity == entities[0]) {
			this->uploadIsAnimated(entity->isAnimated());
//			isAnimated = entity->isAnimated();
//		}

		/// Draw the triangles
//		if (textureID != model.getTexture().getID() || entity == entities[0]) {
			glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
//			textureID = model.getTexture().getID();
//		}

		const tinygltf::Model	&renderModel = model.getTinygltfModel();
		const tinygltf::Scene	&scene = renderModel.scenes[renderModel.defaultScene];

		for (auto &nodeIndex : scene.nodes) {
			const tinygltf::Node	&node = renderModel.nodes[nodeIndex];
			drawMesh(renderModel, renderModel.meshes[(node.mesh >= 0) ? node.mesh : 0], model.getVBOs());
		}
	}
}