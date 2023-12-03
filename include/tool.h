//
//  tool.hpp
//  FinalProjectTools
//
//  Created by Jingxia Zhong on 11/19/23.
//

#ifndef TOOL_HPP
#define TOOL_HPP

#include <vector>
#include "../include/tank.h"

enum ToolType {
    TOOL_HEALTH,
    TOOL_FIRE_RATE,
    TOOL_ADD_SPEED,
    TOOL_SHIELD
};

class Tool {
protected:
    int x, y;
    ToolType type;
    bool isVisible;
    int respawnTimer;
    int power;

public:
    Tool();
    Tool(int x, int y, ToolType type, bool isVisible, int respawnTimer, int power);

    int getX() const;
    int getY() const;
    ToolType getType() const;
    bool getIsVisible() const;
    int getRespawnTimer() const;
    int getPower() const;

    void setX(int newX);
    void setY(int newY);
    void setType(ToolType newType);
    void setIsVisible(bool newIsVisible);
    void setRespawnTimer(int newRespawnTimer);
    void setPower(int newPower);

    void DrawHealthTool() const;
    void DrawFireRateTool() const;
    void DrawAddSpeedTool() const;
    void DrawShieldTool() const;
};

void SetupTools(std::vector<Tool>& tools);
void DisplayTools(const std::vector<Tool>& tools);
void UpdateTools(std::vector<Tool>& tools, const tank& playerTank, int& sharedRespawnTimer);

#endif // TOOL_HPP
