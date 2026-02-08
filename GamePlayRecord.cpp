#include "GamePlayRecord.h"
#include <iostream>
#include <sstream>

// Constructor
GamePlayRecord::GamePlayRecord() {
    gameId = -1;
    gameName = "";
    winnerfirst = nullptr;
    loserfirst = nullptr;
    playDate = time(nullptr);
}

// Parameterized Constructor
GamePlayRecord::GamePlayRecord(int gId, std::string gName) {
    gameId = gId;
    gameName = gName;
    winnerfirst = nullptr;
    loserfirst = nullptr;
    playDate = time(nullptr);
}

// Destructor
GamePlayRecord::~GamePlayRecord() {
    deleteList(winnerfirst);
    deleteList(loserfirst);
}

// add member to list
void GamePlayRecord::addToList(PlayerNode*& head, int memberId) {
    PlayerNode* newNode = new PlayerNode();
    newNode->memberId = memberId;
    newNode->next = head;
    head = newNode;
}

// delete all members from list
void GamePlayRecord::deleteList(PlayerNode* head) {
    PlayerNode* current = head;
    while (current != nullptr) {
        PlayerNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// check if member is in list list
bool GamePlayRecord::isInList(PlayerNode* head, int memberId) {
    PlayerNode* current = head;
    while (current != nullptr) {
        if (current->memberId == memberId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// display list of member ids
void GamePlayRecord::displayList(PlayerNode* head) {
    if (head == nullptr) {
        cout << "None";
        return;
    }
    
    PlayerNode* current = head;
    bool first = true;
    while (current != nullptr) {
        if (!first) cout << ", ";
        cout << current->memberId;
        first = false;
        current = current->next;
    }
}

// count number of members in list
int GamePlayRecord::countList(PlayerNode* head) {
    int count = 0;
    PlayerNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

//convert list to string and vice versa
string GamePlayRecord::listToString(PlayerNode* head) {
    string result = "";
    PlayerNode* current = head;
    while (current != nullptr) {
        if (!result.empty()) {
            result += ";";
        }
        result += std::to_string(current->memberId);
        current = current->next;
    }
    return result.empty() ? "None" : result;
}

void GamePlayRecord::stringToList(PlayerNode*& head,string& str) {
    if (str == "None" || str.empty()) {
        return;
    }
    
    stringstream ss(str);
    string token;
    while (getline(ss, token, ';')) {
        if (!token.empty()) {
            int memberId = std::stoi(token);
            addToList(head, memberId);
        }
    }
}

//get game id, name, date
int GamePlayRecord::getGameId() {
    return gameId;
}

std::string GamePlayRecord::getGameName() {
    return gameName;
}

time_t GamePlayRecord::getPlayDate() {
    return playDate;
}

// add winner to list
void GamePlayRecord::addWinner(int memberId) {
    addToList(winnerfirst, memberId);
}

// add loser to list
void GamePlayRecord::addLoser(int memberId) {
    addToList(loserfirst, memberId);
}

// check if member played in a game
bool GamePlayRecord::hasPlayer(int memberId) {
    return isWinner(memberId) || isLoser(memberId);
}

// check if member is winner
bool GamePlayRecord::isWinner(int memberId) {
    return isInList(winnerfirst, memberId);
}

// check if member is loser
bool GamePlayRecord::isLoser(int memberId) {
    return isInList(loserfirst, memberId);
}

// display game play record of game name, winners, losers and date recorded
void GamePlayRecord::display() {
    cout << "Game: " << gameName << " (ID: " << gameId << ")" << std::endl;
    
    cout << "Winners (IDs): ";
    displayList(winnerfirst);
    cout << endl;
    
    cout << "Losers (IDs): ";
    displayList(loserfirst);
    cout << endl;
    
    char buffer[26];
	ctime_s(buffer, sizeof(buffer), &playDate); // convert time to string
    cout << "Date Played: " << buffer;
}

// get total players in game record
int GamePlayRecord::getTotalPlayers() {
    return countList(winnerfirst) + countList(loserfirst);
}

// convert to csv string
string GamePlayRecord::toCSVString() {
    stringstream ss;
    ss << gameId << ","
        << "\"" << gameName << "\","
        << listToString(winnerfirst) << ","
        << listToString(loserfirst) << ","
        << playDate;
    return ss.str();
}

// convert from csv string
void GamePlayRecord::fromCSVString(string& csvLine) {
    stringstream ss(csvLine);
    string token;
    string line = csvLine;  // Working copy
    
    // Field 0: gameId
    getline(ss, token, ',');
    gameId = stoi(token);
    
    // Remove gameId from line
    size_t firstComma = line.find(',');
    if (firstComma != string::npos) {
        line = line.substr(firstComma + 1);
    }
    
    // 
    if (!line.empty() && line[0] == '"') {
        size_t endQuote = line.find("\",");
        if (endQuote == string::npos) {
            
            gameName = line.substr(1);  
        }
        else {
            gameName = line.substr(1, endQuote - 1); 
            line = line.substr(endQuote + 2); 
        }
    }
    else {
       
        size_t nextComma = line.find(',');
        if (nextComma != string::npos) {
            gameName = line.substr(0, nextComma);
            line = line.substr(nextComma + 1);
        }
        else {
            gameName = line;
            line = "";
        }
    }

    ss.clear();
    ss.str(line);


    getline(ss, token, ',');
    stringToList(winnerfirst, token);


    getline(ss, token, ',');
    stringToList(loserfirst, token);


    getline(ss, token, ',');
    if (!token.empty()) {
        playDate = stoll(token);
    }
}