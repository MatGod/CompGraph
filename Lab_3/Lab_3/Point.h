#pragma once
#include <SFML\Graphics.hpp>

class Point
{
private:
	float x, y, z;
public:
	Point();
	Point(float, float, float);
	sf::Vector2f Isometric(float, float);
	void SetPosition(float, float, float);
	~Point();
};

