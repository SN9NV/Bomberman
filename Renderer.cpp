#include "Renderer.hpp"
#include "Maths.hpp"

Renderer::Renderer(const GLSLProgram &shader) :
	_shader(shader) { }

void Renderer::prepare() const {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

class attrType {
public:
	static constexpr GLuint	POSITION = 0;
	static constexpr GLuint	NORMAL = 1;
	static constexpr GLuint	UV = 2;
	static constexpr GLuint	JOINTS = 3;
	static constexpr GLuint	WEIGHTS = 4;
	static constexpr GLuint UNKNOWN = 5;

	static GLuint convert(const std::string &type) {
		if (type == "POSITION") return attrType::POSITION;
		if (type == "NORMAL") return attrType::NORMAL;
		if (type == "TEXCOORD_0") return attrType::UV;
		if (type == "JOINTS_0") return attrType::JOINTS;
		if (type == "WEIGHTS_0") return attrType::WEIGHTS;

		return attrType::UNKNOWN;
	}
};

void	drawMesh(tinygltf::Model &model, const tinygltf::Mesh &mesh, std::vector<GLuint> &vboMap) {
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

		glDrawElements((GLenum)primitive.mode, (GLsizei)indexAssessor.count, (GLenum)indexAssessor.componentType,
					   BUFFER_OFFSET(indexAssessor.byteOffset));

		for (auto &attr : primitive.attributes) {
			GLuint index = attrType::convert(attr.first);

			if (index != attrType::UNKNOWN) {
				glDisableVertexAttribArray(index);
			}
		}
	}
}

void Renderer::render(Entity &entity) const {
//	Model	&model = entity.getModel();
	Model &entityModel = entity.getModel();
//
//	// Bind the model and texture
	glBindVertexArray(entityModel.getVaoID());
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
	for (auto &attribArray : entityModel.getVBOs()) {
		glEnableVertexAttribArray(attribArray);
	}
//
//	// Upload the model's transformation matrix
//	glm::mat4	transformation = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
//	this->_shader.uploadMatrix4f(this->_shader.getUniformLocation("transformation"), transformation);

	this->_shader.uploadMatrix4f(
			this->_shader.getUniformLocation("transformation"),
			Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale())
	);
//
//	// Draw the triangles
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
//	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);

//	glActiveTexture(GL_TEXTURE0); // Not required. Active by default
	glBindTexture(GL_TEXTURE_2D, entityModel.getTexture().getID());

	tinygltf::Model	&model = entityModel.getTinygltfModel();
	const tinygltf::Scene &scene = model.scenes[model.defaultScene];

	for (auto &nodeIndex : scene.nodes) {
		tinygltf::Node	&node = model.nodes[nodeIndex];
		drawMesh(model, model.meshes[(node.mesh >= 0) ? node.mesh : 0], entityModel.getVBOs());
	}

//
//	// Unbind everything
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
	for (auto &attribArray : entityModel.getVBOs()) {
		glDisableVertexAttribArray(attribArray);
	}

	glBindVertexArray(0);
}