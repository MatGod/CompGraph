#include <SFML\Graphics.hpp>
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\io.hpp>

using namespace boost::numeric::ublas;

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Lab_1", sf::Style::Fullscreen);
	//Круг 1(малый)
	sf::CircleShape circle_1(0.f);
	sf::Vector2f circle_1Pos;
	float circle_1Rad = 0.f;
	circle_1.setFillColor(sf::Color::Green);
	bool circle_1Ready = false;
	//Кру 2(большой)
	sf::CircleShape circle_2(0.f);
	sf::Vector2f circle_2Pos;
	float circle_2Rad = 0.f;
	circle_2.setFillColor(sf::Color::Yellow);
	bool circle_2Ready = false;
	//Касательные
	sf::VertexArray tang_1(sf::Lines, 2);
	tang_1[0].color = sf::Color::Blue;
	tang_1[1].color = sf::Color::Red;

	sf::VertexArray tang_2(sf::Lines, 2);
	tang_2[0].color = sf::Color::Blue;
	tang_2[1].color = sf::Color::Red;
	bool tangReady = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!circle_1Ready) { //Задание первого круга
				circle_1Pos.x = sf::Mouse::getPosition(window).x;
				circle_1Pos.y = sf::Mouse::getPosition(window).y;
				circle_1.setPosition(circle_1Pos);
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
				{
					circle_1.setPosition(circle_1Pos.x - circle_1Rad, circle_1Pos.y - circle_1Rad);
					circle_1Rad = sqrt(pow(abs(circle_1.getPosition().x + circle_1Rad - sf::Mouse::getPosition(window).x), 2) + pow(abs(circle_1.getPosition().y + circle_1Rad - sf::Mouse::getPosition(window).y), 2));
					circle_1.setRadius(circle_1Rad);
					window.clear();
					window.draw(circle_1);
					window.display();
				}
				circle_1Ready = true;
			}
			else if (!circle_2Ready) { //Задание второго круга
				circle_2Pos.x = sf::Mouse::getPosition(window).x;
				circle_2Pos.y = sf::Mouse::getPosition(window).y;
				circle_2.setPosition(circle_2Pos);
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle_2.setPosition(circle_2Pos.x - circle_2Rad, circle_2Pos.y - circle_2Rad);
					circle_2Rad = sqrt(pow(abs(circle_2.getPosition().x + circle_2Rad - sf::Mouse::getPosition(window).x), 2) + pow(abs(circle_2.getPosition().y + circle_2Rad - sf::Mouse::getPosition(window).y), 2));
					circle_2.setRadius(circle_2Rad);
					window.clear();
					window.draw(circle_1);
					window.draw(circle_2);
					window.display();
				}
				circle_2Ready = true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && (circle_1Ready || circle_2Ready)) { //Уничтожение нарисованных объектов
			circle_1.setRadius(0.f);
			tang_1[0].position = sf::Vector2f(0.f, 0.f);
			tang_1[1].position = sf::Vector2f(0.f, 0.f);
			tang_2[0].position = sf::Vector2f(0.f, 0.f);
			tang_2[1].position = sf::Vector2f(0.f, 0.f);
			circle_2.setRadius(0.f);
			circle_1Ready = false;
			circle_2Ready = false;
			tangReady = false;
		}

		if (circle_2Ready && !tangReady) { //Вычисление точек касания и отрисовка касательной
			if (circle_1Rad > circle_2Rad) {
				std::swap(circle_1, circle_2);
				std::swap(circle_1Pos, circle_2Pos);
				std::swap(circle_1Rad, circle_2Rad);
			}
			tang_1[0].position = circle_1Pos;
			float tangLength = sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2) - pow(circle_2Rad - circle_1Rad, 2));

			//Матрицы для операций поворота
			vector<float> point1Vector(3);
			matrix<float> moveMatrix(3, 3);
			matrix<float> rotateMatrix(3, 3);
			//Создание точки на отдалении в длину касательной от центра малой окружности
			point1Vector(0) = circle_1Pos.x + tangLength;
			point1Vector(1) = circle_1Pos.y;
			point1Vector(2) = 1.f;
			//Вспомогательная матрица для поворота
			moveMatrix(0, 0) = 1; moveMatrix(0, 1) = 0; moveMatrix(0, 2) = 0;
			moveMatrix(1, 0) = 0; moveMatrix(1, 1) = 1; moveMatrix(1, 2) = 0;
			moveMatrix(2, 0) = -circle_1Pos.x; moveMatrix(2, 1) = -circle_1Pos.y; moveMatrix(2, 2) = 1;
			//Основная матрица для поворота
			rotateMatrix(0, 0) = (circle_2Pos.x - circle_1Pos.x) / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));
			rotateMatrix(0, 1) = (circle_2Pos.y - circle_1Pos.y) / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));
			rotateMatrix(0, 2) = 0;
			//Вспомогательная матрица для поворота
			rotateMatrix(1, 0) = -rotateMatrix(0, 1);
			rotateMatrix(1, 1) = rotateMatrix(0, 0);
			rotateMatrix(1, 2) = 0;

			rotateMatrix(2, 0) = 0; rotateMatrix(2, 1) = 0; rotateMatrix(2, 2) = 1;
			//Первые два перемножения матриц для поворота
			point1Vector = prod(point1Vector, moveMatrix);
			point1Vector = prod(point1Vector, rotateMatrix);

			//На данном этапе точка лежит на расстоянии длины касательной от малой окружности в направлении центра большой окружности
			//В сдвинутой системе координат
			vector<float> point2Vector(3);
			//Поворот точки и её копии до параллельности текущих отрезков необходимым касательным

			point1Vector = prod(point1Vector, moveMatrix);
			point2Vector = point1Vector;

			rotateMatrix(0, 0) = tangLength / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));
			rotateMatrix(0, 1) = (circle_2Rad - circle_1Rad) / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));

			rotateMatrix(1, 0) = -rotateMatrix(0, 1);
			rotateMatrix(1, 1) = rotateMatrix(0, 0);

			point1Vector = prod(point1Vector, rotateMatrix);

			rotateMatrix(0, 0) = tangLength / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));
			rotateMatrix(0, 1) = -(circle_2Rad - circle_1Rad) / sqrt(pow(circle_2Pos.x - circle_1Pos.x, 2) + pow(circle_2Pos.y - circle_1Pos.y, 2));

			rotateMatrix(1, 0) = -rotateMatrix(0, 1);
			rotateMatrix(1, 1) = rotateMatrix(0, 0);

			point2Vector = prod(point2Vector, rotateMatrix);

			moveMatrix(2, 0) = circle_1Pos.x;
			moveMatrix(2, 1) = circle_1Pos.y;

			point1Vector = prod(point1Vector, moveMatrix);
			point2Vector = prod(point2Vector, moveMatrix);
			//"длина" и "ширина" касательных (длины их проекций на оси)
			float tang1Width = point1Vector(0) - circle_1Pos.x;
			float tang1Height = point1Vector(1) - circle_1Pos.y;

			float tang2Width = point2Vector(0) - circle_1Pos.x;
			float tang2Height = point2Vector(1) - circle_1Pos.y;
			//Параллельный сдвиг текущих отрезков до положения искомых касательных
			tang_1[1].position.x = point1Vector(0) + (point1Vector(0) - circle_2Pos.x) * (circle_1Rad / (circle_2Rad - circle_1Rad));
			tang_1[1].position.y = point1Vector(1) + (point1Vector(1) - circle_2Pos.y) * (circle_1Rad / (circle_2Rad - circle_1Rad));

			tang_1[0].position.x = tang_1[1].position.x - tang1Width;
			tang_1[0].position.y = tang_1[1].position.y - tang1Height;

			tang_2[1].position.x = point2Vector(0) + (point2Vector(0) - circle_2Pos.x) * (circle_1Rad / (circle_2Rad - circle_1Rad));
			tang_2[1].position.y = point2Vector(1) + (point2Vector(1) - circle_2Pos.y) * (circle_1Rad / (circle_2Rad - circle_1Rad));

			tang_2[0].position.x = tang_2[1].position.x - tang2Width;
			tang_2[0].position.y = tang_2[1].position.y - tang2Height;


			tangReady = true;
		}

		window.clear();
		window.draw(circle_1);
		window.draw(circle_2);
		window.draw(tang_1);
		window.draw(tang_2);
		window.display();
	}

	return 0;
}