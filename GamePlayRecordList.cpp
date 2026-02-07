//Name: Ansleigh, group 8, s10268445J
#include "GamePlayRecordList.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
GamePlayRecordList::GamePlayRecordList() {
    firstNode = nullptr;
    size = 0;
    csvFile = "gameplays.csv";
}

// Parameterized Constructor
GamePlayRecordList::GamePlayRecordList(string csvFileName) {
    firstNode = nullptr;
    size = 0;
    csvFile = csvFileName;
}

// Destructor
GamePlayRecordList::~GamePlayRecordList() {
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        GamePlayNode* temp = current;
        current = current->next;
        delete temp->item;
        delete temp;
    }
}

// Add a new game play record and save to csv
void GamePlayRecordList::addGamePlay(GamePlayRecord* gamePlay) {
    GamePlayNode* newNode = new GamePlayNode();
    newNode->item = gamePlay;
    newNode->next = firstNode;
    firstNode = newNode;
    size++;
    
    saveToCSV();
}

// display all gameplay records
void GamePlayRecordList::displayAll() {
    if (firstNode == nullptr) {
        std::cout << "No game plays recorded." << std::endl;
        return;
    }
    
    GamePlayNode* current = firstNode;
    int count = 1;
    while (current != nullptr) {
        std::cout << "\n--- Play Session " << count++ << " ---" << std::endl;
        current->item->display();
        current = current->next;
    }
}

// display gameplay records by game id
void GamePlayRecordList::displayByGame(int gameId) {
    GamePlayNode* current = firstNode;
    int count = 0;
    
    while (current != nullptr) {
        if (current->item->getGameId() == gameId) {
            if (count == 0) {
                std::cout << "\n--- Play History for Game: " << current->item->getGameName() << " ---" << std::endl;
            }
            std::cout << "\nSession " << ++count << ":" << std::endl;
            current->item->display();
        }
        current = current->next;
    }
    
    if (count == 0) {
        std::cout << "No plays recorded for this game." << std::endl;
    }
}

// display gameplay records by member id
void GamePlayRecordList::displayByMember(int memberId) {
    GamePlayNode* current = firstNode;
    int count = 0;
    int wins = 0, losses = 0;
    
    while (current != nullptr) {
        if (current->item->hasPlayer(memberId)) {
            if (count == 0) {
                std::cout << "\n--- Play History for Member ID " << memberId << " ---" << std::endl;
            }
            std::cout << "\nSession " << ++count << ":" << std::endl;
            current->item->display();
            
            if (current->item->isWinner(memberId)) wins++;
            if (current->item->isLoser(memberId)) losses++;
        }
        current = current->next;
    }
    
    if (count == 0) {
        std::cout << "No plays recorded for this member." << std::endl;
    } else {
        std::cout << "\nSummary: " << wins << " wins, " << losses << " losses" << std::endl;
    }
}

// display gameplay records by member id with pagination
void GamePlayRecordList::displayByMemberPaginated(int memberId, int startIdx, int count) {
    GamePlayNode* current = firstNode;
    int currentIndex = 0;
    int displayed = 0;
    
    while (current != nullptr && displayed < count) {
        if (current->item->hasPlayer(memberId)) {
            if (currentIndex >= startIdx) {
                std::cout << "\n--- Game #" << (currentIndex + 1) << " ---" << std::endl;
                current->item->display();
                
                if (current->item->isWinner(memberId)) {
                    std::cout << "Result: WIN" << std::endl;
                } else if (current->item->isLoser(memberId)) {
                    std::cout << "Result: LOSS" << std::endl;
                }
                
                displayed++;
            }
            currentIndex++;
        }
        current = current->next;
    }
    
    if (displayed == 0) {
        std::cout << "No records to display on this page." << std::endl;
    }
}

// get play count by game id
int GamePlayRecordList::getPlayCountByGame(int gameId) {
    int count = 0;
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        if (current->item->getGameId() == gameId) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// get play count by member id
int GamePlayRecordList::getPlayCountByMember(int memberId) {
    int count = 0;
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        if (current->item->hasPlayer(memberId)) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// get win count by member id
int GamePlayRecordList::getWinCountByMember(int memberId) {
    int count = 0;
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        if (current->item->isWinner(memberId)) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// get loss count by member id
int GamePlayRecordList::getLossCountByMember(int memberId) {
    int count = 0;
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        if (current->item->isLoser(memberId)) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// load game play records from CSV file
void GamePlayRecordList::loadFromCSV() {
    ifstream file(csvFile);
    if (!file.is_open()) {
        cout << "No existing game play records file found. Starting fresh." << endl;
        return;
    }
    
    string line;
	getline(file, line);
    int lineNumber = 0;
    int recordsLoaded = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        try {
            GamePlayRecord* record = new GamePlayRecord();
            record->fromCSVString(line);
            
            GamePlayNode* newNode = new GamePlayNode();
            newNode->item = record;
            newNode->next = firstNode;
            firstNode = newNode;
            size++;
            recordsLoaded++;
        }
        catch (const exception& e) {
            cout << "Error loading line " << lineNumber << ": " << e.what() << endl;
        }
    }
    
    file.close();
    cout << "Loaded " << recordsLoaded << " game play records from CSV." << endl;
}

// save the records to CSV file
void GamePlayRecordList::saveToCSV() {
    ofstream file(csvFile);
    if (!file.is_open()) {
        cout << "Failed to open CSV file for writing." << endl;
        return;
    }

    file << "GameID,GameName,WinnerIDs,LoserIDs,Timestamp" << endl;
    
    GamePlayNode* current = firstNode;
    while (current != nullptr) {
        file << current->item->toCSVString() << endl;
        current = current->next;
    }
    
    file.close();
}
