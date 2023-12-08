#pragma once
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

using namespace std; 

class Map
{
private:
	sf::Image keyImg;
	sf::Texture keyTexture;
	sf::Sprite keySprite;

	sf::Image liftImg;
	sf::Texture liftTexture;
	sf::Sprite liftSprite;
	float width;
	float height;
	int cols;
	int rows;
	int startX;
	int startY;
	vector<vector<int>> map;
	sf::Image imgWall;
	sf::Image imgFloor;
	sf::Texture textureWall;
	sf::Texture textureFloor;
	sf::Sprite spriteWall;
	sf::Sprite spriteFloor;
	void prepare();
	bool testXY(int y, int x);
	void testforDEADEND(int num);
	void near_finish(int num);
	sf::Vector2i keyPos;
	void setKeyPos();
	vector<int> points_x;  
	vector<int> points_y;
	int number;
	int end_x, end_y;
	bool key;
public:
	Map();
	~Map();
	void draw(sf::RenderWindow& window);
	bool itsWall(float height, float width);
	int getStartX() { return startX*96; };
	void setStartX(int x) { startX = x / 96; };
	void setStartY(int y) { startY = y / 96; };
	int getStartY() { return startY*96; };
	int getEndX() { return end_x*96; };
	void setEndX(int x) { end_x = x / 96; }
	int getEndY() { return end_y*96; }
	void setEndY(int y) { end_y = y / 96; }
	void mazemake();
	sf::Vector2f getPos();
	bool lee(int ax, int ay, int bx, int by, stack<int>& px, stack<int>& py);
	sf::Vector2i getKeyPos() { return keyPos; };
	void setKeyPosX(int x) { keyPos.x = x;};
	void setKeyPosY(int y) { keyPos.y = y;};
	void setKeySpritePos() { keySprite.setPosition((keyPos.x * 96) + 20, (keyPos.y * 96) + 20); };
	void setKey(bool key) {this->key = key;};
	bool getKey() { return key; }
	void changeFloor(string floor, string wall);
	vector<vector<int>> getMap() { return map; };
	void setMap(vector<vector<int>> map) { this->map = map; };
};