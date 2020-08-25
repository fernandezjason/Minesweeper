#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
struct Tile
{

	int x, y;//postion
	int i;
	int surroundingMines = 0;
	sf::Sprite sprite;
	bool bombStatus = false;
	Tile* neighbors[8];
	bool flagStatus = false;
	bool clickedBomb = false;
	bool revealed = false;



	Tile();
	Tile(int x, int y, sf::Sprite &s, bool status, int index);


	

};