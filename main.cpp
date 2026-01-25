// DSA-NPTTGC-BoardGame-Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Member.h"
#include "MemberList.h"
#include "Game.h"
#include "GameList.h"

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
    const string csvFile = "games.csv";

    GameList csvList(1000);
    csvList.loadFromCSV(csvFile);
    std::cout << "Loaded from CSV:\n";
    csvList.displayAll();


    std::cout << "\nGame and GameList showcase completed.\n";


    return 0;
}

