#include "Colour.hpp"

Colour::Colour() : r(255), g(255), b(255), a(255) {}

Colour::Colour(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
	r(R), g(G), b(B), a(A) {}

Colour::Colour(GLubyte R, GLubyte G, GLubyte B) :
	r(R), g(G), b(B), a(255) {}

Colour::~Colour() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

Colour::Colour(const Colour &colour) {
	*this = colour;
}

Colour &Colour::operator =(const Colour &rhs) {
	this->r = rhs.r;
	this->g = rhs.g;
	this->b = rhs.b;
	this->a = rhs.a;

	return *this;
}

std::ostream	&operator<<(std::ostream &out, const Colour &rhs) {
	out << "R: " << rhs.r << " (" << rhs.r / 255.0f << ")" << "\n"
		<< "G: " << rhs.g << " (" << rhs.g / 255.0f << ")"<< "\n"
		<< "B: " << rhs.b << " (" << rhs.b / 255.0f << ")"<< "\n"
		<< "A: " << rhs.a << " (" << rhs.a / 255.0f << ")";

	return out;
}
