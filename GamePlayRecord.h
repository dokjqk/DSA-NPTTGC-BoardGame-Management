//Name: Ansleigh, group 8, s10268445J
#pragma once
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

struct PlayerNode {
    int memberId;
    PlayerNode* next;
};

class GamePlayRecord
{
private:
    int gameId;
    std::string gameName;
    PlayerNode* winnerfirst; //List of winners
	PlayerNode* loserfirst;  //List of losers   
    time_t playDate;

    void addToList(PlayerNode*& head, int memberId);
    void deleteList(PlayerNode* head);
    bool isInList(PlayerNode* head, int memberId);
    void displayList(PlayerNode* head);
    int countList(PlayerNode* head);
    string listToString(PlayerNode* head);
    void stringToList(PlayerNode*& head, string& str);

public:
    GamePlayRecord();
    GamePlayRecord(int gameId, string gameName);
    ~GamePlayRecord();
    int getGameId();
    string getGameName();
    time_t getPlayDate();
    void addWinner(int memberId);
    void addLoser(int memberId);
    bool hasPlayer(int memberId);
    bool isWinner(int memberId);
    bool isLoser(int memberId);
    void display();
    int getTotalPlayers();
    string toCSVString();
    void fromCSVString(string& csvLine);
};

