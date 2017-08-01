#include "glmOstream.hpp

std::ostream &operator<<(std::ostream &out, const glm::vec4 &rhs) {
	out << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << " ]";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec3 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec2 &rhs) {
	out << "{ " << rhs.x << ", " << rhs.y << " }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const Vertex &rhs) {
	out << "{ { " << rhs.position.x << ", " << rhs.position.y << ", " << rhs.position.z << " }, ";
	out << "{ " << rhs.normal.x << ", " << rhs.normal.y << ", " << rhs.normal.z << " }, ";
	out << "{ " << rhs.uv.x << ", " << rhs.uv.y << " } }";

	return out;
}

std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs) {
	out << "[ " << rhs[0][0] << ", " << rhs[0][1] << ", " << rhs[0][2] << ", " << rhs[0][3] << " ]\n";
	out << "[ " << rhs[1][0] << ", " << rhs[1][1] << ", " << rhs[1][2] << ", " << rhs[1][3] << " ]\n";
	out << "[ " << rhs[2][0] << ", " << rhs[2][1] << ", " << rhs[2][2] << ", " << rhs[2][3] << " ]\n";
	out << "[ " << rhs[3][0] << ", " << rhs[3][1] << ", " << rhs[3][2] << ", " << rhs[3][3] << " ]\n";

	return out;
}