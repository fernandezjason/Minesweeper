#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Tile.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Board
{
	vector<Tile> tiles;
	int mineMax;
	void createBoard(vector<sf::Sprite> &hiddenTiles);
	void createBoardT1(vector<sf::Sprite> &hiddenTiles);
	void createBoardT2(vector<sf::Sprite> &hiddenTiles);
	void createBoardT3(vector<sf::Sprite> &hiddenTiles);
	void readFile(const char* filename, vector<sf::Sprite> &hiddenTiles);
	void setNeighbors();
	//void determineBomb();
	Board();
	

};
