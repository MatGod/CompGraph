#include <SFML\Graphics.hpp>
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\io.hpp>

#include "Point.h"

using namespace boost::numeric::ublas;



int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	float ww = 1366, wh = 768;
	sf::RenderWindow window(sf::VideoMode(ww, wh), "Lab_3", sf::Style::Default, settings);
	Point p1(300, 200, 0);
	Point p2(300, 200, 300);
	Point p3(-300, 200, 300);
	Point p4(-300, 200, 0);
	sf::ConvexShape shape;
	shape.setPointCount(4);
	shape.setFillColor(sf::Color::Green);
	shape.setPoint(0, p1.Isometric(ww, wh));
	shape.setPoint(1, p2.Isometric(ww, wh));
	shape.setPoint(2, p3.Isometric(ww, wh));
	shape.setPoint(3, p4.Isometric(ww, wh));
	Point p5(300, 200, 0);
	Point p6(300, 200, 300);
	Point p7(300, -400, 300);
	Point p8(300, -400, 0); 
	sf::ConvexShape shape1;
	shape1.setPointCount(4);
	shape1.setFillColor(sf::Color::Red);
	shape1.setPoint(0, p5.Isometric(ww, wh));
	shape1.setPoint(1, p6.Isometric(ww, wh));
	shape1.setPoint(2, p7.Isometric(ww, wh));
	shape1.setPoint(3, p8.Isometric(ww, wh));
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(shape1);
		window.display();
	}

	return 0;
}