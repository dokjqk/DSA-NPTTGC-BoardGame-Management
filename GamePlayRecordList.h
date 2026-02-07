//Name: Ansleigh, group 8, s10268445J
#pragma once
#include "GamePlayRecord.h"
#include <string>
using namespace std;

struct GamePlayNode {
    GamePlayRecord* item;
    GamePlayNode* next;
};

class GamePlayRecordList {
private:
    
    
    GamePlayNode* firstNode;
    int size;
    string csvFile;
    
public:
    GamePlayRecordList();
    GamePlayRecordList(string csvFileName);
    ~GamePlayRecordList();
    void addGamePlay(GamePlayRecord* gamePlay);
    void displayAll();
    void displayByGame(int gameId);
    void displayByMember(int memberId);
    void displayByMemberPaginated(int memberId, int startIdx, int count);
    int getPlayCountByGame(int gameId);
    int getPlayCountByMember(int memberId);
    int getWinCountByMember(int memberId);
    int getLossCountByMember(int memberId);
    void loadFromCSV();
    void saveToCSV();
};

