#include "Point.h"
#define _USE_MATH_DEFINES
#include <boost\numeric\ublas\matrix.hpp>
#include <math.h>
using namespace boost::numeric::ublas;


Point::Point() {}

Point::Point(const Point &p) {
	this->pos = p.pos;
}

Point::Point(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

sf::Vector2f Point::Isometric(float xSize, float ySize) {
	//float dist = 1000.0f;
	//float sx = xSize / 2 + pos.x * dist / (pos.z + dist),
		//sy = ySize / 2 - pos.y * dist / (pos.z + dist);
	return sf::Vector2f(pos.x + xSize / 2, ySize / 2 - pos.y);
}

void Point::SetPosition(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Point::SetPosition(sf::Vector3f position) {
	pos = position;
}

sf::Vector3f Point::GetPosition() {
	return pos;
}

void Point::RotateX(float angl) {
	vector<float> posV(3);
	posV(0) = pos.x; posV(1) = pos.y; posV(2) = pos.z;
	matrix<float> rotateM(3, 3);
	rotateM(0, 0) = 1; rotateM(0, 1) = 0;						rotateM(0, 2) = 0;
	rotateM(1, 0) = 0; rotateM(1, 1) = cos(angl * M_PI / 180);	rotateM(1, 2) = sin(angl * M_PI / 180);
	rotateM(2, 0) = 0; rotateM(2, 1) = -sin(angl * M_PI / 180); rotateM(2, 2) = cos(angl * M_PI / 180);
	posV = prod(posV, rotateM);
	pos.x = posV(0); pos.y = posV(1); pos.z = posV(2);
}

void Point::RotateY(float angl) {
	vector<float> posV(3);
	posV(0) = pos.x; posV(1) = pos.y; posV(2) = pos.z;
	matrix<float> rotateM(3, 3);
	rotateM(0, 0) = cos(angl * M_PI / 180); rotateM(0, 1) = 0; rotateM(0, 2) = -sin(angl * M_PI / 180);
	rotateM(1, 0) = 0;						rotateM(1, 1) = 1; rotateM(1, 2) = 0;
	rotateM(2, 0) = sin(angl * M_PI / 180); rotateM(2, 1) = 0; rotateM(2, 2) = cos(angl * M_PI / 180);
	posV = prod(posV, rotateM);
	pos.x = posV(0); pos.y = posV(1); pos.z = posV(2);
}

Point::~Point() {}

Point operator-(Point & left, Point & right) {
	return Point(left.GetPosition().x - right.GetPosition().x, left.GetPosition().y - right.GetPosition().y, left.GetPosition().z - right.GetPosition().z);
}

Point operator+(Point & left, Point & right) {
	return Point(left.GetPosition().x + right.GetPosition().x, left.GetPosition().y + right.GetPosition().y, left.GetPosition().z + right.GetPosition().z);
}

