#include "Tile.h"

Tile::Tile()
{

}
Tile::Tile(int x, int y, sf::Sprite &s, bool status, int index)
{
	this->x = x;
	this->y = y;
	sprite = s;
	bombStatus = status;
	i = index;
}

