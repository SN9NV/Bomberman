#ifndef NEW_VERTEX_HPP
#define NEW_VERTEX_HPP

#include <glm/glm.hpp>
#include <iostream>

struct Vertex {
	glm::vec3	position;	// 4 * 3 = 12
	glm::vec2	uv;			// 4 * 2 = 8
	glm::vec3	normal;		// 4 * 3 = 12
};							// Total = 32 bytes

#endif //NEW_VERTEX_HPP
