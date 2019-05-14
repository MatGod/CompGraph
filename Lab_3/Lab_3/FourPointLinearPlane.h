#pragma once
#include<boost\numeric\ublas\matrix.hpp>
#include<SFML\Graphics.hpp>
#include"Point.h"
using namespace boost::numeric::ublas;

class FourPointLinearPlane {
private:
	matrix<Point> points;
	sf::Vector3f norm;
	void setNorm();
public:
	FourPointLinearPlane();
	FourPointLinearPlane(matrix<Point>);
	void Draw(sf::RenderWindow*, sf::Color, sf::Color);
	void RotateX(float);
	void RotateY(float);
	~FourPointLinearPlane();
};

