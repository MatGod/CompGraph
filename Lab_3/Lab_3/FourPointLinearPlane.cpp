#include "FourPointLinearPlane.h"



FourPointLinearPlane::FourPointLinearPlane() {}

FourPointLinearPlane::FourPointLinearPlane(matrix<Point> m) {
	points.resize(2, 2);
	points = m;
}

void FourPointLinearPlane::Draw(sf::RenderWindow* window, sf::Color color) {
	sf::ConvexShape shape;
	shape.setPointCount(4);
	shape.setFillColor(color);
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
}

void FourPointLinearPlane::RotateY(float angl) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			points(i, j).RotateY(angl);
		}
	}
}

FourPointLinearPlane::~FourPointLinearPlane() {}
