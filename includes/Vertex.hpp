#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Colour.hpp"
#include "Position2D.hpp"
#include "GLTexture.hpp"

class Vertex {
	public:
		Position2D	position;
		Colour		colour;
		UV			uv;

		Vertex();
		Vertex(const Position2D &pos);
		Vertex(const Position2D &pos, const Colour &colour, const UV &uv);
		~Vertex();

		Vertex(const Vertex &vertex);

		Vertex &operator=(const Vertex &rhs);
};

std::ostream	&operator<<(std::ostream &out, const Vertex &rhs);

#endif // VERTEX_HPP
