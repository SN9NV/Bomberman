#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <iostream>
#include <GL/glew.h>

class Colour {
	public:
		GLubyte	r;
		GLubyte	g;
		GLubyte	b;
		GLubyte	a;

		Colour();
		Colour(GLubyte R, GLubyte G, GLubyte B, GLubyte A);
		Colour(GLubyte R, GLubyte G, GLubyte B);
		~Colour();

		Colour(const Colour &colour);

		Colour &operator =(const Colour &rhs);
};

std::ostream	&operator<<(std::ostream &out, const Colour &rhs);

#endif // COLOUR_HPP
