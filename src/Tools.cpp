//
//  Tools.cpp
//  FinalProject
//
//  Created by Jingxia Zhong on 11/13/23.
//
#define GL_SILENCE_DEPRECATION
#include <cmath>
#include <string>
#include "../include/tool.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"

Tool::Tool() : x(0), y(0), type(TOOL_HEALTH), isVisible(false), respawnTimer(0), power(0)
{
}

Tool::Tool(int x, int y, ToolType type, bool isVisible, int respawnTimer, int power) :
    x(x), y(y), type(type), isVisible(isVisible), respawnTimer(respawnTimer), power(power)
    {
    }

int Tool::getX() const {
    return x;
}
int Tool::getY() const {
    return y;
}
ToolType Tool::getType() const {
    return type;
}
bool Tool::getIsVisible() const {
    return isVisible;
}
int Tool::getRespawnTimer() const {
    return respawnTimer;
}
int Tool::getPower() const {
    return power;
}

void Tool::setX(int newX) {
    x = newX;
}
void Tool::setY(int newY) {
    y = newY;
}
void Tool::setType(ToolType newType) {
    type = newType;
}
void Tool::setIsVisible(bool newIsVisible) {
    isVisible = newIsVisible;
}
void Tool::setRespawnTimer(int newRespawnTimer) {
    respawnTimer = newRespawnTimer;
}
void Tool::setPower(int newPower) {
    power = newPower;
}

// Helper function to draw a circle
void DrawCircle(int centerX, int centerY, int radius, const unsigned char color[3]) {
    glColor3ubv(color);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        int x = centerX + radius * cos(angle);
        int y = centerY + radius * sin(angle);
        glVertex2i(x, y);
    }
    glEnd();
}

void Tool::DrawHealthTool() const {
    const unsigned char red[3] = {255, 0, 0};
    int circleRadius = 7*0.75;
    int triangleSize = 15*0.75;
    
    int offsetX = 4 * circleRadius;
    int offsetY = 4.5 * circleRadius;
    
    DrawCircle(this->x - circleRadius - offsetX, this->y - offsetY, circleRadius, red);
    DrawCircle(this->x + circleRadius - offsetX, this->y - offsetY, circleRadius, red);
    
    glColor3ubv(red);
    glBegin(GL_TRIANGLES);
    glVertex2i(this->x - triangleSize - offsetX, this->y - offsetY);
    glVertex2i(this->x + triangleSize - offsetX, this->y - offsetY);
    glVertex2i(this->x - offsetX, this->y + triangleSize - offsetX);
    glEnd();
}

void Tool::DrawFireRateTool() const {
    const unsigned char black[3] = {0, 0, 0};
    const unsigned char gold[3] = {255, 215, 0};

    glColor3ubv(gold);
    int bulletWidth = 9*0.9;
    int bulletHeight = 15*0.9;
    int triangleHeight = 7.5*0.9;
    
    int offsetX = 2.6 * bulletWidth;
    int offsetY = 1.85 * bulletHeight;
    
    glBegin(GL_TRIANGLES);
    glVertex2i(this->x - offsetX, this->y - triangleHeight - offsetY);
    glVertex2i(this->x - bulletWidth / 2 - offsetX, this->y - offsetY);
    glVertex2i(this->x + bulletWidth / 2 - offsetX, this->y - offsetY);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(this->x - bulletWidth / 2 - offsetX, this->y - offsetY);
    glVertex2i(this->x + bulletWidth / 2 - offsetX, this->y - offsetY);
    glVertex2i(this->x + bulletWidth / 2 - offsetX, this->y + bulletHeight - offsetY);
    glVertex2i(this->x - bulletWidth / 2 - offsetX, this->y + bulletHeight - offsetY);
    glEnd();
}

void Tool::DrawAddSpeedTool() const {
    const unsigned char lightBlue[3] = {173, 216, 230};
    const unsigned char mediumBlue[3] = {0, 0, 205};
    const unsigned char darkBlue[3] = {0, 0, 139};

    int triangleBase = 10;
    int triangleHeight = 17.5;
    int offsetX = 1.85 * triangleHeight;
    int offsetY = 2.8 * triangleBase;

    int triangleOffsetX = triangleBase - 3; // Horizontal offset between triangles
    int currentX = this->x;

    glColor3ubv(lightBlue);
    glBegin(GL_TRIANGLES);
    glVertex2i(currentX - offsetX, this->y - offsetY);
    glVertex2i(currentX - offsetX, this->y + triangleHeight - offsetY);
    glVertex2i(currentX + triangleBase - offsetX, this->y + (triangleHeight / 2) - offsetY);
    glEnd();

    currentX += triangleOffsetX;

    glColor3ubv(mediumBlue);
    glBegin(GL_TRIANGLES);
    glVertex2i(currentX - offsetX, this->y - offsetY);
    glVertex2i(currentX - offsetX, this->y + triangleHeight - offsetY);
    glVertex2i(currentX + triangleBase - offsetX, this->y + (triangleHeight / 2) - offsetY);
    glEnd();

    currentX += triangleOffsetX;

    glColor3ubv(darkBlue);
    glBegin(GL_TRIANGLES);
    glVertex2i(currentX - offsetX, this->y - offsetY);
    glVertex2i(currentX - offsetX, this->y + triangleHeight - offsetY);
    glVertex2i(currentX + triangleBase - offsetX, this->y + (triangleHeight / 2) - offsetY);
    glEnd();
}

