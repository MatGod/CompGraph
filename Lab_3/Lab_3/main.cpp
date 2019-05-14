#include <SFML\Graphics.hpp>
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\io.hpp>

#include "Point.h"
#include "FourPointLinearPlane.h"

using namespace boost::numeric::ublas;



int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	float ww = 1366, wh = 768;
	sf::RenderWindow window(sf::VideoMode(ww, wh), "Lab_3", sf::Style::Default, settings);

	matrix<Point> m(2, 2);
	m(0, 0) = Point(-300, -200, 0);
	m(0, 1) = Point(300, -200, 0);
	m(1, 0) = Point(-300, -200, 300);
	m(1, 1) = Point(300, -200, 300);

	FourPointLinearPlane plane(m);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up)	plane.RotateX(1);
				if (event.key.code == sf::Keyboard::Down) plane.RotateX(-1);
				if (event.key.code == sf::Keyboard::Left) plane.RotateY(1);
				if (event.key.code == sf::Keyboard::Right) plane.RotateY(-1);
				break;

			case sf::Event::Closed:
				window.close();
				break;
			}

			window.clear();
			plane.Draw(&window, sf::Color::Green);
			window.display();
		}
	}
	return 0;
}