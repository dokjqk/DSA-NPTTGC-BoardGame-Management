/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
Ansleigh Ong Hong Yi (S10268445J)
------------------------------------------------------------
*/
#include "Game.h"
#include <string>
using namespace std;

// Constructor
Game::Game(){
}

// Parameterized Constructor
Game::Game(int id, string name, int minPlayers, int maxPlayers, int minPlayTime, int maxPlayTime, int yearPublished) {
	Game::gameId = id;
	Game::name = name;
	Game::minPlayers = minPlayers;
	Game::maxPlayers = maxPlayers;
	Game::minPlayTime = minPlayTime;
	Game::maxPlayTime = maxPlayTime;
	Game::yearPublished = yearPublished;
	Game::isBorrowed = false;
}

// get game id
int Game::getGameId() {
	return gameId;
}

// get game name
string Game::getName() const {
    return name;
}

// get min and max players
int Game::getMinPlayers() {
	return minPlayers;
}
int Game::getMaxPlayers() {
	return maxPlayers;
}

// get year published
int Game::getYearPublished() {
	return yearPublished;
}

// get min and max play time
int Game::getMinPlayTime() {
	return minPlayTime;
}

int Game::getMaxPlayTime() {
	return maxPlayTime;
}

// check if game can be played by given number of players
bool Game::canPlay(int playerCount) {
	return (playerCount >= minPlayers && playerCount <= maxPlayers);
}

// borrow game
bool Game::borrow() {
	if (isBorrowed) {
		return false;
	}
	else {
		isBorrowed = true;
		return true;
	}
}

// return game
bool Game::returnGame() {
	if (isBorrowed) {
		isBorrowed = false;
		return true;
	}
	else {
		return false;
	}
}

// display game details
void Game::display() {
	cout << "Game ID: " << gameId << endl;
	cout << "Name: " << name << endl;
	cout << "Players: " << minPlayers << " - " << maxPlayers << endl;
	cout << "Play Time: " << minPlayTime << " - " << maxPlayTime << " minutes" << endl;
	cout << "Year Published: " << yearPublished << endl;
	cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
}

// check if game is borrowed
bool Game::checkIfBorrowed() {
	return isBorrowed;
}

// add review to game
void Game::addReview(int memberId, int rating, std::string comment) {
	Review r(memberId, rating, comment);
	reviews.addReview(r);
}

// display all reviews for the game
void Game::displayReviews() {
	reviews.displayAll();
}