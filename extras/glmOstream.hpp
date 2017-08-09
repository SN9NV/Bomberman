#ifndef NEW_GLMOSTREAM_HPP
#define NEW_GLMOSTREAM_HPP

#include <iostream>
#include <glm/glm.hpp>

std::ostream &operator<<(std::ostream &out, const glm::vec4 &rhs);
std::ostream &operator<<(std::ostream &out, const glm::vec3 &rhs);
std::ostream &operator<<(std::ostream &out, const glm::vec2 &rhs);
std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs);
std::ostream &operator<<(std::ostream &out, const glm::quat &rhs);

#endif //NEW_GLMOSTREAM_HPP
