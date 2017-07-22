#include "Position2D.hpp"

Position2D::Position2D() : x(0.0f), y(0.0f) {}
Position2D::Position2D(float X, float Y) : x(X), y(Y) {}
Position2D::~Position2D() {}

Position2D::Position2D(const Position2D &rhs) {
	*this = rhs;
}

Position2D &Position2D::operator =(const Position2D &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;

	return *this;
}

std::ostream	&operator<<(std::ostream &out, const Position2D &rhs) {
	out << "( " << rhs.x << ", " << rhs.y << " )";

	return out;
}
