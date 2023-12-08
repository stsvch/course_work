#pragma once
#include "Player.h"

class Opponent 
{
private:
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	bool detected;
	float n;
	float speed;
	float x;
	float y;
	direction dir;
	int imgHeight;
	int imgWidth;
public:
	Opponent();
	void move(float dT);
	sf::Sprite getSprite() { return sprite; };
	void update();
	direction getDir() { return dir; };
	float getXPos() { return x; };
	float getYPos() { return y; };
	int getHeight() { return imgHeight; };
	int getWidth() { return imgWidth; };
	bool itsDetected() { return detected; };
	void setDetection(bool f) { detected = f; };
	void setDir(direction dir) { this->dir = dir; };
	void setPos(sf::Vector2f v) { x = v.x; y = v.y; };
	void setYPos(float y) { this->y = y; };
	void setXPos(float x) { this->x = x; };
};

