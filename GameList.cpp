#include "GameList.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void GameList::quickSort(Game array[], int left, int right)
{
	if (left < right) {

		int pivotIdx = partition(array,left, right);
		quickSort(array,left, pivotIdx - 1);
		quickSort(array, pivotIdx, right);
	}
}

int GameList::partition(Game array[], int left, int right)
{
	Game pivot = array[(left+right)/2];
	
	while (left <= right){
		while (array[left].getYearPublished() < pivot.getYearPublished()) {
			left++;
		}
		while (array[right].getYearPublished() > pivot.getYearPublished()) {
			right--;
		}
		if (left <= right) {
			swap(array[left], array[right]);
			left++;
			right--;
		}
	}
	return left;
}


GameList::GameList(int capacity)
{
	this->capacity = capacity;
	this->size = 0;

	// allocate on heap
	try {
		items = new Game[capacity];
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Failed to allocate GameList: " << e.what() << std::endl;
		items = nullptr;
		this->capacity = 0;
	}
}

GameList::~GameList()
{
	delete[] items;
}

void GameList::loadFromCSV(string filename)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return;
	}

	string line;

	getline(file, line);

	while(getline(file, line)) {

		if (line.empty()){
			continue;
		}

		if (size >= capacity) {
			cout << "GameList full.\n";
			break;
		}

		istringstream iss(line);
		string name, temp;
		int minPlayers, maxPlayers, maxPlayTime, minPlayTime, yearPublished;

		if (line[0] == '"') {
			size_t endQuote = line.find("\",");
			name = line.substr(1, endQuote - 1);
			line = line.substr(endQuote + 2);
			iss.clear();
			iss.str(line);
		}
		else {
			getline(iss, name, ',');
		}

		try {
			if (!getline(iss, temp, ',')) continue;
			minPlayers = stoi(temp);

			if (!getline(iss, temp, ',')) continue;
			maxPlayers = stoi(temp);

			if (!getline(iss, temp, ',')) continue;
			maxPlayTime = stoi(temp);

			if (!getline(iss, temp, ',')) continue;
			minPlayTime = stoi(temp);

			if (!getline(iss, temp, ',')) continue;
			yearPublished = stoi(temp);
		}
		catch (const exception& e) {
			cout << "Skipping malformed line: " << line << endl;
			continue;
		}

		Game newGame(size + 1, name, minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished);
		addGame(newGame);
	}

	file.close();
}

void GameList::addGame(Game game)
{
	if (size < capacity) {
		items[size] = game;
		size++;
	}
	else {
		cout << "Game list is full. Cannot add more games." << endl;
		return;
	}
}

bool GameList::removeGame(int id)
{
	for (int i = 0; i < size; i++) {
		if (items[i].getGameId() == id) {
			for (int j = i; j < size - 1; j++) {
				items[j] = items[j + 1];
			}
			size--;
			return true;
		}
	}
	return false;
}

Game* GameList::findById(int id)
{
	for (int i = 0; i < size; i++) {
		if (items[i].getGameId() == id) {
			return &items[i];
		}
	}
	return nullptr;
}

Game* GameList::findByName(string name)
{
	for (int i = 0; i < size; i++) {
		if (items[i].getName() == name) {
			return &items[i];
		}
	}
	return nullptr;
}

void GameList::listByPlayers(int players)
{
	for (int i = 0; i < size; i++) {
		if (items[i].canPlay(players)) {
			items[i].display();
			cout << "------------------------" << endl;
		}
	}
}

void GameList::sortByYear()
{
	quickSort(items, 0, size - 1);
}

void GameList::displayAll() {
	for (int i = 0; i < size; i++) {
		items[i].display();
		cout << "------------------------" << endl;
	}
}
