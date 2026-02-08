//Name: Ansleigh, group 8, s10268445J

#pragma once
#include "Game.h"
#include <string>
using namespace std;


enum SortType {
    year,
    name,
    status,
    ID
};

class GameList
{
private:
    Game* items;
    int size;
    int capacity;
    string csvFile;

    void quickSort(Game array[], int left, int right, SortType type);
    int partition(Game array[], int left, int right, SortType type);

public:
    GameList(int capacity, string filename);
    ~GameList();

    void loadFromCSV(string filename);

    void addGame(Game game);
    bool removeGame(int id);

    Game* findById(int id);
    Game* findByName(string name);

    void listByPlayers(int players);
    void sortByYear();
	void sortByName();
	void sortByBorrowedStatus();
	void sortById();
    void displayAll();
    int binarySearchById(int id);
    int getSize();
    Game* getGameAt(int index);
};

