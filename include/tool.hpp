//
//  tool.hpp
//  FinalProjectTools
//
//  Created by Jingxia Zhong on 11/19/23.
//

#ifndef TOOL_HPP
#define TOOL_HPP

#include <vector>
#include "simulation.hpp"

// Enumeration for different types of tools
enum ToolType {
    TOOL_HEALTH,
    TOOL_FIRE_RATE,
    TOOL_LAND_MINE,
    TOOL_SHIELD
};

// Class to represent a tool
class Tool {
protected:
    int x, y;             // Position of the tool
    ToolType type;        // Type of the tool
    bool isVisible;       // Visibility of the tool
    int respawnTimer;     // Respawn timer for the tool
    int power;            // Power or effect level of the tool

public:
    Tool() : x(0), y(0), type(TOOL_HEALTH), isVisible(false), respawnTimer(0), power(0) 
    {
    }
    Tool(int x, int y, ToolType type, bool isVisible, int respawnTimer, int power) :
        x(x), y(y), type(type), isVisible(isVisible), respawnTimer(respawnTimer), power(power) 
    {
    }

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    ToolType getType() const {
        return type;
    }
    bool getIsVisible() const {
        return isVisible;
    }
    int getRespawnTimer() const {
        return respawnTimer;
    }
    int getPower() const {
        return power;
    }

    void setX(int newX) {
        x = newX;
    }
    void setY(int newY) {
        y = newY;
    }
    void setType(ToolType newType) {
        type = newType;
    }
    void setIsVisible(bool newIsVisible) {
        isVisible = newIsVisible;
    }
    void setRespawnTimer(int newRespawnTimer) {
        respawnTimer = newRespawnTimer;
    }
    void setPower(int newPower) {
        power = newPower;
    }

    void drawHealthTool() const;
    void drawFireRateTool() const;
    void drawLandMineTool() const;
    void drawShieldTool() const;
};

// Display all tools based on their visibility
void DisplayTools(const std::vector<Tool>& tools);

// Update the state of tools based on collision with tanks
void UpdateTools(std::vector<Tool>& tools, const SimulatedTank& tank, int& sharedRespawnTimer);

#endif // TOOL_HPP
