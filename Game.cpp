#include "Game.h"
#include <string>
using namespace std;


Game::Game(){
}

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

int Game::getGameId() {
	return gameId;
}

string Game::getName() const {
	return name;
}

int Game::getMinPlayers() {
	return minPlayers;
}
int Game::getMaxPlayers() {
	return maxPlayers;
}

bool Game::canPlay(int playerCount) {
	return (playerCount >= minPlayers && playerCount <= maxPlayers);
}

bool Game::borrow() {
	if (isBorrowed) {
		return false;
	}
	else {
		isBorrowed = true;
		return true;
	}
}

bool Game::returnGame() {
	if (isBorrowed) {
		isBorrowed = false;
		return true;
	}
	else {
		return false;
	}
}

int Game::getYearPublished() {
	return yearPublished;
}

int Game::getMinPlayTime() {
	return minPlayTime;
}

int Game::getMaxPlayTime(){
	return maxPlayTime; 
}

void Game::display() {
	cout << "Game ID: " << gameId << endl;
	cout << "Name: " << name << endl;
	cout << "Players: " << minPlayers << " - " << maxPlayers << endl;
	cout << "Play Time: " << minPlayTime << " - " << maxPlayTime << " minutes" << endl;
	cout << "Year Published: " << yearPublished << endl;
	cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
}

bool Game::checkIfBorrowed() {
	return isBorrowed;
}