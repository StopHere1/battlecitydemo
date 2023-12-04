#define GL_SILENCE_DEPRECATION
#include "../include/GameJudge.h"
#include <iostream>

// ... [Other GameJudge methods] ...

void GameJudge::updateGameState(int p1HP, int p2HP, int p1OccupationPoints, int p2OccupationPoints, int elapsed) {
    // std::cout << "Updating game state: "
    //     << "Player 1 HP: " << p1HP
    //     << ", Player 2 HP: " << p2HP
    //     << ", Player 1 Occupation Points: " << p1OccupationPoints
    //     << ", Player 2 Occupation Points: " << p2OccupationPoints
    //     << ", Elapsed Time: " << elapsed << std::endl;

    player1HP = p1HP;
    player2HP = p2HP;
    player1OccupationPoints = p1OccupationPoints;
    player2OccupationPoints = p2OccupationPoints;
    elapsedTime = elapsed;
}

// ... [Rest of the GameJudge class methods] ...


GameJudge::GameJudge(GameMode mode, int totalGameTime)
    : mode(mode), totalTime(totalGameTime), elapsedTime(0), winner(0) {
    // Initialize other game-specific variables if needed
}

bool GameJudge::checkWinCondition() {
    switch (mode) {
    case GameMode::DeathBattle:
        return checkDeathBattleWin();
    case GameMode::Occupation:
        return checkOccupationWin();
    case GameMode::TimeLimitedOccupation:
        return checkTimeLimitedOccupationWin();
    default:
        return false;
    }
}

bool GameJudge::checkDeathBattleWin() {
    std::cout << "Player 1 HP: " << player1HP << ", Player 2 HP: " << player2HP << std::endl;
    if (player1HP <= 0 && player2HP > 0) {
        winner = 2;  // Player 2 wins
        return true;
    }
    else if (player2HP <= 0 && player1HP > 0) {
        winner = 1;  // Player 1 wins
        return true;
    }
    return false; // No winner yet
}



bool GameJudge::checkOccupationWin() {
    // Check if either player's HP has dropped to 0 or below
    if (player1HP <= 0 && player2HP > 0) {
        winner = 2;  // Player 2 wins
        return true;
    }
    else if (player2HP <= 0 && player1HP > 0) {
        winner = 1;  // Player 1 wins
        return true;
    }
    if (player1OccupationPoints >= 50) {
        winner = 1;  // Player 1 wins
        return true;
    }
    else if (player2OccupationPoints >= 50) {
        winner = 2;  // Player 2 wins
        return true;
    }
    return false; // No winner yet
}


bool GameJudge::checkTimeLimitedOccupationWin() {
    // Check if either player's HP has dropped to 0 or below
    if (player1HP <= 0 && player2HP > 0) {
        winner = 2;  // Player 2 wins
        return true;
    }
    else if (player2HP <= 0 && player1HP > 0) {
        winner = 1;  // Player 1 wins
        return true;
    }

    if (elapsedTime >= 120) {
        if (player1OccupationPoints > player2OccupationPoints) {
            winner = 1;  // Player 1 wins
            return true;
        }
        else if (player2OccupationPoints > player1OccupationPoints) {
            winner = 2;  // Player 2 wins
            return true;
        }
        else if (player2OccupationPoints == player1OccupationPoints) {
            winner = 3;  // Player 2 wins
            return true;

        }
        return false; // No winner yet, or time not up yet
    }
}

int GameJudge::getWinner() const {
    return winner;
    }