#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Board.h"

using namespace std;

void revealNeighbors(Board &board, int i);
//void recurr(int i);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper!", sf::Style::Default);
	
	map<string, sf::Texture> textures;
	sf::Texture debug, digits, happy, lose, win, flag, mine, num1, num2, num3, num4, num5, num6, num7, num8, t1, t2, t3, tileH, tileR;

	debug.loadFromFile("images/debug.png");
	digits.loadFromFile("images/digits.png");
	happy.loadFromFile("images/face_happy.png");
	lose.loadFromFile("images/face_lose.png");
	win.loadFromFile("images/face_win.png");
	flag.loadFromFile("images/flag.png");
	mine.loadFromFile("images/mine.png");
	num1.loadFromFile("images/number_1.png");
	num2.loadFromFile("images/number_2.png");
	num3.loadFromFile("images/number_3.png");
	num4.loadFromFile("images/number_4.png");
	num5.loadFromFile("images/number_5.png");
	num6.loadFromFile("images/number_6.png");
	num7.loadFromFile("images/number_7.png");
	num8.loadFromFile("images/number_8.png");
	t1.loadFromFile("images/test_1.png");
	t2.loadFromFile("images/test_2.png");
	t3.loadFromFile("images/test_3.png");
	tileH.loadFromFile("images/tile_hidden.png");
	tileR.loadFromFile("images/tile_revealed.png");


	textures.emplace("debug" , debug);
	textures.emplace("digits", digits);
	textures.emplace("happy", happy);
	textures.emplace("lose", lose);
	textures.emplace("win", win);
	textures.emplace("flag", flag);
	textures.emplace("mine", mine);
	textures.emplace("1", num1);
	textures.emplace("2", num2);
	textures.emplace("3", num3);
	textures.emplace("4", num4);
	textures.emplace("5", num5);
	textures.emplace("6", num6);
	textures.emplace("7", num7);
	textures.emplace("8", num8);
	textures.emplace("test1", t1);
	textures.emplace("test2", t2);
	textures.emplace("test3", t3);
	textures.emplace("tileH", tileH);
	textures.emplace("tileR", tileR);

	//sprite stuff

	vector<sf::Sprite> hiddenTiles;//a vector of sprites 

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			sf::Sprite sprite;
			sprite.setTexture(textures["tileH"]);

			sprite.setPosition(i * 32,j * 32);
			hiddenTiles.push_back(sprite);
		}
		
		
	}

	sf::Sprite happySprite;
	happySprite.setTexture(textures["happy"]);
	happySprite.setPosition(520, 400);

	sf::Sprite loseSprite;
	loseSprite.setTexture(textures["lose"]);
	loseSprite.setPosition(520, 400);

	sf::Sprite winSprite;
	winSprite.setTexture(textures["win"]);
	winSprite.setPosition(520, 400);

	sf::Sprite debugSprite;
	debugSprite.setTexture(textures["debug"]);
	debugSprite.setPosition(584, 400);

	sf::Sprite test1;
	test1.setTexture(textures["test1"]);
	test1.setPosition(560, 512);

	sf::Sprite test2;
	test2.setTexture(textures["test2"]);
	test2.setPosition(624, 512);

	sf::Sprite test3;
	test3.setTexture(textures["test3"]);
	test3.setPosition(688, 512);
	
	Board board;
	board.createBoard(hiddenTiles);

	bool lost = false;
	bool won = false;
	bool debugB = false;

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))//polleven returns true if event pending, or false if there is none
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//cout << "Right click registered" << endl;
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;

					x /= 32;
					y /= 32;
					for (int i = 0; i < board.tiles.size(); i++)
					{
						if (board.tiles.at(i).x / 32 == x && board.tiles.at(i).y / 32 == y)
						{
							if (board.tiles.at(i).flagStatus)
							{
								board.tiles.at(i).flagStatus = false;;
								break;
							}
							else if (board.tiles.at(i).revealed)
							{
								break;//dont add a flag
							}
							else
							{
								board.tiles.at(i).flagStatus = true;
								break;
							}

						}
					}
					
				}
				else if (event.mouseButton.button == sf::Mouse::Left)
				{
					//cout << "Left click registered" << endl;
					int x = event.mouseButton.x;
					int y = event.mouseButton.y;

					//int faceX = x;
					//int faceY = y;
					if (lost)//if we lost
					{
						

						if (x >= 520 && x <= 584 && y >= 400 && y <= 464)//clicked on face
						{

							board.createBoard(hiddenTiles);
							lost = false;
						}

					}
					else if (won)//if we lost
					{


						if (x >= 520 && x <= 584 && y >= 400 && y <= 464)//clicked on face
						{

							board.createBoard(hiddenTiles);
							won = false;
						}

					}
					else if (x >= 584 && x <= 648 && y >= 400 && y <= 464)//clicked on debug
					{

						if (debugB)//means its already clicked
						{
							debugB = false;
						}
						else
						{
							debugB = true;
						}
						
					}
					else if (x >= 560 && x <= 624 && y >= 512 && y <= 576 )
					{
						board.createBoardT1(hiddenTiles);
					}
					else if(x >= 624 && x <= 688 && y >= 512 && y <= 576)
					{
						board.createBoardT2(hiddenTiles);
					}
					else if (x >= 688 && x <= 752 && y >= 512 && y <= 576)
					{
						board.createBoardT3(hiddenTiles);
					}
					else
					{
						if (x >= 520 && x <= 584 && y >= 400 && y <= 464)//clicked on face
						{
							board.createBoard(hiddenTiles);
						}
						x /= 32;
						y /= 32;
						for (int i = 0; i < board.tiles.size(); i++)
						{
							if (board.tiles.at(i).x / 32 == x && board.tiles.at(i).y / 32 == y)
							{
								if (board.tiles.at(i).flagStatus)
								{
									//do nothing
									break;
								}
								else if (board.tiles.at(i).bombStatus)//clicked on a bomb
								{
									board.tiles.at(i).clickedBomb = true;
									lost = true;
									break;
								}
								else//something else
								{
									board.tiles.at(i).revealed = true;//we revealed
									break;
								}

							}
						}
					}
				}
			}
			
		}

		window.clear();


		int flagcount = 0;
		
		for (int i = 0; i < board.tiles.size(); i++)
		{
			if (board.tiles.at(i).clickedBomb)
			{
				sf::Sprite revSprite;
				revSprite.setTexture(tileR);
				revSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

				sf::Sprite mineSprite;
				mineSprite.setTexture(mine);
				mineSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

				window.draw(revSprite);
				window.draw(mineSprite);
				
				

			}
			else if (board.tiles.at(i).flagStatus)
			{
				sf::Sprite flagSprite;
				flagSprite.setTexture(flag);
				flagSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

				window.draw(board.tiles.at(i).sprite);//regular tiles
				window.draw(flagSprite);//flag overlay
			}
			else if (board.tiles.at(i).revealed)
			{
				//figure out how many adjacent
				string num;
				
				num = to_string(board.tiles.at(i).surroundingMines);
				//cout << num << endl;


				sf::Sprite revealedSprite;
				revealedSprite.setTexture(textures["tileR"]);
				revealedSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

				window.draw(revealedSprite);//revealed tile

				sf::Sprite numSprite;
				if (!(num == "0"))
				{
					numSprite.setTexture(textures[num]);
					numSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);
					window.draw(numSprite);
				}
				else
				{
					revealNeighbors(board, i);
				}
			}
			else
			{
				
				window.draw(board.tiles.at(i).sprite);//regular tiles
			}
			
		}
		if (lost)
		{

			for (int i = 0; i < board.tiles.size(); i++)
			{
				if (board.tiles.at(i).bombStatus)
				{
					sf::Sprite revSprite;
					revSprite.setTexture(tileR);
					revSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

					sf::Sprite mineSprite;
					mineSprite.setTexture(mine);
					mineSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

					window.draw(revSprite);
					window.draw(mineSprite);
				}
			}

			window.draw(loseSprite);

		}
		else if (debugB)
		{
			for (int i = 0; i < board.tiles.size(); i++)
			{
				if (board.tiles.at(i).bombStatus)
				{
					sf::Sprite revSprite;
					revSprite.setTexture(tileR);
					revSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

					sf::Sprite mineSprite;
					mineSprite.setTexture(mine);
					mineSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

					window.draw(revSprite);
					window.draw(mineSprite);
					window.draw(happySprite);
				}
			}
		}

		else
		{
			int revealedCounter = 0;
			for (int i = 0; i < board.tiles.size(); i++)
			{
				if (board.tiles.at(i).revealed)
				{
					revealedCounter++;
				}
				
			}
			//cout << revealedCounter << endl;
			if (revealedCounter == 350)
			{
				won = true;
				window.draw(winSprite);
			}


			if (won)
			{
				for (int i = 0; i < board.tiles.size(); i++)
				{
					if (board.tiles.at(i).bombStatus)
					{
						sf::Sprite revSprite;
						revSprite.setTexture(tileR);
						revSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

						sf::Sprite flagSprite;
						flagSprite.setTexture(flag);
						flagSprite.setPosition(board.tiles.at(i).x, board.tiles.at(i).y);

						window.draw(revSprite);
						window.draw(flagSprite);
						window.draw(winSprite);
					}
				}
			}
			else
			{
				window.draw(happySprite);
			}
			
		}
		window.draw(test1);
		window.draw(test2);
		window.draw(test3);
		window.draw(debugSprite);
		window.display();
	}

	return 0;
}

void revealNeighbors(Board &board, int i)
{
	for (int j = 0; j < 8; j++)
	{
		if (board.tiles.at(i).neighbors[j] != nullptr)
		{
			if (!(board.tiles.at(i).neighbors[j]->bombStatus))
			{
				if (!(board.tiles.at(i).neighbors[j]->revealed))
				{
					board.tiles.at(i).neighbors[j]->revealed = true;

					if (board.tiles.at(i).neighbors[j]->surroundingMines == 0)
					{

						revealNeighbors(board, board.tiles.at(i).neighbors[j]->i);//this final i a variable of tile
					}
				}

			}
		}
			
				
	}
	
}
