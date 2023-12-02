#ifndef GAMEJUDGE_H
#define GAMEJUDGE_H

enum class GameMode {
    DeathBattle,
    Occupation,
    TimeLimitedOccupation
};

class GameJudge {
public:
    GameJudge(GameMode mode, int totalGameTime = 0);

    void updateGameState(int player1HP, int player2HP, int player1OccupationPoints, int player2OccupationPoints, int elapsedTime);
    bool checkWinCondition();
    int getWinner() const;

private:
    GameMode mode;
    int player1HP;
    int player2HP;
    int player1OccupationPoints;
    int player2OccupationPoints;
    int totalTime;  // for time-limited mode
    int elapsedTime;  // for time-limited mode
    int winner;  // To store the winner

    bool checkDeathBattleWin();
    bool checkOccupationWin();
    bool checkTimeLimitedOccupationWin();
};

#endif // GAMEJUDGE_H
