#include "Entity.hpp"
#include "../extras/Maths.hpp"

namespace cge
{
	Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model) :
			_model(model),
			_position(position),
			_rotation(rotation),
			_scale(scale),
			_hitBoxRadius(0),
			_transformation(1.0),
			_transformationLocation(0),
			_lastTicks(glfwGetTime()),
			_ticksDelta(0.0),
			_animationTicks(0.0),
			_currentAnimation(0),
			_hasAnimation(!model.getTinygltfModel().animations.empty()),
			_animationSpeed(1.0),
			_needsTransformationUpdate(true)
	{

	}

	Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model, float hitBox) :
			_model(model),
			_position(position),
			_rotation(rotation),
			_scale(scale),
			_hitBoxRadius(hitBox * _scale),
			_transformation(1.0),
			_transformationLocation(0),
			_lastTicks(glfwGetTime()),
			_ticksDelta(0.0),
			_animationTicks(0.0),
			_currentAnimation(0),
			_hasAnimation(!model.getTinygltfModel().animations.empty()),
			_animationSpeed(1.0),
			_needsTransformationUpdate(true)
	{

	}

	void Entity::addPosition(const glm::vec3 &delta)
	{
		this->_position += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setPosition(const glm::vec3 &position)
	{
		this->_position = position;
		this->_needsTransformationUpdate = true;
	}

	void Entity::addRotation(const glm::vec3 &delta)
	{
		this->_rotation += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setRotation(const glm::vec3 &rotation)
	{
		this->_rotation = rotation;
		this->_needsTransformationUpdate = true;
	}

	Model &Entity::getModel()
	{
		return this->_model;
	}

	glm::vec3 Entity::getPosition() const
	{
		return this->_position;
	}

	glm::vec3 Entity::getRotation() const
	{
		return this->_rotation;
	}

	float Entity::getScale() const
	{
		return this->_scale;
	}

	bool	cge::Entity::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime)
	{
		(void)lastFrameTime;

//		double currentTime = glfwGetTime();

//		this->_ticksDelta = currentTime - this->_lastTicks;
		this->_ticksDelta = lastFrameTime;
		this->_animationTicks += (this->_ticksDelta * this->_animationSpeed);

		std::cout << _ticksDelta << ", " << _animationTicks << "\n";

		this->_lastTicks = (lastFrameTime / 1000.0);

		if (this->_hasAnimation) {
			if (shader.isInUse()) {
				this->_applyAnimation(shader);
			} else {
				shader.start();
				this->_applyAnimation(shader);
				shader.end();
			}
		}

		return true;
	}

	void cge::Entity::_applyAnimation(cge::GLSLProgram &shader) {
		tinygltf::Model &model = this->_model.getTinygltfModel();
		if (!this->_hasAnimation || model.skins.empty() || model.skins[0].joints.empty()) {
			return;
		}

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
			float animationLength = inAccessor.count * (keyFrames[1] - keyFrames[0]);

			if (this->_animationTicks < 0.0) {
				this->_animationTicks += animationLength;
			} else if (this->_animationTicks >= animationLength) {
				this->_animationTicks -= animationLength;
			}

			/// Find the top of the frame we're in
			unsigned upperKeyframe = 0;
			if (this->_animationTicks < keyFrames[inAccessor.count-1]) {
				while (this->_animationTicks > keyFrames[upperKeyframe] - keyFrames[0]) {
					++upperKeyframe;
				}
			}

			unsigned lowerKeyframe = (upperKeyframe == 0) ? static_cast<unsigned>(inAccessor.count - 1) : upperKeyframe - 1;

			auto transformation = transformationMap.find(channel.target_node);
			if (transformation == transformationMap.end()) {
				transformationMap[channel.target_node] = { glm::vec3(), glm::quat() };
			}

			/// Find how far through the bottom frame we are
			/// Interpolant = (x - a)/(b - a) where a < x < b
			float upperKeyframeTime =
					(upperKeyframe == 0) ?
					inAccessor.count * (keyFrames[1] - keyFrames[0]) :
					keyFrames[upperKeyframe] - keyFrames[0];
			float lowerKeyframeTime = keyFrames[lowerKeyframe] - keyFrames[0];
			float interpolant = static_cast<float>(this->_animationTicks - lowerKeyframeTime) / (upperKeyframeTime - lowerKeyframeTime);

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

	float Entity::getHitBoxRadius() const
	{
		return _hitBoxRadius;
	}

	void Entity::setHitBoxRadius(const float &hitBox)
	{
		_hitBoxRadius = hitBox * _scale;

	}

	void Entity::setScale(float scale)
	{
		_scale = scale;
		this->_needsTransformationUpdate = true;
		_hitBoxRadius = _hitBoxRadius * _scale;
	}

	void Entity::setAnimationTicks(double ticks) {
		this->_animationTicks = ticks;
	}

	void Entity::setAnimationSpeed(float speed) {
		this->_animationSpeed = speed;
	}

	bool Entity::isAnimated() const {
		return this->_hasAnimation;
	}

	double Entity::getAnimationSpeed() const {
		return this->_animationSpeed;
	}


}