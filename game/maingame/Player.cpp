#include "Player.h"

Player::Player()
{
	dir = direction::down;
	speed = 15;
	x = 100;
	y = 100;
	lives = 3;
	n = 0;
	img.loadFromFile("img/Player.png");
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,64,64));

	imgHeight = 64;
	imgWidth = 64;
};

void::Player::update()
{
	switch (dir)
	{
	case direction::down:
	{
		sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
		break;
	};
	case direction::up:
	{
		sprite.setTextureRect(sf::IntRect(64,192, 64, 64));
		break;
	};
	case direction::left:
	{
		sprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
		break;
	};
	case direction::right:
	{
		sprite.setTextureRect(sf::IntRect(64, 128, 64, 64));
		break;
	};
	}
	sprite.setPosition(x, y);
};

void::Player::setDir(direction dir)
{
	this->dir = dir;
};

void::Player::move(float dT)
{
	switch (dir)
	{
	case direction::down: 
	{
		if (n > 3) 
		{
			n = 0; 
		}
		sprite.setTextureRect(sf::IntRect(64* (int)n, 0, 64, 64));
		n+=dT;
		y += speed*dT;
		sprite.move(0, speed * dT);
		break;
	};
	case direction::up: 
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * (int)n, 192, 64, 64));
		n +=dT;
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
		sprite.setTextureRect(sf::IntRect(64 * (int)n, 64, 64, 64));
		n += dT;
		x -=  speed * dT;
		sprite.move(-(speed * dT), 0);
		break;
	};
	case direction::right: 
	{
		if (n > 3)
		{
			n = 0;
		}
		sprite.setTextureRect(sf::IntRect(64 * (int)n, 128, 64, 64));
		n += dT;
		x += speed * dT;
		sprite.move(speed * dT, 0);
		break;
	};
	}
}
void Player::setYPos(float y)
{
	this->y = y;
};

void Player::setXPos(float x)
{
	this->x = x;
};