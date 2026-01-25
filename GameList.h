#pragma once
#include "Game.h"
#include <string>
using namespace std;



class GameList
{
private:
    Game* items;
    int size;
    int capacity;

    void quickSort(Game array[], int left, int right);
    int partition(Game array[], int left, int right);

public:
    GameList(int capacity);
    ~GameList();

    void loadFromCSV(string filename);

    void addGame(Game game);
    bool removeGame(int id);

    Game* findById(int id);
    Game* findByName(string name);

    void listByPlayers(int players);
    void sortByYear();
    void displayAll();

};

