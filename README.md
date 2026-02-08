# DSA-NPTTGC-BoardGame-Manager

A comprehensive Board Game Management System built with C++ for managing board game collections, member registrations, borrowing/returning games, and tracking gameplay statistics.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [Usage](#usage)
  - [Administrator Functions](#administrator-functions)
  - [Member Functions](#member-functions)

## 🎯 Overview

The NPTTGC Board Game Manager is a C++ console-based application developed to manage the board game collection of the Ngee Ann Polytechnic Tabletop Games Club. The system supports two types of users: Administrators and Members, each with distinct functionalities.

## ✨ Features

### Administrator Features
- ✅ Display all games with pagination and sorting
- ✅ Add new board games to the collection
- ✅ Remove board games from the system
- ✅ Register new members
- ✅ View borrow/return summaries
- ✅ Filter games by player count
- ✅ View detailed game play statistics

### Member Features
- ✅ Borrow board games
- ✅ Return board games
- ✅ View personal borrow/return history
- ✅ View detailed information about specific games
- ✅ Search games by player count
- ✅ Write reviews and ratings for games
- ✅ View reviews for games
- ✅ Display personal play history

## 🔧 Data Structures Used

- **Linked List**: For storing members, game play records, and reviews
- **Array/List**: For storing the collection of board games
- **Hash Table/Dictionary**: For efficient borrow record lookups
- **Sorting Algorithms**: For organizing game displays

## 📖 Usage

### Starting the Application

When you launch the application, you'll be presented with a role selection menu:

---

### Administrator Functions

After selecting Administrator (option 1), you can access the following features:

#### 1. Display All Games
- **Function**: View all games in the system with pagination
- **Usage**: 
  - Navigate with `P` (Previous), `N` (Next), `F` (First), `L` (Last)
  - Sort games using `S` option
  - View details of specific game using `D` option
- **Example Output**:

#### 2. Add a Board Game
- **Function**: Add a new game to the collection
- **Required Input**:
  - Game ID (integer)
  - Game Name (string)
  - Minimum Players (integer)
  - Maximum Players (integer)
  - Minimum Play Time (integer, in minutes)
  - Maximum Play Time (integer, in minutes)
  - Year Published (integer)
- **Example**:

#### 3. Remove a Board Game
- **Function**: Remove a game from the system
- **Required Input**: Game ID
- **Note**: Game cannot be removed if currently borrowed

#### 4. Add a New Member
- **Function**: Register a new member
- **Required Input**:
  - Member ID (integer)
  - Member Name (string)

#### 5. Display Borrow/Return Summary
- **Function**: View comprehensive borrowing statistics
- **Shows**: 
  - All borrowed games
  - Return dates
  - Member information

#### 6. Display Games by Player Count
- **Function**: Filter games that support a specific number of players
- **Required Input**: Number of players (integer)
- **Example**: Shows all games that can be played with 4 players.

#### 7. View Game Play Statistics
- **Function**: View detailed analytics about game usage
- **Shows**:
  - Most played games
  - Play frequency
  - Member engagement statistics

---

### Member Functions

After selecting Member (option 2), enter your Member ID to access:

#### 1. Borrow a Board Game
- **Function**: Check out a game from the collection
- **Required Input**:
  - Game ID (integer)
  - Date (DD/MM/YYYY format)
- **Example**:

#### 2. Return a Board Game
- **Function**: Return a borrowed game
- **Required Input**:
  - Game ID (integer)
  - Return Date (DD/MM/YYYY format)

#### 3. Display Personal Borrow/Return Summary
- **Function**: View your borrowing history
- **Shows**:
  - Games you've borrowed
  - Borrow dates
  - Return dates
  - Current borrowed games

#### 4. Display Game Details
- **Function**: View detailed information about a specific game
- **Required Input**: Game ID
- **Shows**:
  - Game name
  - Player range
  - Play time
  - Year published
  - Availability status
  - Average rating

#### 5. Display Games by Player Count
- **Function**: Find games suitable for your group size
- **Required Input**: Number of players

#### 6. Write a Review
- **Function**: Rate and review a game
- **Required Input**:
  - Game ID (integer)
  - Rating (1-5 stars)
  - Comment (string)
- **Example**:

#### 7. View Reviews for a Game
- **Function**: Read reviews from other members
- **Required Input**: Game ID
- **Shows**:
  - Member IDs
  - Ratings
  - Comments
  - Average rating

#### 8. Display Member's Play History
- **Function**: View your complete gameplay history
- **Shows**: All games you've played and when

---

## 📝 Notes

- All dates should be entered in DD/MM/YYYY format
- Game IDs and Member IDs must be unique integers
- Games cannot be removed while borrowed
- Members must be registered before borrowing games
- Pagination displays 20 games per page for better navigation

---
