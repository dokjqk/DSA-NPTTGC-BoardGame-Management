/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
Ansleigh Ong Hong Yi (S10268445J)
------------------------------------------------------------
*/
#pragma once
#include <string>
#include <iostream>
#include "ReviewList.h"
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
	ReviewList reviews;

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
	int getMinPlayTime();
	int getMaxPlayTime();
	void display();
	bool checkIfBorrowed();
	void addReview(int memberId, int rating, std::string comment);
	void displayReviews();
};



