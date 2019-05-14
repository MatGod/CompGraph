#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

class Point
{
private:
	sf::Vector3f pos;
public:
	Point();
	Point(float, float, float);
	sf::Vector2f Isometric(float, float);
	void SetPosition(float, float, float);
	void SetPosition(sf::Vector3f);
	sf::Vector3f GetPosition();
	void RotateX(float);
	void RotateY(float);
	~Point();
};

Point operator- (Point &left, Point &right);

Point operator+ (Point &left, Point &right);