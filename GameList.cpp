//Name: Ansleigh, group 8, s10268445J

#include "GameList.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


//quickSort for all sort types
void GameList::quickSort(Game array[], int left, int right, SortType type)
{
	if (left < right) {

		int pivotIdx = partition(array, left, right, type);
		quickSort(array, left, pivotIdx - 1, type);
		quickSort(array, pivotIdx, right, type);
	}
}

int GameList::partition(Game array[], int left, int right, SortType type)
{
	Game pivot = array[(left+right)/2];
	//based on sort type, define comparison lambdas
	auto lessThan = [&](Game& a, Game& b) {
		switch (type) {
		case year:
			return a.getYearPublished() < b.getYearPublished();
		case name:
			return a.getName() < b.getName();
		case status:
			return a.checkIfBorrowed() < b.checkIfBorrowed();
		case ID:
			return a.getGameId() < b.getGameId();
		default:
			return false;
		}
		};

	auto greaterThan = [&](Game& a, Game& b) {
		switch (type) {
		case year:
			return a.getYearPublished() > b.getYearPublished();
		case name:
			return a.getName() > b.getName();
		case status:
			return a.checkIfBorrowed() > b.checkIfBorrowed();
		case ID:
			return a.getGameId() > b.getGameId();
		default:
			return false;
		}
		};
	
	
	while (left <= right) {

		while (lessThan(array[left], pivot)) { 
			left++;
		};
		while (greaterThan(array[right], pivot)) {
			right--;
		};

		if (left <= right) {
			swap(array[left], array[right]);
			left++;
			right--;
		}
	}
	return left;
}

// Constructor
GameList::GameList(int capacity, string filename)
{
	this->capacity = capacity;
	this->size = 0;
	this->csvFile = filename;

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

// Destructor
GameList::~GameList()
{
	delete[] items;
}

// Load games from a CSV file
void GameList::loadFromCSV(string filename)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return;
	}

	string line;
	int lineNumber = 0;
	int skippedLines = 0; //Document skipped lines

	getline(file, line);
	lineNumber++; // Skip header line

	while(getline(file, line)) {
		lineNumber++;

		if (line.empty()){
			continue;
		}
		// Check capacity if full
		if (size >= capacity) {
			cout << "GameList full at line " << lineNumber << ".\n";
			break;
		}

		bool lineValid = true;
		string name, temp;
		int minPlayers = 0, maxPlayers = 0, maxPlayTime = 0, minPlayTime = 0, yearPublished = 0;

		try {
			istringstream iss(line);

			// Parse name
			if (!line.empty() && line[0] == '"') {
				size_t endQuote = line.find("\",");
				if (endQuote == string::npos) {
					cout << "Line " << lineNumber << ": Malformed quoted name - " << line.substr(0, 50) << "...\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					name = line.substr(1, endQuote - 1);
					line = line.substr(endQuote + 2);
					iss.clear();
					iss.str(line);
				}
			}
			else {
				getline(iss, name, ',');
			}

			// Parse numeric fields only if line is valid
			if (lineValid) {
				if (!getline(iss, temp, ',') || temp.empty()) {
					cout << "Line " << lineNumber << ": Missing minPlayers\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					minPlayers = stoi(temp);
				}
			}

			if (lineValid) {
				if (!getline(iss, temp, ',') || temp.empty()) {
					cout << "Line " << lineNumber << ": Missing maxPlayers\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					maxPlayers = stoi(temp);
				}
			}

			if (lineValid) {
				if (!getline(iss, temp, ',') || temp.empty()) {
					cout << "Line " << lineNumber << ": Missing maxPlayTime\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					maxPlayTime = stoi(temp);
				}
			}

			if (lineValid) {
				if (!getline(iss, temp, ',') || temp.empty()) {
					cout << "Line " << lineNumber << ": Missing minPlayTime\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					minPlayTime = stoi(temp);
				}
			}

			if (lineValid) {
				if (!getline(iss, temp, ',') || temp.empty()) {
					cout << "Line " << lineNumber << ": Missing yearPublished\n";
					skippedLines++;
					lineValid = false;
				}
				else {
					yearPublished = stoi(temp);
				}
			}

			// If all fields are valid, create Game object
			if (lineValid) {
				Game newGame(size + 1, name, minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished);
				items[size] = newGame;
				size++;
			}
		}
		catch (const exception& e) {
			cout << "Line " << lineNumber << ": Exception - " << e.what() << " | Line content: " << line.substr(0, 80) << endl;
			skippedLines++;
		}
	}

	file.close(); //close the file
	cout << "\n=== CSV Load Summary ===\n";
	cout << "Total lines processed: " << lineNumber << endl;
	cout << "Games loaded: " << size << endl;
	cout << "Lines skipped: " << skippedLines << endl;
}

