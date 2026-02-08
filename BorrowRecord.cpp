/*
------------------------------------------------------------
Hendi Wong Jia Ming (S10270162K)
------------------------------------------------------------
*/
#include "BorrowRecord.h"
#include "Game.h"
#include <iostream>


BorrowRecord::BorrowRecord() {
	recordId = -1;
	memberId = -1;
	game = Game();
	action = "";
	date = "";
}

BorrowRecord::BorrowRecord(int rId, int mId, Game g, std::string act, std::string d) {
	recordId = rId;
	memberId = mId;
	game = g;
	action = act;
	date = d;
}
Game BorrowRecord::getGame() const {
	return game;
}
int BorrowRecord::getMemberId() const {
	return memberId;
}
std::string BorrowRecord::getAction() const {
	return action;
}
void BorrowRecord::display() const {
	std::cout << memberId << " | "
		<< game.getName() << " | "
		<< action << " | "
		<< date << std::endl;
}