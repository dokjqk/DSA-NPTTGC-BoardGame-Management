/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
------------------------------------------------------------
*/
#include "BorrowRecordDictionary.h"
#include <iostream>

BorrowRecordDictionary::BorrowRecordDictionary() {
    array = new RecordNode * [tableSize];
    for (int i = 0; i < tableSize; i++) {
        array[i] = nullptr;
    }
    nextRecordId = 1;
}

BorrowRecordDictionary::~BorrowRecordDictionary() {
    for (int i = 0; i < tableSize; i++) {
        RecordNode* current = array[i];
        while (current != nullptr) {
            RecordNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] array;
}

int BorrowRecordDictionary::hash(std::string gameName) const {
    int hashValue = 0;
    const int p = 31;

    for (int i = 0; i < gameName.length(); i++) {
        hashValue = (hashValue * p + gameName[i]) % tableSize;
    }

    return hashValue;
}


bool BorrowRecordDictionary::borrowGame(int memberId, Game& game, std::string date) {
    if (game.checkIfBorrowed()) {
        return false;
    }

    BorrowRecord newRecord = BorrowRecord(nextRecordId++, memberId, game, "Borrow", date);

    int index = hash(game.getName());
    RecordNode* newNode = new RecordNode;
    newNode->item = newRecord;
    newNode->next = array[index];
    array[index] = newNode;

    game.borrow();
    return true;
}

bool BorrowRecordDictionary::returnGame(int memberId, Game& game, std::string date) {
    if (!game.checkIfBorrowed()) {
        return false;
    }

    BorrowRecord newRecord = BorrowRecord(nextRecordId++, memberId, game, "Return", date);
    int index = hash(game.getName());
    RecordNode* newNode = new RecordNode;
    newNode->item = newRecord;
    newNode->next = array[index];
    array[index] = newNode;

    game.returnGame();
    return true;
}

void BorrowRecordDictionary::displayAll() const {
    for (int i = 0; i < tableSize; i++) {
        RecordNode* current = array[i];
        while (current != nullptr) {
            current->item.display();
            current = current->next;
        }
    }
}
void BorrowRecordDictionary::displayByGame(Game& game) const {
    int index = hash(game.getName());
    RecordNode* current = array[index];

    while (current != nullptr) {
        if (current->item.getGame().getGameId() == game.getGameId()) {
            current->item.display();
        }
        current = current->next;
    }
}

void BorrowRecordDictionary::displayByMember(int memberId) const {
    for (int i = 0; i < tableSize; i++) {
        RecordNode* current = array[i];
        while (current != nullptr) {
            if (current->item.getMemberId() == memberId) {
                current->item.display();
            }
            current = current->next;
        }
    }
}