// Add a new game
void GameList::addGame(Game game)
{
	if (size >= capacity) {
		cout << "Game list is full. Cannot add more games." << endl;
		return;
	}

	game = Game(size + 1, game.getName(), game.getMinPlayers(), game.getMaxPlayers(), game.getMinPlayTime(), game.getMaxPlayTime(), game.getYearPublished());

	items[size] = game;
	size++;

	quickSort(items, 0, size - 1, name); // sort by alphabetical order after adding

	
	// Update CSV file
	ofstream file(csvFile);
	if (!file.is_open()) {
		cout << "Failed to open CSV for writing." << endl;
		size--;
		return;
	}

	file << "name,minplayers,maxplayers,maxplaytime,minplaytime,yearpublished\n";

	for (int i = 0; i < size; i++) {
		file << "\"" << items[i].getName() << "\","
			<< items[i].getMinPlayers() << ","
			<< items[i].getMaxPlayers() << ","
			<< items[i].getMaxPlayTime() << ","
			<< items[i].getMinPlayTime() << ","
			<< items[i].getYearPublished()
			<< "\n";
	}

	file.close();
	
	cout << "CSV file written successfully!" << endl;
}

// Remove a game by ID
bool GameList::removeGame(int id)
{
	int index = -1;
	for (int i = 0; i < size; i++) {
		if (items[i].getGameId() == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		cout << "Game not found.\n";
		return false;
	}

	
	for (int i = index; i < size - 1; i++) {
		items[i] = items[i + 1];
	}
	size--;

	for (int i = 0; i < size; i++) {
		items[i] = Game(i + 1, items[i].getName(), items[i].getMinPlayers(),items[i].getMaxPlayers(), items[i].getMinPlayTime(),items[i].getMaxPlayTime(), items[i].getYearPublished());
		
		if (items[i].checkIfBorrowed()) {
			items[i].borrow();
		}
	}

	quickSort(items, 0, size - 1, name); // sort by alphabetical order after removal

	ofstream out(csvFile); //redo csv file
	if (!out.is_open()) {
		cout << "Failed to open CSV for writing.\n";
		return false;
	}


	out << "Name,MinPlayers,MaxPlayers,MaxPlayTime,MinPlayTime,YearPublished\n";

	for (int i = 0; i < size; i++) {
		out << "\"" << items[i].getName() << "\","
			<< items[i].getMinPlayers() << ","
			<< items[i].getMaxPlayers() << ","
			<< items[i].getMaxPlayTime() << ","
			<< items[i].getMinPlayTime() << ","
			<< items[i].getYearPublished()
			<< endl;
	}

	out.close();

	cout << "Game removed and IDs updated.\n";
	return true;
}

// Find a game by ID
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
	quickSort(items, 0, size - 1, year);
}

void GameList::sortByName()
{
	quickSort(items, 0, size - 1, name);
}

void GameList::sortByBorrowedStatus()
{
	quickSort(items, 0, size - 1, status);
}

void GameList::sortById()
{
	quickSort(items, 0, size - 1, ID);
}

void GameList::displayAll() {
	for (int i = 0; i < size; i++) {
		items[i].display();
		cout << "------------------------" << endl;
	}
}

int GameList::binarySearchById(int id)
{
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = (left + right) / 2;

		if (items[mid].getGameId() == id)
			return mid;

		if (items[mid].getGameId() < id)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return -1;
}

int GameList::getSize() {
    return size;
}

Game* GameList::getGameAt(int index) {
    if (index >= 0 && index < size) {
        return &items[index];
    }
    return nullptr;
}
