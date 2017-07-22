#include "Vertex.hpp"

Vertex::Vertex() : position(), colour() {}

Vertex::Vertex(const Position2D &pos) : position(pos), colour() {}

Vertex::Vertex(const Position2D &pos, const Colour &colour) : position(pos), colour(colour) {}

Vertex::~Vertex() {}

Vertex::Vertex(const Vertex &vertex) {
	*this = vertex;
}

Vertex	&Vertex::operator=(const Vertex &rhs) {
	this->position = rhs.position;
	this->colour = rhs.colour;

	return *this;
}


std::ostream	&operator<<(std::ostream &out, const Vertex &rhs) {
	out << rhs.position << "\n"
		<< rhs.colour;

	return out;
}
