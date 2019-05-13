#include "Point.h"

#include <boost\numeric\ublas\matrix.hpp>
using namespace boost::numeric::ublas;


Point::Point()
{
}

Point::Point(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

sf::Vector2f Point::Isometric(float xSize, float ySize) {
	float dist = 1000.0f;
	float sx = xSize / 2 + x * dist / (z + dist),
		sy = ySize / 2 - y * dist / (z + dist);
	return sf::Vector2f(sx, sy);
}

void Point::SetPosition(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


Point::~Point()
{
}
