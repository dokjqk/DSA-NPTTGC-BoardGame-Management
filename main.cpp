// DSA-NPTTGC-BoardGame-Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Member.h"
#include "MemberList.h"
#include "Game.h"
#include "GameList.h"
#include "BorrowRecordDictionary.h"
#include "GamePlayRecordList.h"
#include "GamePlayRecord.h"

void displayAdminMenu() {
    std::cout << "\nAdministrator Menu:\n";
    std::cout << "1. Display All Games" << std::endl;
    std::cout << "2. Add a board game" << std::endl;
    std::cout << "3. Remove a board game" << std::endl;
    std::cout << "4. Add a new member" << std::endl;
    std::cout << "5. Display a summary of games borrowed/returned" << std::endl;
    std::cout << "6. Display a list of games that can be played by a given number players" << std::endl;
    std::cout << "7. View game play statistics" << std::endl;
	std::cout << "0. Return to main menu" << std::endl;
}

void displayMemberMenu() {
    std::cout << "\nMember Menu:\n";
    std::cout << "1. Borrow a board game" << std::endl;
    std::cout << "2. Return a board game" << std::endl;
    std::cout << "3. Display a summary of games borrowed/returned by member" << std::endl;
    std::cout << "4. Display the details of a particular game" << std::endl;
    std::cout << "5. Display a list of games that can be played by a given number of players" << std::endl;
    std::cout << "6. Write a review"<< std::endl;
    std::cout << "7. View reviews for a game" << std::endl;
	std::cout << "8. Display member's play history" << std::endl;
    std::cout << "0. Return to main menu" << std::endl;
}

