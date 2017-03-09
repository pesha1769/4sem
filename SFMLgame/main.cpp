#include <SFML\Graphics.hpp>
#define HERO_SIZE 60

struct Bullet
{
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Sprite bullet;

	void update(float dt)
	{
		pos += vel * dt ;
	}
};

int main()
{
	const int Widht = 800;
	const int Height = 600;
	float Max_velocity = 300;
	float Prev_time = 0;
	const float Pi = 3.14159f;

	sf::RenderWindow window(sf::VideoMode(Widht, Height), "My window");
	sf::Clock clock;
	sf::Event event;


	sf::Texture textureHero;
	textureHero.loadFromFile("bat.png");
	sf::Sprite circle(textureHero);
	
	sf::Texture textureBullet;
	textureBullet.loadFromFile("bullet.png");

	Bullet bul;
	std::vector <Bullet> bullets;
	bullets.reserve(1000);

	circle.setPosition(400, 300);
	sf::Vector2u circleSize = circle.getTexture()->getSize();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}

		sf::Time time = clock.getElapsedTime();
	
		sf::Vector2u circleSize = circle.getTexture()->getSize();
		circle.setOrigin((float)circleSize.x / 2, (float)circleSize.y / 2);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = circle.getPosition();
		sf::Vector2f d = sf::Vector2f((float)mousePosition.x, (float)mousePosition.y) - center;
		circle.setRotation(60 + atan2f(d.y, d.x) * 180 / Pi);
		circle.setScale(0.4f, 0.4f);
		
		window.clear(sf::Color::Blue);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (center.x > HERO_SIZE))
		{
			circle.move((-time.asSeconds() + Prev_time) * Max_velocity, 0);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (center.x + HERO_SIZE < Widht))
		{
			circle.move((time.asSeconds() - Prev_time) * Max_velocity, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (center.y > HERO_SIZE))
		{
			circle.move(0, (-time.asSeconds() + Prev_time) * Max_velocity);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (center.y + HERO_SIZE < Height))
		{
			circle.move(0, (time.asSeconds() - Prev_time) * Max_velocity);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{				
				bul.bullet.setTexture(textureBullet);
				bul.bullet.setOrigin((float)circleSize.x / 2, (float)circleSize.y / 2);
				bul.bullet.setScale(0.3f, 0.3f);
				bul.vel = d / sqrt(d.x * d.x + d.y * d.y);
				bul.pos = center + bul.vel * (float)( circleSize.x / 4);
				bul.bullet.setRotation(90 + (float)(atan2f(d.y, d.x) * 180 / Pi));
				bul.bullet.setPosition(bul.pos);
				bullets.push_back(bul);			
		}
		

		for (auto current = bullets.begin(); current != bullets.end(); current++)
		{
			current->update(static_cast<float>(time.asSeconds() - Prev_time + 1));
			current->bullet.setPosition(current->pos);
			window.draw(current->bullet);

			if (!((center.x < Widht) && (center.x > 0) && (center.y < Height) && (center.y > 0)))
			{
				bullets.erase(current);
				current--;
			}

		}

		Prev_time = time.asSeconds();
		window.draw(circle);
		window.display();
	}
	return 0;
}
