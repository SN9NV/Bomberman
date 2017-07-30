#ifndef NEW_VERTEX_HPP
#define NEW_VERTEX_HPP

#include <glm/glm.hpp>
#include <iostream>

struct Vertex {
	glm::vec3	position;	// 4 * 3 = 12
	glm::vec3	normal;		// 4 * 3 = 12
	glm::vec2	uv;			// 4 * 2 = 8
};							// Total = 32 bytes


/*std::ostream &operator<<(std::ostream &out, const glm::vec3 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec2 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << " }";

	return out;
}*/

/*std::ostream &operator<<(std::ostream &out, const engine::Vertex &rhs) {
	out << "{ { " << rhs.position.x << ", " << rhs.position.y << ", " << rhs.position.z << " }, ";
	out << "{ " << rhs.normal.x << ", " << rhs.normal.y << ", " << rhs.normal.z << " }, ";
	out << "{ " << rhs.uv.x << ", " << rhs.uv.y << " } }";

	return out;
}*/

#endif //NEW_VERTEX_HPP