void Tool::DrawShieldTool() const {
    const unsigned char black[3] = {0, 0, 0};
    int squareSide = 15;
    int radius = squareSide / 2;
    
    int offsetX = 1.35 * squareSide;
    int offsetY = 1.55 * squareSide;

    glColor3ubv(black);
    glBegin(GL_QUADS);
    glVertex2i(this->x - radius - offsetX, this->y - radius - offsetY);
    glVertex2i(this->x + radius - offsetX, this->y - radius - offsetY);
    glVertex2i(this->x + radius - offsetX, this->y + radius - offsetY);
    glVertex2i(this->x - radius - offsetX, this->y + radius - offsetY);
    glEnd();

    DrawCircle(this->x - offsetX, this->y + radius - offsetY, radius, black);
}

void SetupTools(std::vector<Tool>& tools) {
     tools.clear();

     tools.emplace_back(120, 120, TOOL_HEALTH, true, 0, 30);
     tools.emplace_back(560, 360, TOOL_FIRE_RATE, true, 0, 20);
     tools.emplace_back(440, 400, TOOL_ADD_SPEED, true, 0, 15);
     tools.emplace_back(880, 640, TOOL_SHIELD, true, 0, 30);
}

void DisplayTools(const std::vector<Tool>& tools) {
    for (const auto& tool : tools) {
        if (tool.getIsVisible()) {
            switch (tool.getType()) {
                case TOOL_HEALTH:
                    tool.DrawHealthTool();
                    break;
                case TOOL_FIRE_RATE:
                    tool.DrawFireRateTool();
                    break;
                case TOOL_ADD_SPEED:
                    tool.DrawAddSpeedTool();
                    break;
                case TOOL_SHIELD:
                    tool.DrawShieldTool();
                    break;
            }
        }
    }
}

bool IsColliding(int tankX, int tankY, int toolX, int toolY, int offsetX, int offsetY) {
    toolX += offsetX;
    toolY += offsetY;
    
    // Define a collision range
    const int collisionRange = 20;
    return std::abs(tankX - toolX) <= collisionRange && std::abs(tankY - toolY) <= collisionRange;
}

void UpdateTools(std::vector<Tool>& tools, tank& playerTank, int& sharedRespawnTimer) {
    bool allToolsNotVisible = true;
    tank& nonConstTank = const_cast<tank&>(playerTank);
    for (auto& tool : tools) {
        int offsetX = 0;
        int offsetY = 0;

        switch (tool.getType()) {
            case TOOL_HEALTH:
                offsetX = -4 * 7 * 0.75; // 7 is the circleRadius in DrawHealthTool
                offsetY = -4.5 * 7 * 0.75;
                break;
            case TOOL_FIRE_RATE:
                offsetX = -2.6 * 9 * 0.9; // 9 is the bulletWidth in DrawFireRateTool
                offsetY = -1.85 * 15 * 0.9; // 15 is the bulletHeight in DrawFireRateTool
                break;
            case TOOL_ADD_SPEED:
                offsetX = -1.85 * 17.5; // 17.5 is the triangleHeight in DrawAddSpeedTool
                offsetY = -2.8 * 10; // 10 is the triangleBase in DrawAddSpeedTool
                break;
            case TOOL_SHIELD:
                offsetX = -1.35 * 15; // 15 is the squareSide in DrawShieldTool
                offsetY = -1.55 * 15;
                break;
        }

        if (IsColliding(static_cast<int>(playerTank.getPosX()), static_cast<int>(playerTank.getPosY()), tool.getX(), tool.getY(), offsetX, offsetY) && tool.getIsVisible()) {
            // Handle health tool
            if (tool.getType() == TOOL_HEALTH) {
                if (playerTank.getHealth() < 50) {
                    float newHealth = std::min(playerTank.getHealth() + tool.getPower(), playerTank.getHealthMax());
                    playerTank.setHealth(newHealth);
                    tool.setIsVisible(false);
                } else {
                    std::cout << "You cannot apply add health tool since you have the max health value." << std::endl;
                    allToolsNotVisible = false;
                    continue;
                }
            }
            else if (tool.getType() == TOOL_FIRE_RATE) {
                std::vector<int> bulletCount = playerTank.getBulletCount(); // Make a copy
                for (int& count : bulletCount) {
                    count += 5; // Increase each bullet type's count by 5
                }
                playerTank.setBulletCount(bulletCount); // Set the modified vector back to the tank
                tool.setIsVisible(false);
            }

            // Handle add speed tool
            else if (tool.getType() == TOOL_ADD_SPEED) {
                float newSpeed = playerTank.getSpeed() * 1.5f;
                playerTank.setSpeed(newSpeed);
                tool.setIsVisible(false);
            }
            // Handle add shield tool
            else if (tool.getType() == TOOL_SHIELD) {
                float newArmor = playerTank.getArmor() + 30;
                playerTank.setArmor(newArmor);
                tool.setIsVisible(false);
            }

            // Additional code for add bullet tool
        }
        if (tool.getIsVisible()) {
            allToolsNotVisible = false;
        }
    }

    if (allToolsNotVisible && sharedRespawnTimer == 0) {
        sharedRespawnTimer = 1500; // Respawn time
    }

    if (sharedRespawnTimer > 0) {
        sharedRespawnTimer--;
        if (sharedRespawnTimer <= 0) {
            for (auto& tool : tools) {
                tool.setIsVisible(true);
            }
        }
    }
}
