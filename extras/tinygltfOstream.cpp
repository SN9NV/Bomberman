#include "tinygltfOstream.hpp"

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vector) {
	out << "[ ";

	for (auto &item : vector) {
		out << item;

		if (&item != &vector.back()) {
			out << ", ";
		}
	}

	out << " ]";

	return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<double> &vector) {
	out << "[ ";

	for (auto &item : vector) {
		out << item;

		if (&item != &vector.back()) {
			out << ", ";
		}
	}

	out << " ]";

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::Model &model) {
	out << "Accessors: " << model.accessors.size() << "\n";
	out << "Animations: " << model.animations.size() << "\n";
	out << "Buffers: " << model.buffers.size() << "\n";
	out << "Buffer Views: " << model.bufferViews.size() << "\n";
	out << "Materials: " << model.materials.size() << "\n";
	out << "Meshes: " << model.meshes.size() << "\n";
	out << "Nodes: " << model.nodes.size() << "\n";
	out << "Textures: " << model.textures.size() << "\n";
	out << "Images: " << model.images.size() << "\n";
	out << "Skins: " << model.skins.size() << "\n";
	out << "Sampler: " << model.samplers.size() << "\n";
	out << "Cameras: " << model.cameras.size() << "\n";
	out << "Scenes: " << model.scenes.size() << "\n";
	out << "Default Scene: " << model.defaultScene;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::AnimationChannel &channel) {
	out << "Sampler:     " << channel.sampler << "\n";
	out << "Target Node: " << channel.target_node << "\n";
	out << "Target Path: " << channel.target_path;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::AnimationSampler &sampler) {
	out << "Input:         " << sampler.input << "\n";
	out << "Output:        " << sampler.output << "\n";
	out << "Interpolation: " << sampler.interpolation;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::Animation &animation) {
	out << "Name: " << animation.name << "\n";

	out << "Animation Channels:\n";
	for (auto &channel : animation.channels) {
		out << channel << "\n";
		out << "Sampler:\n";
		out << animation.samplers[channel.sampler] << "\n";
	}

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::Accessor &accessor) {
	out << "Name: " << accessor.name << "\n";
	out << "Byte Offset: " << accessor.byteOffset << "\n";
	out << "Normalized: " << (accessor.normalized ? "TRUE" : "FALSE") << "\n";
	out << "Component Type: " << accessor.componentType << "\n";
	out << "Count: " << accessor.count << "\n";
	out << "Type: " << accessor.type;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::BufferView &bufferView) {
	out << "Name: " << bufferView.name << "\n";
	out << "Buffer Index: " << bufferView.buffer << "\n";
	out << "Byte Offset: " << bufferView.byteOffset << "\n";
	out << "Byte Length: " << bufferView.byteLength << "\n";
	out << "Byte Stride: " << bufferView.byteStride << "\n";
	out << "Target: " << bufferView.target << "\n";
	out << "pad0: " << bufferView.pad0;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::Node &node) {
	out << "Name: " << node.name << "\n";
	out << "Camera: " << node.camera << "\n";
	out << "Skin: " << node.skin << "\n";
	out << "Mesh: " << node.mesh << "\n";

	out << "Children:\n";
	out << node.children << "\n";

	out << "Rotation:\n"<< node.rotation << "\n";
	out << "Scale:\n" << node.scale << "\n";
	out << "Translation:\n" << node.translation << "\n";
	out << "Matrix:\n" << node.matrix << "\n";
	out << "Weights:\n" << node.weights;

	return out;
}

std::ostream &operator<<(std::ostream &out, const tinygltf::Skin &skin) {
	out << "Name: " << skin.name << "\n";
	out << "Inverse Bind Matrices: " << skin.inverseBindMatrices << "\n";
	out << "Skeleton: " << skin.skeleton << "\n";
	out << "Joints:\n" << skin.joints;

	return out;
}