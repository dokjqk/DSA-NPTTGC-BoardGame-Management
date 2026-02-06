
// DSA-NPTTGC-BoardGame-Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Member.h"
#include "MemberList.h"
#include "Game.h"
#include "GameList.h"
#include "BorrowRecordDictionary.h"

void displayAdminMenu() {
    std::cout << "\nAdministrator Menu:\n";
    std::cout << "1. Add a board game" << std::endl;
    std::cout << "2. Remove a board game" << std::endl;
    std::cout << "3. Add a new member" << std::endl;
    std::cout << "4. Display a summary of games borrowed/returned" << std::endl;
    std::cout << "5.Display the details of a particular game" << std::endl;
    std::cout << "6. Display a list of games that can be played by a given number players" << std::endl;
}

void displayMemberMenu() {
    std::cout << "\nMember Menu:\n";
    std::cout << "1. Borrow a board game" << std::endl;
    std::cout << "2. Return a board game" << std::endl;
    std::cout << "3. Display a summary of games borrowed/returned by member" << std::endl;
    std::cout << "4. Display the details of a particular game" << std::endl;
    std::cout << "5. Display a list of games that can be played by a given number of players" << std::endl;
}


int main() {
    GameList gameList(1000);
    MemberList memberList;
    BorrowRecordDictionary borrowDict;

    const std::string csvGame = "games.csv";
    const std::string csvMember = "members.csv";

    memberList.loadFromCSV(csvMember);
    gameList.loadFromCSV(csvGame);

    int roleChoice = 0;

    while (true) {
        std::cout << "\n==== NPTTGC Board Game Manager ====\n";
        std::cout << "1. Administrator" << std::endl;
        std::cout << "2. Member" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> roleChoice;

        if (roleChoice == 3) {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        if (roleChoice == 1) {
            int adminChoice;
            displayAdminMenu();
            std::cout << "Enter choice: ";
            std::cin >> adminChoice;

            switch (adminChoice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                std::cout << "Admin feature not implemented yet." << std::endl;
                break;

            default:
                std::cout << "Invalid choice." << std::endl;
            }
        }
        else if (roleChoice == 2) {
            int memberChoice;
            displayMemberMenu();
            std::cout << "Enter choice: ";
            std::cin >> memberChoice;

            switch (memberChoice) {
            case 1: { // Borrow Game
                int memberId;
                int gameId;
                std::string date;

                std::cout << "Enter memberId: ";
                std::cin >> memberId;

                std::cout << "Enter gameId: ";
                std::cin >> gameId;
                std::cin.ignore();

                std::cout << "Enter Date (DD/MM/YYYY): ";
                getline(std::cin, date);

                Game* g = gameList.findById(gameId);

                if (g && borrowDict.borrowGame(memberId, *g, date))
                    std::cout << "Borrow successful." << std::endl;
                else
                    std::cout << "Borrow failed." << std::endl;

                break;
            }
            case 2: { // Return Game
                int memberId, gameId;
                std::string date;

                std::cout << "Enter Member ID: ";
                std::cin >> memberId;

                std::cout << "Enter Game ID: ";
                std::cin >> gameId;
                std::cin.ignore();

                std::cout << "Enter Date: ";
                getline(std::cin, date);

                Game* g = gameList.findById(gameId);

                if (g && borrowDict.returnGame(memberId, *g, date))
                    std::cout << "Return successful." << std::endl;
                else
                    std::cout << "Return failed." << std::endl;

                break;
            }
            case 3: { // Display Member Summary
                int memberId;
                std::cout << "Enter memberId: ";
                std::cin >> memberId;

                borrowDict.displayByMember(memberId);
                break;
            }
            case 4: { // Display Game Details
                int id;
                std::cout << "Enter gameId: ";
                std::cin >> id;

                Game* g = gameList.findById(id);
                if (g)
                    g->display();
                else
                    std::cout << "Game not found." << std::endl;

                break;
            }
            case 5: { // List of games able to be played

            }
            }
        }
    }
}