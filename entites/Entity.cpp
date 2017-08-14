#include "Entity.hpp"
#include "../extras/Maths.hpp"
#include "../tinyGLTF/tiny_gltf.h"
#include "../extras/glmOstream.hpp"

cge::Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model) :
		_model(model),
		_position(position),
		_rotation(rotation),
		_scale(scale),
		_transformationLocation(0),
		_lastTicks(SDL_GetTicks()),
		_ticksDelta(0),
		_animationTicks(0),
		_currentAnimation(0),
		_hasAnimation(!model.getTinygltfModel().animations.empty()),
		_needsTransformationUpdate(true)
{

}

void cge::Entity::addPosition(const glm::vec3 &delta) {
	this->_position += delta;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::setPosition(const glm::vec3 &position) {
	this->_position = position;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::addRotation(const glm::vec3 &delta) {
	this->_rotation += delta;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
	this->_needsTransformationUpdate = true;
}

cge::Model &cge::Entity::getModel() {
	return this->_model;
}

glm::vec3 cge::Entity::getPosition() const {
	return this->_position;
}

glm::vec3 cge::Entity::getRotation() const {
	return this->_rotation;
}

float cge::Entity::getScale() const {
	return this->_scale;
}

void cge::Entity::update(cge::GLSLProgram &shader, bool updateAnimation, int frameTime) {
	unsigned currentTicks = SDL_GetTicks();
	if (frameTime >= 0) {
		this->_ticksDelta = static_cast<unsigned>(frameTime);
	} else {
		this->_ticksDelta = currentTicks - this->_lastTicks;
	}

	this->_lastTicks = currentTicks;

	if (updateAnimation && this->_hasAnimation) {
		this->_applyAnimation(shader);
	}
}

void cge::Entity::_applyAnimation(cge::GLSLProgram &shader) {
	tinygltf::Model &model = this->_model.getTinygltfModel();
	if (!this->_hasAnimation || model.skins.empty() || model.skins[0].joints.empty()) {
		return;
	}

	this->_animationTicks += this->_ticksDelta;

	std::map<int, cge::Entity::Transformation>	transformationMap;

	unsigned char *data = model.buffers[0].data.data();
	tinygltf::Animation animation = model.animations[this->_currentAnimation];

	for (auto &channel : animation.channels) {
		tinygltf::AnimationSampler animationSampler = animation.samplers[channel.sampler];

		/// Array of keyframe times in seconds
		tinygltf::Accessor		inAccessor	= model.accessors[animationSampler.input];
		tinygltf::BufferView	inBuffView	= model.bufferViews[inAccessor.bufferView];

		/// Array of values for each keyframe
		tinygltf::Accessor		outAccessor	= model.accessors[animationSampler.output];
		tinygltf::BufferView	outBuffView	= model.bufferViews[outAccessor.bufferView];

		auto *keyFrames = reinterpret_cast<float *>(data + inBuffView.byteOffset);
		float ticks = std::fmod(this->_animationTicks / 1000.0f, inAccessor.count * (keyFrames[1] - keyFrames[0])/*keyFrames[inAccessor.count-1] - keyFrames[0]*/);

		/// Find the top of the frame we're in
		unsigned upperKeyframe = 0;
		if (ticks < keyFrames[inAccessor.count-1]) {
			while (ticks > keyFrames[upperKeyframe] - keyFrames[0]) {
				++upperKeyframe;
			}
		}

		unsigned lowerKeyframe = (upperKeyframe == 0) ? static_cast<unsigned>(inAccessor.count - 1) : upperKeyframe - 1;


		auto transformation = transformationMap.find(channel.target_node);
		if (transformation == transformationMap.end()) {
			transformationMap[channel.target_node] = { glm::vec3(), glm::quat() };
		}

//		/// If upperKeyframe == 0, that means that the transformation is 0 and no need for interpolation to be calculated.
//		if (upperKeyframe == 0) {
//			if (channel.target_path == "translation") {
//				transformationMap[channel.target_node].translation = *reinterpret_cast<glm::vec3 *>(data + outBuffView.byteOffset);
//			} else if (channel.target_path == "rotation") {
//				transformationMap[channel.target_node].rotation = *reinterpret_cast<glm::quat *>(data + outBuffView.byteOffset);
//			}
//
//			continue;
//		}

		/// Find how far through the bottom frame we are
		/// Interpolant = (x - a)/(b - a) where a < x < b
		float upperKeyframeTime =
				(upperKeyframe == 0) ?
				inAccessor.count * (keyFrames[1] - keyFrames[0]) :
				keyFrames[upperKeyframe] - keyFrames[0];
		float lowerKeyframeTime = keyFrames[lowerKeyframe] - keyFrames[0];
		float interpolant = (ticks - lowerKeyframeTime) / (upperKeyframeTime - lowerKeyframeTime);

		if (inBuffView.target == 3) {
			std::cout << lowerKeyframe << "(" << lowerKeyframeTime << "), " << upperKeyframe << "(" << upperKeyframeTime << "), " << interpolant << "\n";
		}

		if (channel.target_path == "translation") {
			auto *translation = reinterpret_cast<glm::vec3 *>(data + outBuffView.byteOffset);
			transformationMap[channel.target_node].translation = glm::mix(translation[lowerKeyframe], translation[upperKeyframe], interpolant);
		} else if (channel.target_path == "rotation") {
			auto *rotation = reinterpret_cast<glm::quat *>(data + outBuffView.byteOffset);
			transformationMap[channel.target_node].rotation = glm::slerp(rotation[lowerKeyframe], rotation[upperKeyframe], interpolant);
		}
	}

	tinygltf::Skin	&skin = model.skins[0];
	int rootJointIndex = skin.joints[0];

	auto						*inverseMatrices = (glm::mat4 *)(data + model.bufferViews[skin.inverseBindMatrices].byteOffset);
	glm::mat4					skeletonTransformation;
	std::map<int, glm::mat4>	animatedMatrices;


	tinygltf::Node &skeleton = model.nodes[skin.skeleton];

	if (!skeleton.translation.empty()) {
		glm::vec3	skeletonTranslation(skeleton.translation[0], skeleton.translation[1], skeleton.translation[2]);
		skeletonTransformation = glm::translate(skeletonTransformation, skeletonTranslation);
	}

	for (auto &joint : model.nodes[skin.skeleton].children) {
		if (joint < skin.skeleton) {
			continue;
		}

		this->_animateSkeleton(transformationMap, skeletonTransformation, model.nodes, joint, rootJointIndex, inverseMatrices, animatedMatrices);
	}

	const unsigned MAX_JOINTS = 50;
	for (unsigned i = 0; i < MAX_JOINTS; i++) {
		shader.uploadMatrix4f(shader.getUniformLocation("jointTransforms[" + std::to_string(i) + "]"),
							  i < animatedMatrices.size() ? animatedMatrices[i] : glm::mat4());
	}
}

void	cge::Entity::_animateSkeleton(const std::map<int, cge::Entity::Transformation> &transformationMap,
									  const glm::mat4 &parentTransform, std::vector<tinygltf::Node> &nodes,
									  int startNodeIndex, int rootNodeIndex, const glm::mat4 *inverseMatrices,
									  std::map<int, glm::mat4> &animatedMatrices) {
	glm::mat4	inverseMatrix = inverseMatrices[startNodeIndex - rootNodeIndex];

	glm::mat4		globalJointTransform;
	auto			jointTransform = transformationMap.find(startNodeIndex);

	glm::mat4	currentTransform;
	if (jointTransform == transformationMap.end()) {
		currentTransform = parentTransform;
		std::cout << "using parent transform\n";
	} else {
		currentTransform =
				parentTransform *
				glm::translate(glm::mat4(), jointTransform->second.translation) *
				glm::mat4_cast(glm::normalize(jointTransform->second.rotation));
	}

	for (auto &child : nodes[startNodeIndex].children) {
		this->_animateSkeleton(transformationMap, currentTransform, nodes, child, rootNodeIndex, inverseMatrices, animatedMatrices);
	}

	animatedMatrices[startNodeIndex - rootNodeIndex] = currentTransform * inverseMatrix;
}

bool cge::Entity::isAnimated() const {
	return this->_hasAnimation;
}

void cge::Entity::setAnimationTicks(unsigned ticks) {
	this->_animationTicks = ticks;
}
