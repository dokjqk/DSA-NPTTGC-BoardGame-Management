// DSA-NPTTGC-BoardGame-Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Member.h"
#include "MemberList.h"
#include "Game.h"
#include "GameList.h"
#include "BorrowRecordDictionary.h"

int main() {
    std::cout << "testing member class" << std::endl;

    Member m1(1, "alice");
    Member m2(2, "bob");
    Member m3(3, "charlie");

    m1.display();
    m2.display();
    m3.display();

    std::cout << "\ntesting memberlist class" << std::endl;

    MemberList memberList;

    std::cout << "\nadding members..." << std::endl;
    memberList.addMember(m1);
    memberList.addMember(m2);
    memberList.addMember(m3);

    std::cout << "\ndisplaying all members:" << std::endl;
    memberList.displayAll();

    std::cout << "\nfinding member of id 2:" << std::endl;
    Member* found = memberList.findById(2);
    if (found != nullptr) {
        found->display();
    }
    else {
        std::cout << "member not found" << std::endl;
    }

    std::cout << "\nremoving member with id 1" << std::endl;
    memberList.removeMember(1);

    std::cout << "\ndisplaying all members after removing:" << std::endl;
    memberList.displayAll();

    std::cout << "\nfinding removed member with id 1:" << std::endl;
    found = memberList.findById(1);
    if (found == nullptr) {
        std::cout << "member not found (correct)" << std::endl;
    }

    std::cout << "\ndone" << std::endl;

    std::cout << "\n=== Game class showcase ===" << std::endl;

    Game g1(1, "Chess", 2, 2, 30, 60, 1850);
    std::cout << "Game ID: " << g1.getGameId() << "\n";
    std::cout << "Name: " << g1.getName() << "\n";
    std::cout << "Min Players: " << g1.getMinPlayers() << "\n";
    std::cout << "Max Players: " << g1.getMaxPlayers() << "\n";
    std::cout << "Year Published: " << g1.getYearPublished() << "\n";
    std::cout << "Can play with 2 players? " << (g1.canPlay(2) ? "Yes" : "No") << "\n";
    std::cout << "Can play with 1 player? " << (g1.canPlay(1) ? "Yes" : "No") << "\n";

    std::cout << "\nBorrow/return behavior:\n";
    std::cout << "First borrow: " << (g1.borrow() ? "Success" : "Failed") << "\n";
    std::cout << "Second borrow: " << (g1.borrow() ? "Success" : "Failed") << "\n";
    std::cout << "Returning game: " << (g1.returnGame() ? "Success" : "Failed") << "\n";
    std::cout << "Returning again: " << (g1.returnGame() ? "Success" : "Failed") << "\n";

    std::cout << "\n=== GameList showcase ===" << std::endl;
    GameList list(10);

    Game a(1, "Catan", 3, 4, 60, 120, 1995);
    Game b(2, "Pandemic", 2, 4, 45, 60, 2008);
    Game c(3, "Terraforming Mars", 1, 5, 90, 150, 2016);

    list.addGame(a);
    list.addGame(b);
    list.addGame(c);

    std::cout << "\n-- displayAll() --\n";
    list.displayAll();

    std::cout << "\n-- findById(2) --\n";
    Game* founded = list.findById(2);
    if (founded) {
        std::cout << "Found game: " << founded->getName() << "\n";
        founded->display();
    }
    else {
        std::cout << "Game with ID 2 not found.\n";
    }

    std::cout << "\n-- findByName(\"Catan\") --\n";
    Game* byName = list.findByName("Catan");
    if (byName) {
        std::cout << "Found game: " << byName->getName() << "\n";
        byName->display();
    }
    else {
        std::cout << "Game 'Catan' not found.\n";
    }

    std::cout << "\n-- removeGame(1) --\n";
    bool removed = list.removeGame(1);
    std::cout << "Removed game 1? " << (removed ? "Yes" : "No") << "\n";
    std::cout << "Remaining list:\n";
    list.displayAll();

    std::cout << "\n-- listByPlayers(4) --\n";
    list.listByPlayers(4);

    std::cout << "\n-- loadFromCSV(\"games.csv\") --\n";
    const std::string csvFile = "games.csv";

    GameList csvList(1000);
    csvList.loadFromCSV(csvFile);
    std::cout << "Loaded from CSV:\n";
    csvList.displayAll();


    std::cout << "\nGame and GameList showcase completed.\n";

    std::cout << "\n=== BorrowRecordDictionary Test with Actual Games ===\n";

    // Use csvList (the list loaded from games.csv) to find games by name.
    BorrowRecordDictionary brDict;

    Game* csv_g1 = csvList.findByName("Abalone");
    Game* csv_g2 = csvList.findByName("Sequence");
    Game* csv_g3 = csvList.findByName("The Settlers of Catan");

    if (csv_g1) std::cout << "\nBorrowing Abalone by member 101: "
        << (brDict.borrowGame(101, *csv_g1, "2026-02-01") ? "Success" : "Failed") << "\n";

    if (csv_g2) std::cout << "Borrowing Sequence by member 102: "
        << (brDict.borrowGame(102, *csv_g2, "2026-02-01") ? "Success" : "Failed") << "\n";

    if (csv_g3) std::cout << "Borrowing The Settlers of Catan by member 103: "
        << (brDict.borrowGame(103, *csv_g3, "2026-02-02") ? "Success" : "Failed") << "\n";

    if (csv_g1) std::cout << "Trying to borrow Abalone again by member 104: "
        << (brDict.borrowGame(104, *csv_g1, "2026-02-03") ? "Success" : "Failed") << "\n";

    if (csv_g1) std::cout << "\nReturning Abalone by member 101: "
        << (brDict.returnGame(101, *csv_g1, "2026-02-04") ? "Success" : "Failed") << "\n";

    if (csv_g3) std::cout << "Returning The Settlers of Catan by member 103: "
        << (brDict.returnGame(103, *csv_g3, "2026-02-04") ? "Success" : "Failed") << "\n";

    if (csv_g1) std::cout << "\nBorrowing Abalone again by member 104: "
        << (brDict.borrowGame(104, *csv_g1, "2026-02-05") ? "Success" : "Failed") << "\n";

    std::cout << "\nDisplaying all borrow/return records:\n";
    brDict.displayAll();

    if (csv_g1) {
        std::cout << "\nDisplaying records for Abalone:\n";
        brDict.displayByGame(*csv_g1);
    }
    if (csv_g2) {
        std::cout << "\nDisplaying records for Sequence:\n";
        brDict.displayByGame(*csv_g2);
    }
    if (csv_g3) {
        std::cout << "\nDisplaying records for The Settlers of Catan:\n";
        brDict.displayByGame(*csv_g3);
    }


    return 0;
}

