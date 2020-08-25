#include "Board.h"

Board::Board()
{
	mineMax = 50;
}


void Board::createBoard(vector<sf::Sprite> &hiddenTiles)//this is all the sprites
{
	tiles.clear();
	bool mines[400];
	for (int c = 0; c < 400; c++)
	{
		mines[c] = false;
	}

	int randomNum;
	int mineCounter = 0;

	
	while (mineCounter < mineMax)
	{
		randomNum = rand() % 400;
		
		if (mines[randomNum] == false)
		{
			
			mines[randomNum] = true;
			mineCounter++;
		}
	}
	
	int counter = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)	
		{
			int x = i * 32;
			int y = j * 32;

			
			Tile tile(x, y, hiddenTiles.at(counter), mines[counter], counter);
			counter++;
			tiles.push_back(tile);
			
		}
		
		
	}
	setNeighbors();
}

void Board::setNeighbors()
{
	for (int index = 0; index < tiles.size(); index++)
	{
		if (index == 0) //top left corner
		{
			tiles.at(index).neighbors[0] = nullptr;
			tiles.at(index).neighbors[1] = nullptr;
			tiles.at(index).neighbors[2] = nullptr;
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = &tiles.at(index + 25 + 1);
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = nullptr;
			tiles.at(index).neighbors[7] = nullptr;
		}
		else if (index == 24)//top right corner
		{
			tiles.at(index).neighbors[0] = nullptr;
			tiles.at(index).neighbors[1] = nullptr;
			tiles.at(index).neighbors[2] = nullptr;
			tiles.at(index).neighbors[3] = nullptr;
			tiles.at(index).neighbors[4] = nullptr;
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = &tiles.at(index + 25 - 1);
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}
		else if (index == 375)//bottom left
		{
			tiles.at(index).neighbors[0] = nullptr;
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = &tiles.at(index - 25 + 1);
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = nullptr;
			tiles.at(index).neighbors[5] = nullptr;
			tiles.at(index).neighbors[6] = nullptr;
			tiles.at(index).neighbors[7] = nullptr;
		}
		else if (index == 399)//bottom right
		{
			tiles.at(index).neighbors[0] = &tiles.at(index - 25 - 1);
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = nullptr;
			tiles.at(index).neighbors[3] = nullptr;
			tiles.at(index).neighbors[4] = nullptr;
			tiles.at(index).neighbors[5] = nullptr;
			tiles.at(index).neighbors[6] = nullptr;
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}
		else if (index % 25 == 24)//right edge
		{
			tiles.at(index).neighbors[0] = &tiles.at(index - 25 - 1);
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = nullptr;
			tiles.at(index).neighbors[3] = nullptr;
			tiles.at(index).neighbors[4] = nullptr;
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = &tiles.at(index + 25 - 1);
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}
		else if (index % 25 == 0)//left side edge
		{
			tiles.at(index).neighbors[0] = nullptr;
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = &tiles.at(index - 25 + 1);
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = &tiles.at(index + 25 + 1);
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = nullptr;
			tiles.at(index).neighbors[7] = nullptr;
		}
		else if (index > 0 && index < 24)//top 
		{
			tiles.at(index).neighbors[0] = nullptr;
			tiles.at(index).neighbors[1] = nullptr;
			tiles.at(index).neighbors[2] = nullptr;
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = &tiles.at(index + 25 + 1);
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = &tiles.at(index + 25 - 1);
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}
		else if (index > 375 && index < 399)//bottom edge
		{
			tiles.at(index).neighbors[0] = &tiles.at(index - 25 - 1);
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = &tiles.at(index - 25 + 1);
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = nullptr;
			tiles.at(index).neighbors[5] = nullptr;
			tiles.at(index).neighbors[6] = nullptr;
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}
		else//shmee
		{
			tiles.at(index).neighbors[0] = &tiles.at(index - 25 - 1);
			tiles.at(index).neighbors[1] = &tiles.at(index - 25);
			tiles.at(index).neighbors[2] = &tiles.at(index - 25 + 1);
			tiles.at(index).neighbors[3] = &tiles.at(index + 1);
			tiles.at(index).neighbors[4] = &tiles.at(index + 25 + 1);
			tiles.at(index).neighbors[5] = &tiles.at(index + 25);
			tiles.at(index).neighbors[6] = &tiles.at(index + 25 - 1);
			tiles.at(index).neighbors[7] = &tiles.at(index - 1);
		}

		int number = 0;
		for (int j = 0; j < 8; j++)
		{
			if (!(tiles.at(index).neighbors[j] == nullptr))
			{
				if (tiles.at(index).neighbors[j]->bombStatus)
				{
					number++;
				}

			}
		}
		tiles.at(index).surroundingMines = number;
	}

}

void Board::createBoardT1(vector<sf::Sprite> &hiddenTiles)
{
	tiles.clear();
	readFile("boards/testboard1.brd", hiddenTiles);

}

void Board::createBoardT2(vector<sf::Sprite> &hiddenTiles)
{
	tiles.clear();
	readFile("boards/testboard2.brd", hiddenTiles);
}

void Board::createBoardT3(vector<sf::Sprite> &hiddenTiles)
{
	tiles.clear();
	readFile("boards/testboard3.brd", hiddenTiles);
}
void Board::readFile(const char* filename, vector<sf::Sprite> &hiddenTiles)
{
	ifstream file;
	file.open(filename);

	string token = "";

	bool mines[400];
	for (int c = 0; c < 400; c++)
	{
		mines[c] = false;
	}
	int i = 0;
	
	if (file.is_open())
	{
		int counter = 0;
		while (!file.eof())
		{
			file >> token;
			cout << token << endl;

			for (i = 0; i < token.length(); i++)
			{
				if (token[i] == '1')
				{
					mines[counter] = true;
				}
				counter++;
			}
			
		}
	}
	else
	{
		cout << "File not opened :(" << endl;
	}

	int counter = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int x = i * 32;
			int y = j * 32;


			Tile tile(x, y, hiddenTiles.at(counter), mines[counter], counter);
			counter++;
			tiles.push_back(tile);

		}


	}
	setNeighbors();

}