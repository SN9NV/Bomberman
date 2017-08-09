#include "Entity.hpp"
#include "../extras/Maths.hpp"
#include "../tinyGLTF/tiny_gltf.h"
#include "../extras/glmOstream.hpp"

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
	} else {
		std::cout << "No animation\n"; ///> TODO remove debug
	}
}

void cge::Entity::_applyAnimation() {
	tinygltf::Model &model = this->_model.getTinygltfModel();
	if (!this->_hasAnimation || model.skins.empty() || model.skins[0].joints.empty()) {
		return;
	}

	this->_animationTicks += this->_ticksDelta;

	std::unordered_map<int, cge::Entity::Transformation>	transformationMap;

	unsigned char *data = model.buffers[0].data.data();
	tinygltf::Animation animation = model.animations[this->_currentAnimation];
	tinygltf::Skin skin = model.skins[0];

	std::vector<glm::mat4>	posedJoints;
	posedJoints.reserve(skin.joints.size());
	int rootJointIndex = skin.joints[0];
	(void)rootJointIndex; ///> TODO remove

//	auto *inverseMatrices = reinterpret_cast<glm::mat4 *>(data + model.bufferViews[skin.inverseBindMatrices].byteOffset);

	for (auto &channel : animation.channels) {
		tinygltf::AnimationSampler animationSampler = animation.samplers[channel.sampler];

		// Array of keyframe times in seconds
		tinygltf::Accessor		inAccessor	= model.accessors[animationSampler.input];
		tinygltf::BufferView	inBuffView	= model.bufferViews[inAccessor.bufferView];
		// Array of values for each keyframe
		tinygltf::Accessor		outAccessor	= model.accessors[animationSampler.output];
		tinygltf::BufferView	outBuffView	= model.bufferViews[outAccessor.bufferView];
//		glm::mat4				inverseBind = inverseMatrices[channel.target_node];

		auto *keyFrames = reinterpret_cast<float *>(data + inBuffView.byteOffset);
		this->_animationTicks %= static_cast<unsigned>((keyFrames[inAccessor.count-1] - keyFrames[0]) * 1000);


		/// Find the top of the frame we're in
		unsigned upperKeyframe = 0;
		while ((this->_animationTicks / 1000.0f) > keyFrames[upperKeyframe]) {
			++upperKeyframe;
		}

		auto transformation = transformationMap.find(channel.target_node);
		if (transformation == transformationMap.end()) {
			transformationMap[channel.target_node] = { glm::vec3(), glm::quat() };
		}

		if (upperKeyframe == 0) {
			if (channel.target_path == "translation") {
				transformationMap[channel.target_node].translation = reinterpret_cast<glm::vec3 *>(data + outBuffView.byteOffset)[0];
			} else if (channel.target_path == "rotation") {
				transformationMap[channel.target_node].rotation = reinterpret_cast<glm::quat *>(data + outAccessor.byteOffset)[0];
			}

			continue;
		}

		/// Find how far through the bottom frame we are
		/// Interpolant = (x - a)/(b - a) where a < x < b
		float interpolant =
				((this->_animationTicks / 1000.0f) - keyFrames[upperKeyframe-1]) /
				(keyFrames[upperKeyframe] - keyFrames[upperKeyframe-1]);

		if (channel.target_path == "translation") {
			auto *translation = reinterpret_cast<glm::vec3 *>(data + outBuffView.byteOffset);
			transformationMap[channel.target_node].translation =
					glm::mix(translation[upperKeyframe-1], translation[upperKeyframe], interpolant);
		} else if (channel.target_path == "rotation") {
			auto *rotation = reinterpret_cast<glm::quat *>(data + outAccessor.byteOffset);
			transformationMap[channel.target_node].rotation =
					glm::lerp(rotation[upperKeyframe-1], rotation[upperKeyframe], interpolant);
		}
	}

	for (auto &transformation : transformationMap) {
		std::cout << "Target Node: " << transformation.first << "\n";
		std::cout << "Translation: " << transformation.second.translation << "\n";
		std::cout << "Rotation: " << transformation.second.rotation << "\n\n";
	}
}