//Display all games with pagination and sorting
void displayGamesWithPagination(GameList& gameList) {
    const int gamesPerPage = 20;
    int currentPage = 0;
    int totalGames = gameList.getSize();
    int totalPages = (totalGames + gamesPerPage - 1) / gamesPerPage;

    while (true) {
        system("cls");
        std::cout << "\n==== All Games (Page " << (currentPage + 1) << "/" << totalPages << ") ====\n";
        std::cout << "-------------------------------------------------------\n";

        int startIdx = currentPage * gamesPerPage;
        int endIdx = std::min(startIdx + gamesPerPage, totalGames);

        for (int i = startIdx; i < endIdx; i++) {
            Game* game = gameList.getGameAt(i);
            if (game) {
                std::cout << "ID: " << game->getGameId() << " | Name: " << game->getName() << "\n";
                std::cout << "Players: " << game->getMinPlayers() << "-" << game->getMaxPlayers();
                std::cout << " | Year: " << game->getYearPublished();
                std::cout << " | Status: " << (game->checkIfBorrowed() ? "Borrowed" : "Available") << "\n";
                std::cout << "-------------------------------------------------------\n";
            }
        }

        std::cout << "\nOptions:\n";
        if (currentPage > 0) std::cout << "P - Previous Page\n";
        if (currentPage < totalPages - 1) std::cout << "N - Next Page\n";
        std::cout << "S - Sort Games\n";
        std::cout << "D - View Game Details (by ID)\n";
        std::cout << "F - First Page\n";
        std::cout << "L - Last Page\n";
        std::cout << "0 - Back to Admin Menu\n";
        std::cout << "\nEnter choice: ";

        char choice;
        std::cin >> choice;
        choice = toupper(choice);

        switch (choice) {
        case 'P':
            if (currentPage > 0) {
                currentPage--;
            }
            else {
                std::cout << "Already on first page.\n";
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case 'N':
            if (currentPage < totalPages - 1) {
                currentPage++;
            }
            else {
                std::cout << "Already on last page.\n";
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case 'F':
            currentPage = 0;
            break;

        case 'L':
            currentPage = totalPages - 1;
            break;

        case 'S': {
            std::cout << "\nSort by:\n";
            std::cout << "1. Name\n";
            std::cout << "2. Year Published\n";
            std::cout << "3. Game ID\n";
            std::cout << "4. Borrow Status\n";
            std::cout << "Enter choice: ";

            int sortChoice;
            std::cin >> sortChoice;

            switch (sortChoice) {
            case 1:
                gameList.sortByName();
                std::cout << "Sorted by name.\n";
                break;
            case 2:
                gameList.sortByYear();
                std::cout << "Sorted by year.\n";
                break;
            case 3:
                gameList.sortById();
                std::cout << "Sorted by ID.\n";
                break;
            case 4:
                gameList.sortByBorrowedStatus();
                std::cout << "Sorted by borrow status.\n";
                break;
            default:
                std::cout << "Invalid sort option.\n";
            }

            totalGames = gameList.getSize();
            totalPages = (totalGames + gamesPerPage - 1) / gamesPerPage;
            currentPage = 0;

            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 'D': {
            int gameId;
            std::cout << "Enter Game ID: ";
            std::cin >> gameId;

            Game* game = gameList.findById(gameId);
            if (game) {
                std::cout << "\n";
                game->display();
            }
            else {
                std::cout << "Game not found.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case '0':
            return;

        default:
            std::cout << "Invalid choice.\n";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

//Display games by player count with pagination apply same concept as above
void displayGamesByPlayersWithPagination(GameList& gameList, int players) {
    const int gamesPerPage = 20;
    int currentPage = 0;

    
    int matchingGames = 0;
    for (int i = 0; i < gameList.getSize(); i++) {
        Game* game = gameList.getGameAt(i);
        if (game && game->canPlay(players)) {
            matchingGames++;
        }
    }

    if (matchingGames == 0) {
        std::cout << "No games found that can be played with " << players << " players.\n";
        return;
    }

    int totalPages = (matchingGames + gamesPerPage - 1) / gamesPerPage;

    while (true) {
        system("cls");
        std::cout << "\n==== Games for " << players << " Players (Page " << (currentPage + 1) << "/" << totalPages << ") ====\n";
        std::cout << "Total matching games: " << matchingGames << "\n";
        std::cout << "-------------------------------------------------------\n";

        int displayedOnPage = 0;
        int startGame = currentPage * gamesPerPage;
        int matchedSoFar = 0;

        for (int i = 0; i < gameList.getSize() && displayedOnPage < gamesPerPage; i++) {
            Game* game = gameList.getGameAt(i);
            if (game && game->canPlay(players)) {
                if (matchedSoFar >= startGame) {
                    std::cout << "ID: " << game->getGameId() << " | Name: " << game->getName() << "\n";
                    std::cout << "Players: " << game->getMinPlayers() << "-" << game->getMaxPlayers();
                    std::cout << " | PlayTime: " << game->getMinPlayTime() << "-" << game->getMaxPlayTime() << " min";
                    std::cout << " | Year: " << game->getYearPublished();
                    std::cout << " | Status: " << (game->checkIfBorrowed() ? "Borrowed" : "Available") << "\n";
                    std::cout << "-------------------------------------------------------\n";
                    displayedOnPage++;
                }
                matchedSoFar++;
            }
        }

        std::cout << "\nOptions:\n";
        if (currentPage > 0) std::cout << "P - Previous Page\n";
        if (currentPage < totalPages - 1) std::cout << "N - Next Page\n";
        std::cout << "D - View Game Details (by ID)\n";
        std::cout << "F - First Page\n";
        std::cout << "L - Last Page\n";
        std::cout << "0 - Back to Menu\n";
        std::cout << "\nEnter choice: ";

        char choice;
        std::cin >> choice;
        choice = toupper(choice);

        switch (choice) {
        case 'P':
            if (currentPage > 0) {
                currentPage--;
            }
            else {
                std::cout << "Already on first page.\n";
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case 'N':
            if (currentPage < totalPages - 1) {
                currentPage++;
            }
            else {
                std::cout << "Already on last page.\n";
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case 'F':
            currentPage = 0;
            break;

        case 'L':
            currentPage = totalPages - 1;
            break;

        case 'D': {
            int gameId;
            std::cout << "Enter Game ID: ";
            std::cin >> gameId;

            Game* game = gameList.findById(gameId);
            if (game) {
                std::cout << "\n";
                game->display();
            }
            else {
                std::cout << "Game not found.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case '0':
            return;

        default:
            std::cout << "Invalid choice.\n";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

//Record new game play
bool recordGamePlay(GamePlayRecordList& gamePlayList, MemberList& memberList, GameList& gameList) {
    system("cls");
    
    int gameId, numWinners, numLosers;
    
    std::cout << "\n==== Record New Game Play ====\n";
    std::cout << "Enter Game ID (or 0 to cancel): ";
    std::cin >> gameId;

	if (std::cin.fail()) {
        std::cin.clear();
		std::cin.ignore();
        std::cout << "Invalid input. Please enter a valid Game ID." << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return false;
    }
    
    if (gameId == 0) {
        return false;
    }
    
    Game* game = gameList.findById(gameId);
    if (game == nullptr) {
        std::cout << "Game not found!" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return false;
    }
    
    std::cout << "Recording play for: " << game->getName() << std::endl;
    
    GamePlayRecord* play = new GamePlayRecord(gameId, game->getName());
    
    std::cout << "\nEnter number of winners: ";
    std::cin >> numWinners;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        delete play;
        std::cout << "Invalid input. Please enter a valid number" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return false;
    }
    
    if (numWinners > 0) {
        std::cout << "Enter winner IDs:" << std::endl;
        for (int i = 0; i < numWinners; i++) {
            int winnerId;
            std::cout << "  Winner " << (i + 1) << ": ";
            std::cin >> winnerId;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore();
                i--;
                std::cout << "Invalid input. Please enter a valid member ID." << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                continue;
            }
            
            Member* winnerMember = memberList.findById(winnerId);
            if (winnerMember == nullptr) {
                std::cout << "  Warning: Member ID " << winnerId << " not found in system." << std::endl;
            } else {
                std::cout << "  Added: " << winnerMember->getName() << std::endl;
            }
            
            play->addWinner(winnerId);
        }
    }
    
    std::cout << "\nEnter number of losers: ";
    std::cin >> numLosers;
    
    if (numLosers > 0) {
        std::cout << "Enter loser IDs:" << std::endl;
        for (int i = 0; i < numLosers; i++) {
            int loserId;
            std::cout << "  Loser " << (i + 1) << ": ";
            std::cin >> loserId;
            
            Member* loserMember = memberList.findById(loserId);
            if (loserMember == nullptr) {
                std::cout << "  Warning: Member ID " << loserId << " not found in system." << std::endl;
            } else {
                std::cout << "  Added: " << loserMember->getName() << std::endl;
            }
            
            play->addLoser(loserId);
        }
    }
    
    int totalPlayers = play->getTotalPlayers();
    if (totalPlayers == 0) {
        std::cout << "\nError: At least one player must be recorded!" << std::endl;
        delete play;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return false;
    }
    
    if (!game->canPlay(totalPlayers)) {
        std::cout << "\nWarning: Total players (" << totalPlayers 
                  << ") is outside the valid range for this game ("
                  << game->getMinPlayers() << "-" << game->getMaxPlayers() << " players)." << std::endl;
        std::cout << "Record anyway? (Y/N): ";
        char confirm;
        std::cin >> confirm;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
			delete play;
            std::cout << "Invalid input. Play was not recorded." << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return false;
        }

        if (toupper(confirm) != 'Y') {
            delete play;
            std::cout << "Game play recording cancelled." << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return false;
        }
    }
    
    gamePlayList.addGamePlay(play);
    std::cout << "\nGame play recorded successfully!" << std::endl;
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    
    return true;
}

//Display member play history with pagination too
void displayMemberPlayHistoryWithPagination(GamePlayRecordList& gamePlayList, MemberList& memberList, GameList& gameList, int memberId) {
    const int recordsPerPage = 10;
    int currentPage = 0;
    
    int totalRecords = gamePlayList.getPlayCountByMember(memberId);
    
    if (totalRecords == 0) {
        std::cout << "\nYou have no play history recorded yet.\n";
        std::cout << "Press Enter to record your first game play...";
        std::cin.ignore();
        std::cin.get();
		recordGamePlay(gamePlayList, memberList, gameList);
        return;
    }
    
    int totalPages = (totalRecords + recordsPerPage - 1) / recordsPerPage;
    
    while (true) {
        system("cls");
        
        int wins = gamePlayList.getWinCountByMember(memberId);
        int losses = gamePlayList.getLossCountByMember(memberId);
        double winRate = totalRecords > 0 ? (double)wins / totalRecords * 100.0 : 0.0;
        
        std::cout << "\n==== Your Play History (Page " << (currentPage + 1) << "/" << totalPages << ") ====\n";
        std::cout << "Total Games: " << totalRecords << " | Wins: " << wins 
                  << " | Losses: " << losses << " | Win Rate: " << winRate << "%\n";
        std::cout << "-------------------------------------------------------\n";
        
        int startIdx = currentPage * recordsPerPage;
        
        std::cout << "\n";
        gamePlayList.displayByMemberPaginated(memberId, startIdx, recordsPerPage);
        
        std::cout << "\n-------------------------------------------------------\n";
        std::cout << "Options:\n";
        if (currentPage > 0) std::cout << "P - Previous Page\n";
        if (currentPage < totalPages - 1) std::cout << "N - Next Page\n";
        std::cout << "F - First Page\n";
        std::cout << "L - Last Page\n";
        std::cout << "R - Record New Game Play\n";
        std::cout << "S - View Statistics\n";
        std::cout << "0 - Back to Menu\n";
        std::cout << "\nEnter choice: ";
        
        char choice;
        std::cin >> choice;
        choice = toupper(choice);
        
        switch (choice) {
            case 'P':
                if (currentPage > 0) {
                    currentPage--;
                } else {
                    std::cout << "Already on first page.\n";
                    std::cin.ignore();
                    std::cin.get();
                }
                break;
                
            case 'N':
                if (currentPage < totalPages - 1) {
                    currentPage++;
                } else {
                    std::cout << "Already on last page.\n";
                    std::cin.ignore();
                    std::cin.get();
                }
                break;
                
            case 'F':
                currentPage = 0;
                break;
                
            case 'L':
                currentPage = totalPages - 1;
                break;
                
            case 'S': {
                system("cls");
                std::cout << "\n==== Your Detailed Statistics ====\n";
                std::cout << "Total games played: " << totalRecords << std::endl;
                std::cout << "Games won: " << wins << std::endl;
                std::cout << "Games lost: " << losses << std::endl;
                std::cout << "Win rate: " << winRate << "%" << std::endl;
                
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
                
            case 'R': {
                std::cin.ignore(10000, '\n');
                if (recordGamePlay(gamePlayList, memberList, gameList)) {
                    totalRecords = gamePlayList.getPlayCountByMember(memberId);
                    totalPages = (totalRecords + recordsPerPage - 1) / recordsPerPage;
                }
                break;
            }
                
            case '0':
                return;
                
            default:
                std::cout << "Invalid choice.\n";
                std::cin.ignore();
                std::cin.get();
        }
    }
}

int main() {
    GameList gameList(1000,"games.csv");
    MemberList memberList;
    BorrowRecordDictionary borrowDict;
	GamePlayRecordList gamePlayList("gameplays.csv");

    const std::string csvGame = "games.csv";
    const std::string csvMember = "members.csv";

    memberList.loadFromCSV(csvMember);
    gameList.loadFromCSV(csvGame);
	gamePlayList.loadFromCSV();

    int roleChoice = 0;

    while (true) {
        std::cout << "\n==== NPTTGC Board Game Manager ====\n";
        std::cout << "1. Administrator" << std::endl;
        std::cout << "2. Member" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> roleChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        if (roleChoice == 3) {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        if (roleChoice == 1) {
            bool exitAdminMenu = false;
            while (!exitAdminMenu) {
                int adminChoice;
                displayAdminMenu();
                std::cout << "Enter choice: ";
                std::cin >> adminChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    continue;
                }

                switch (adminChoice) {
                case 1: {   // Display All Games
                    displayGamesWithPagination(gameList);
                    break;
                }
                case 2: {   // Add game
                    std::string gameName;
                    int minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished;

                    std::cin.ignore();
                    std::cout << "Enter game name: ";
                    std::getline(std::cin, gameName);

                    std::cout << "Enter minimum players: ";
                    std::cin >> minPlayers;

                    std::cout << "Enter maximum players: ";
                    std::cin >> maxPlayers;

                    std::cout << "Enter minimum play time (minutes): ";
                    std::cin >> minPlayTime;

                    std::cout << "Enter maximum play time (minutes): ";
                    std::cin >> maxPlayTime;

                    std::cout << "Enter year published: ";
                    std::cin >> yearPublished;

                    Game newGame(0, gameName, minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished);
                    gameList.addGame(newGame);

                    std::cout << "Game added successfully!" << std::endl;
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 3: {   // Remove game
                    int gameId;

                    std::cout << "Enter game ID to remove: ";
                    std::cin >> gameId;

                    if (gameList.removeGame(gameId)) {
                        std::cout << "Game removed successfully!" << std::endl;
                    }
                    else {
                        std::cout << "Failed to remove game. Game not found or error occurred." << std::endl;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 4: {   // Add Member
                    int memberId;
                    std::string memberName;

                    std::cout << "Enter member ID: ";
                    std::cin >> memberId;

                    std::cin.ignore();
                    std::cout << "Enter member name: ";
                    std::getline(std::cin, memberName);

                    Member newMember(memberId, memberName);

                    if (memberList.addMember(newMember)) {
                        std::cout << "Member added successfully!" << std::endl;
                    }
                    else {
                        std::cout << "Failed to add member. Member ID already exists." << std::endl;
                    }

                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }

                case 5: {   // Borrowed summary
                    std::cout << "\n=== Summary of All Games Borrowed/Returned ===" << std::endl;
                    borrowDict.displayAll();
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 6: {   // Games by player count
                    int players;
                    std::cout << "Enter number of players: ";
                    std::cin >> players;

                    displayGamesByPlayersWithPagination(gameList, players);
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 7: {   // View game play statistics for admin
                    std::cout << "\n=== Game Play Statistics ===" << std::endl;
                    std::cout << "1. View all game plays" << std::endl;
                    std::cout << "2. View plays for a game" << std::endl;
                    std::cout << "3. View plays for a member" << std::endl;
					std::cout << "Quick game lookup" << std::endl;
                    std::cout << "Enter choice: ";

                    int statsChoice;
                    std::cin >> statsChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid input." << std::endl;
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }

                    switch (statsChoice) {
                    case 1: {
                        // View all gameplay records
                        std::cout << "\n=== All Game Plays (System-Wide) ===" << std::endl;
                        gamePlayList.displayAll();

                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }

                    case 2: {
                        // View records for a specific game
                        int gId;
                        std::cout << "Enter Game ID: ";
                        std::cin >> gId;

                        Game* game = gameList.findById(gId);
                        if (game) {
                            std::cout << "\n=== Play History for: " << game->getName() << " ===" << std::endl;
                            gamePlayList.displayByGame(gId);

                            int playCount = gamePlayList.getPlayCountByGame(gId);
                            std::cout << "\n--- Statistics ---" << std::endl;
                            std::cout << "Total plays recorded: " << playCount << std::endl;
                        }
                        else {
                            std::cout << "Game not found!" << std::endl;
                        }

                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }

                    case 3: {
                        // View records for a specific member
                        int mId;
                        std::cout << "Enter Member ID: ";
                        std::cin >> mId;

                        Member* member = memberList.findById(mId);
                        if (member) {
                            std::cout << "\n=== Play History for: " << member->getName() << " ===" << std::endl;
                            gamePlayList.displayByMember(mId);

							// Display member statistics
                            int total = gamePlayList.getPlayCountByMember(mId);
                            int wins = gamePlayList.getWinCountByMember(mId);
                            int losses = gamePlayList.getLossCountByMember(mId);

                            if (total > 0) {
                                double winRate = (double)wins / total * 100.0;
                                std::cout << "\n--- Detailed Statistics ---" << std::endl;
                                std::cout << "Total games played: " << total << std::endl;
                                std::cout << "Wins: " << wins << std::endl;
                                std::cout << "Losses: " << losses << std::endl;
                                std::cout << "Win rate: " << winRate << "%" << std::endl;
                            }
                        }
                        else {
                            std::cout << "Member not found!" << std::endl;
                        }

                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }

					case 4: { // Binary search for game by ID
                        gameList.sortById();

                        int id;
                        std::cout << "\nEnter Game ID (0 to cancel): ";
                        std::cin >> id;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout << "Invalid input." << std::endl;
                            continue;
                        }

                        if (id == 0) {
                            break;
                        }

                        int index = gameList.binarySearchById(id);
                        Game* game = gameList.getGameAt(index);
                        game->display();
                        gameList.sortByName();
                        break;
					}

                    default:
                        std::cout << "Invalid choice." << std::endl;
                        std::cout << "\nPress Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    }
                    break;
                }


                case 0:
                    std::cout << "Returning to main menu..." << std::endl;
                    exitAdminMenu = true;
                    break;

                default:
                    std::cout << "Invalid choice. Please enter a number between 0 and 6." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }
            }
        }
        else if (roleChoice == 2) {
            int memberId;
            std::cout << "Enter memberId: ";
            std::cin >> memberId;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a valid member ID." << std::endl;
                continue;
            }

            Member* member = memberList.findById(memberId);
            if (!member) {
                std::cout << "Member ID not found. Please check your ID or contact administrator." << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                continue;
            }

            std::cout << "Welcome, " << member->getName() << "!" << std::endl;

            bool exitMemberMenu = false;
            while (!exitMemberMenu) {
                int memberChoice;
                displayMemberMenu();
                std::cout << "Enter choice: ";
                std::cin >> memberChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    continue;
                }

                switch (memberChoice) {
                case 1: { // Borrow Game
                    int gameId;
                    std::string date;

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

                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }
                case 2: { // Return Game
                    int gameId;
                    std::string date;

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

                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }
                case 3: { // Display Member Summary
                    borrowDict.displayByMember(memberId);
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                case 4: { // Display Game Details
                    displayGamesWithPagination(gameList);
                    break;
                }
                case 5: { // List of games able to be played
                    int players;
                    std::cout << "Enter number of players: ";
                    std::cin >> players;

                    displayGamesByPlayersWithPagination(gameList, players);
                    break;
                }
                case 6: { // Write a review
                    int gameId;
                    int rating;
                    std::string comment;

                    std::cout << "Enter Game ID: ";
                    std::cin >> gameId;
                    std::cin.ignore();

                    while (true) {
                        std::cout << "Enter Rating (0-5): ";
                        std::cin >> rating;

                        if (std::cin.fail() || rating < 0 || rating > 5) {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout << "Invalid rating. Please enter a number between 0 and 5." << std::endl;
                            continue;
                        }

                        std::cin.ignore();
                        break;
                    }

                    std::cout << "Enter Comment: ";
                    getline(std::cin, comment);

                    Game* g = gameList.findById(gameId);
                    if (g) {
                        g->addReview(memberId, rating, comment);
                        std::cout << "Review added." << std::endl;
                    }
                    else {
                        std::cout << "Game not found." << std::endl;
                    }

                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;

                }
                case 7: { // Read review for a game
                    int gameId;
                    std::cout << "Enter Game ID: ";
                    std::cin >> gameId;

                    Game* g = gameList.findById(gameId);
                    if (g) {
                        g->displayReviews();
                    }
                    else {
                        std::cout << "Game not found." << std::endl;
                    }

                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 8: { // Display member's play history
					displayMemberPlayHistoryWithPagination(gamePlayList, memberList, gameList, memberId);
                    break;
				}
                case 0:
                    std::cout << "Returning to main menu..." << std::endl;
                    exitMemberMenu = true;
                    break;

                default:
                    std::cout << "Invalid choice. Please enter a number between 0 and 7." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }
            }
        }
        else {
            std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
        }
    }
    
    return 0;
}