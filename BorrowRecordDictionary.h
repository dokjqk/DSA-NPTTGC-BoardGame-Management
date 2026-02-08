/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
------------------------------------------------------------
*/
#pragma once
#include <string>
#include "BorrowRecord.h"
#include "Game.h"

class BorrowRecordDictionary {
private:
    struct RecordNode {
        BorrowRecord item;
        RecordNode* next;
    };

    RecordNode** array;
    int tableSize = 109;
    int nextRecordId;

    int hash(std::string gameName) const;

public:
    BorrowRecordDictionary();
    ~BorrowRecordDictionary();

    bool borrowGame(int memberId, Game& game, std::string date);
    bool returnGame(int memberId, Game& game, std::string date);

    void displayAll() const;
    void displayByGame(Game& game) const;
    void displayByMember(int memberId) const;
};
