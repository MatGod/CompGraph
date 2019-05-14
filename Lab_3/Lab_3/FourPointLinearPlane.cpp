#include "FourPointLinearPlane.h"



void FourPointLinearPlane::setNorm() {
	Point a(points(0, 1) - points(0, 0)),
		b(points(1, 0) - points(0, 0));
	float x = a.GetPosition().y * b.GetPosition().z - a.GetPosition().z * b.GetPosition().y,
		y = a.GetPosition().z * b.GetPosition().x - a.GetPosition().x * b.GetPosition().z,
		z = a.GetPosition().x * b.GetPosition().y - a.GetPosition().y * b.GetPosition().x;
	norm = sf::Vector3f(x, y, z);
}

FourPointLinearPlane::FourPointLinearPlane() {}

FourPointLinearPlane::FourPointLinearPlane(matrix<Point> m) {
	points.resize(2, 2);
	points = m;
	setNorm();
}

void FourPointLinearPlane::Draw(sf::RenderWindow* window, sf::Color color, sf::Color color2) {
	sf::ConvexShape shape;
	shape.setPointCount(4);
	float cos = norm.z / (sqrt(pow(norm.x, 2) + pow(norm.y, 2) + pow(norm.z, 2)));
	if (cos < 0)
		shape.setFillColor(sf::Color(color.r - (color.r * (1 - abs(cos)) / 1.25f), color.g - (color.g * (1 - abs(cos)) / 1.25f), color.b - (color.b * (1 - abs(cos)) / 1.25f)));
	else shape.setFillColor(sf::Color(color2.r - (color2.r * (1 - abs(cos)) / 1.25f), color2.g - (color2.g * (1 - abs(cos)) / 1.25f), color2.b - (color2.b * (1 - abs(cos)) / 1.25f)));
	shape.setPoint(0, points(0, 0).Isometric(window->getSize().x, window->getSize().y));
	shape.setPoint(1, points(0, 1).Isometric(window->getSize().x, window->getSize().y));
	shape.setPoint(2, points(1, 1).Isometric(window->getSize().x, window->getSize().y));
	shape.setPoint(3, points(1, 0).Isometric(window->getSize().x, window->getSize().y));
	window->draw(shape);
}

void FourPointLinearPlane::RotateX(float angl) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			points(i, j).RotateX(angl);
		}
	}
	setNorm();
}

void FourPointLinearPlane::RotateY(float angl) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			points(i, j).RotateY(angl);
		}
	}
	setNorm();
}

FourPointLinearPlane::~FourPointLinearPlane() {}
