#pragma once
#include <string>
#include "Game.h"

class BorrowRecord {
private:
    int recordId;
    int memberId;
    Game game;
    std::string action;
    std::string date;

public:
    BorrowRecord();
    BorrowRecord(int rid, int mid, Game g, std::string act, std::string d);
    Game getGame() const;
    int getMemberId() const;
    std::string getAction() const;
    void display() const;
};
