#include <SFML\Graphics.hpp>

const int K = 2;
const int IterationCount = 50;
using Centroids = std::vector < sf::Color>;
using ClosestCentroidIndices = std::vector<int>;

struct ColorBuf
{
	int r, g, b, a;
	int count;
	ColorBuf& operator += (const sf::Color c)
	{
		count++;
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}
	
	ColorBuf& normalize()
	{
		if (count != 0)
		{
			r /= count;
			g /= count;
			b /= count;
		}
		return *this;
	}
};


Centroids initializeCentroids(const sf::Image& im , int k)
{
	Centroids c;
	c.resize(k);
	for (int i = 0; i < k; i++)
	{
		sf::Vector2u pix;
		pix.x = rand() % im.getSize().x;
		pix.y = rand() % im.getSize().y;

		c[i] = im.getPixel(pix.x, pix.y); 
	}
	return c;
}

ClosestCentroidIndices findClosestCentroids(const sf::Image& im, Centroids c)
{
	ClosestCentroidIndices Ids;
	Ids.resize(im.getSize().x * im.getSize().y);

	std::vector<int> length;
	length.resize(K);

	for (int i = 0; i < im.getSize().x; i++)
	{
		for (int j = 0; j < im.getSize().y; j++)
		{
			for (int k = 0; k < K; k++)
			{
				length[k] = sqrt((im.getPixel(i, j).r - c[k].r) * (im.getPixel(i, j).r - c[k].r) + (im.getPixel(i, j).g  - c[k].g) * (im.getPixel(i, j).g - c[k].g) +
					(im.getPixel(i, j).b - c[k].b) * (im.getPixel(i, j).b - c[k].b));
			}

			int min = length[0];
			int index = 0;

			for (int k = 0; k < K; k++)
			{
				if (min > length[k])
				{
					min = length[k];
					index = k;
				}

			}

			Ids[j * im.getSize().x + i] = index;
			
		}
	}
	return Ids;
}

Centroids computeMeans(sf::Image im, ClosestCentroidIndices ids, int k)
{
	Centroids c;
	c.resize(k);
	std::vector<ColorBuf> buf;
	buf.resize(k);

	for (int i = 0; i < ids.size(); i++)
	{
		buf[ids[i]] += im.getPixel(i % im.getSize().x, i / im.getSize().x);
	}
	
	for (int i = 0; i < k; i++)
	{
		buf[i].normalize();
	}
	
	for (int i = 0; i < K; i++)
	{
		c[i] = sf::Color(buf[i].r, buf[i].g, buf[i].b);

	}
	return c;

}

void changeColors(sf::Image& im, ClosestCentroidIndices ids, Centroids c)
{
	for (int i = 0; i < ids.size(); i++)
	{
		im.setPixel(i % im.getSize().x, i / im.getSize().x, c[ids[i]]);
	}

}





int main()
{


	sf::Texture texture;
	texture.loadFromFile("hero.png");
	auto image = texture.copyToImage();

	ClosestCentroidIndices ids;
	Centroids centroids = initializeCentroids(image, K);
	for (int it = 0; it < IterationCount; it++)
	{
		ids = findClosestCentroids(image, centroids);
		centroids = computeMeans(image, ids, K);		
	}
	changeColors(image, ids, centroids);

	texture.update(image);

	sf::Sprite photo;
	photo.setTexture(texture);

	sf::Vector2u photoSize = photo.getTexture()->getSize();
	sf::RenderWindow window(sf::VideoMode(photoSize.x, photoSize.y), "My window");

	


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.draw(photo);
		window.display();

	}


	
	
	return 0;
}
