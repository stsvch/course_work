#pragma once
#include "Opponent.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>

class IFile
{
public:
	IFile();
	string path = "config.ini";
	void save(Map map, Player player, vector<Opponent> o, Floor floorNumber, int heartCount, vector<sf::Vector2f> heartPos);
	void load(Map& map, Player &player, vector<Opponent> &o, Floor &floorNumber, int &heartCount, vector<sf::Vector2f> &heartPos);
private:
	std::map<std::string, std::map<std::string, std::string>> config;
};

