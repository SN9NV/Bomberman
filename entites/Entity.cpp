#include "Entity.hpp"
#include "../extras/Maths.hpp"
#include "../tinyGLTF/tiny_gltf.h"

cge::Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model) :
		_model(model),
		_position(position),
		_rotation(rotation),
		_scale(scale),
		_transformation(1.0),
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

void cge::Entity::update(bool updateAnimation) {
	unsigned currentTicks = SDL_GetTicks();
	this->_ticksDelta = currentTicks - this->_lastTicks;
	this->_lastTicks = currentTicks;

	if (updateAnimation && this->_hasAnimation) {
		this->_applyAnimation();
	}
}

void cge::Entity::_applyAnimation() {
	tinygltf::Model &model = this->_model.getTinygltfModel();
	if (!this->_hasAnimation || model.skins.empty() || model.skins[0].joints.empty()) {
		return;
	}

	this->_animationTicks += this->_ticksDelta;

	unsigned char *data = model.buffers[0].data.data();
	tinygltf::Animation animation = model.animations[this->_currentAnimation];
	tinygltf::Skin skin = model.skins[0];

	std::vector<glm::mat4>	posedJoints;
	posedJoints.reserve(skin.joints.size());
	int rootJointIndex = skin.joints[0];

	auto *inverseMatrices = reinterpret_cast<glm::mat4 *>(data + model.bufferViews[skin.inverseBindMatrices].byteOffset);

	for (auto &channel : animation.channels) {
		tinygltf::AnimationSampler animationSampler = animation.samplers[channel.sampler];

		// Array of keyframe times in seconds
		tinygltf::Accessor		inAccessor	= model.accessors[animationSampler.input];
		tinygltf::BufferView	inBuffView	= model.bufferViews[inAccessor.bufferView];
		// Array of values for each keyframe
		tinygltf::Accessor		outAccessor	= model.accessors[animationSampler.output];
		tinygltf::BufferView	outBuffView	= model.bufferViews[outAccessor.bufferView];
		glm::mat4				inverseBind = inverseMatrices[channel.target_node];

		auto *keyFrames = reinterpret_cast<float *>(data + inBuffView.byteOffset);
		this->_animationTicks %= static_cast<unsigned>((keyFrames[inAccessor.count-1] - keyFrames[0]) * 1000);

		/// Find the top of the frame we're in
		unsigned topKeyframeIndex = 0;
		while (topKeyframeIndex < inAccessor.count && this->_animationTicks < keyFrames[topKeyframeIndex]) {
			++topKeyframeIndex;
		}

		/// Find how far through the bottom frame we are
		/// bottomScale(a, x, b) = (x - a)/(b - x) where a < x < b

		if (channel.target_path == "translation") {

		}
	}
}
