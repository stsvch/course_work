#pragma once
#include <SFML/Graphics.hpp> 

enum class direction { up, down, right, left };
enum class Floor { first, second, third };

class Player
{
private:
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	float x;
	float y;
	direction dir;
	int imgHeight;
	int imgWidth;
	int lives;
	float n;
public:
	Player();
	void update();
	void setDir(direction dir);
	void move(float dT);
	sf::Sprite getSprite() { return sprite; };
	void decLives() { lives--; };
	int getLives() { return lives; };
	void setLives(int n) { lives = n; };
	float getXPos() { return sprite.getPosition().x; };
	float getYPos() { return sprite.getPosition().y; };
	void setYPos(float y);
	void setXPos(float x);
	int getHeight() { return imgHeight; };
	int getWidth() { return imgWidth; };
	void setPos(sf::Vector2f v) { x = v.x; y = v.y; };
	direction getDir() { return dir; };
	void setSpeed(float speed) { this->speed = speed; };
};

