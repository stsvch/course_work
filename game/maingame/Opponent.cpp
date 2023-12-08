#include "Opponent.h"

Opponent::Opponent()
{
	n = 0;
	dir = direction::down;
	detected = false;
	speed = 8;
	x = 100;
	y = 100;
	img.loadFromFile("img/Enemy.png");
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	imgHeight = 64;
	imgWidth = 64;
}

void Opponent::move(float dT)
{
	switch (dir)
	{
	case direction::down:
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * int(n), 0, 64, 64));
		n += dT;
		y += speed * dT;
		sprite.move(0, speed * dT);
		break;
	};
	case direction::up:
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * int(n), 192, 64, 64));
		n += dT;
		y -= speed * dT;
		sprite.move(0, -(speed * dT));
		break;
	};
	case direction::left:
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * int(n), 64, 64, 64));
		n += dT;
		x -= speed * dT;
		sprite.move(-(speed * dT), 0);
		break;
	};
	case direction::right:
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * int(n), 128, 64, 64));
		n += dT;
		x += speed * dT;
		sprite.move(speed * dT, 0);
		break;
	};
	}
}

void Opponent::update()
{
	sprite.setPosition(x, y);
}
