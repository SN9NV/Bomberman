#ifndef BOMBERMAN_TINYGLTFOSTREAM_HPP
#define BOMBERMAN_TINYGLTFOSTREAM_HPP

#include <ostream>

#include "../tinyGLTF/tiny_gltf.h"

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vector);
std::ostream &operator<<(std::ostream &out, const std::vector<double> &vector);

std::ostream &operator<<(std::ostream &out, const tinygltf::Model &model);
std::ostream &operator<<(std::ostream &out, const tinygltf::AnimationChannel &channel);
std::ostream &operator<<(std::ostream &out, const tinygltf::AnimationSampler &sampler);
std::ostream &operator<<(std::ostream &out, const tinygltf::Animation &animation);
std::ostream &operator<<(std::ostream &out, const tinygltf::Accessor &accessor);
std::ostream &operator<<(std::ostream &out, const tinygltf::BufferView &bufferView);
std::ostream &operator<<(std::ostream &out, const tinygltf::Skin &skin);

std::ostream &operator<<(std::ostream &out, const tinygltf::Node &node);
//std::ostream &operator<<(std::ostream &out, const tinygltf::BufferView &bufferView);


#endif //BOMBERMAN_TINYGLTFOSTREAM_HPP
