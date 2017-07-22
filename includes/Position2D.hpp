#ifndef POSITION2D_HPP
#define POSITION2D_HPP

#include <iostream>

class Position2D {
	public:
		float x;
		float y;

		Position2D();
		Position2D(float X, float Y);
		~Position2D();

		Position2D(const Position2D &position);

		Position2D &operator =(const Position2D &rhs);
};

std::ostream	&operator<<(std::ostream &out, const Position2D &rhs);

#endif // POSITION2D_HPP
