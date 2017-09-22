#include "Renderer.hpp"
#include "../extras/Maths.hpp"

cge::Renderer::Renderer(GLSLProgram &shader) :
		_shader(shader)
{
	bool programInUse = shader.isInUse();

	if (!programInUse) shader.begin();
		this->_uniformIsAnimated = this->_shader.getUniformLocation("isAnimated");
		this->_uniformTransformation = this->_shader.getUniformLocation("transformation");
		this->_uniformView = this->_shader.getUniformLocation("view");
		this->_uniformJointTransforms = this->_shader.getUniformLocation("jointTransforms");
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
			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
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
	this->_shader.uploadMatrix4f(this->_uniformJointTransforms, jointTransforms);
}

void	cge::Renderer::uploadTransformation(const glm::mat4 &transformation) const {
	this->_shader.uploadMatrix4f(this->_uniformTransformation, transformation);
}

void	cge::Renderer::uploadView(const glm::mat4 &view) const {
	this->_shader.uploadMatrix4f(this->_uniformView, view);
}


void	cge::Renderer::render(std::vector<Entity *> &entities) {
	GLuint lastTextur = 0;


	if(!entities.empty())
	{
		auto foo = entities.begin();
		lastTextur = (*foo)->getRenderParameters().textureID;
		glBindTexture(GL_TEXTURE_2D, lastTextur);
	}
	for (auto &entity : entities) {
		auto renderParameters = entity->getRenderParameters();

		/// Bind the model and texture
		glBindVertexArray(renderParameters.VAO);

		/// Upload the model's transformation matrix
		this->uploadTransformation(entity->getTransformation());

		/// Upload if the model has an animation or not
		this->uploadIsAnimated(entity->isAnimated());

		/// Upload animations
		if (entity->isAnimated()) {
			this->uploadJointTransforms(entity->getJointTransforms());
		}

		/// Draw the triangles
		if (renderParameters.textureID != lastTextur)
		{
			glBindTexture(GL_TEXTURE_2D, renderParameters.textureID);
			lastTextur = renderParameters.textureID;
		}

		for (auto &index : *renderParameters.attribArrayIndexes) {
			glEnableVertexAttribArray(index);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderParameters.indexAssessor);

		glDrawElements(
			renderParameters.mode,
			renderParameters.count,
			renderParameters.componentType,
			BUFFER_OFFSET(renderParameters.byteOffset)
		);

		for (auto &index : *renderParameters.attribArrayIndexes) {
			glDisableVertexAttribArray(index);
		}
	}
}
