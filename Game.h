#pragma once
#include <string>
#include <iostream>
using namespace std;

class Game
{
private:
	int gameId;
	string name;
	int minPlayers;
	int maxPlayers;
	int minPlayTime;
	int maxPlayTime;
	int yearPublished;
	bool isBorrowed;

public:
	Game(int id, string name, int minPlayers, int maxPlayers, int minPlayTime, int maxPlayTime, int yearPublished);
	Game();
	int getGameId();
	string getName() const;
	int getMinPlayers();
	int getMaxPlayers();
	bool canPlay(int playerCount);
	bool borrow();
	bool returnGame();
	int getYearPublished();
	void display();
	bool checkIfBorrowed();

};



