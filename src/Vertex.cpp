#include "Vertex.hpp"

Vertex::Vertex() : position(), colour() {}

Vertex::Vertex(const Position2D &pos) : position(pos), colour() {}

Vertex::Vertex(const Position2D &pos, const Colour &colour, const UV &uv) : position(pos), colour(colour), uv(uv) {}

Vertex::~Vertex() {}

Vertex::Vertex(const Vertex &vertex) {
	*this = vertex;
}

Vertex	&Vertex::operator=(const Vertex &rhs) {
	this->position = rhs.position;
	this->colour = rhs.colour;
	this->uv = rhs.uv;

	return *this;
}


std::ostream	&operator<<(std::ostream &out, const Vertex &rhs) {
	out << "Position: " << rhs.position << "\n"
		<< "Colour:   " << rhs.colour << "\n"
		<< "UV:       ( " << rhs.uv.u << ", " << rhs.uv.v << " )";

	return out;
}
