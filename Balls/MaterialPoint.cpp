#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include <vector>

sf::Vector2i convert(const Vector2 v)
{
	return sf::Vector2i(v.x, v.y);
}

Vector2 convert2(const sf::Vector2i v)
{
	return Vector2(v.x, v.y);
}


int main()
{
	const int Widht = 800;
	const int Height = 600;
	float Prev_time = 0, Delta_time;

	sf::RenderWindow window(sf::VideoMode(Widht, Height), "My window");
	sf::Event event;
	sf::Clock clock;
	std::vector <Ball> balls;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		sf::Time time = clock.getElapsedTime();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			Ball ball;

			ball.position = convert2(mousePosition);
			ball.velocity = convert2(sf::Vector2i(rand() % 100, rand() % 100));
			ball.radius = (rand() % 5) * 5;
			ball.mass = ball.radius / 5;
			balls.push_back(ball);
		}

		window.clear(sf::Color::White);
		
		for (int i = 0; i < balls.size(); ++i)
		{
			sf::CircleShape ball(balls[i].radius);

			ball.setOrigin(balls[i].radius, balls[i].radius);
			ball.setPosition(balls[i].position.x, balls[i].position.y);

			ball.setFillColor(sf::Color::Red);

			window.draw(ball);

			balls[i].UpdatePosition(Delta_time);

			if (balls[i].position.x - balls[i].radius <= 0 || balls[i].position.x + balls[i].radius > Widht) 
			{
				balls[i].velocity.x *= -1;
			}
			if (balls[i].position.y - balls[i].radius <= 0 || balls[i].position.y + balls[i].radius > Height) 
			{
				balls[i].velocity.y *= -1;
			}
		
			for (int j = 0; j < balls.size(); ++j) 
			{

				Vector2 Delta = balls[j].position - balls[i].position + Vector2(balls[j].radius - balls[i].radius, balls[j].radius - balls[i].radius);
				Vector2 Delta_Velocity = balls[j].velocity - balls[i].velocity;

				if ((Delta.len() <= balls[i].radius + balls[j].radius) && (Delta_Velocity * Delta < 0))
				{
					Vector2 Delta_impulse = 2 * (Delta_Velocity / (1 / balls[j].mass + 1 / balls[i].mass)) * Delta.norm() * Delta.norm();
					balls[i].velocity += Delta_impulse / balls[i].mass;
					balls[j].velocity -= Delta_impulse / balls[j].mass;
				}

			}
			
		}

		Delta_time = time.asSeconds() - Prev_time;
		Prev_time = time.asSeconds();
		window.display();
	}
	return 0;
}