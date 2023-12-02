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
    int offsetY = 4 * circleRadius;
    
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
    
    int offsetX = 3 * bulletWidth;
    int offsetY = 1.5 * bulletHeight;
    
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

void Tool::DrawLandMineTool() const {
    int size = std::min(this->power, 25);
    int halfSize = size / 2 * 0.75;
    int quarterSize = size / 4 * 0.75;
    const unsigned char black[3] = {0, 0, 0};
    glColor3ubv(black);
    
    int offsetX = 2 * halfSize;
    int offsetY = 2 * halfSize;
    
    DrawCircle(this->x - offsetX, this->y - offsetY, halfSize, black);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; ++i) {
        double angle = i * M_PI / 4.0;
        glVertex2i(this->x - offsetX, this->y - offsetY);
        glVertex2i(this->x + halfSize * cos(angle - M_PI / 8) - offsetX, this->y + halfSize * sin(angle - M_PI / 8) - offsetY);
        glVertex2i(this->x + halfSize * cos(angle + M_PI / 8) - offsetX, this->y + halfSize * sin(angle + M_PI / 8) - offsetY);
    }
    glEnd();

    DrawCircle(this->x - offsetX, this->y - offsetY, quarterSize, black);
    int dotRadius = size / 10;
    DrawCircle(this->x - offsetX, this->y - offsetY, dotRadius, black);

    int tinyTriangleSize = 5;
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; ++i) {
        double angle = i * M_PI / 4.0;
        int outerRadius = halfSize + 2;
        int tipX = this->x + (outerRadius + tinyTriangleSize) * cos(angle) - offsetX;
        int tipY = this->y + (outerRadius + tinyTriangleSize) * sin(angle) - offsetY;
        glVertex2i(tipX, tipY);
        glVertex2i(this->x + outerRadius * cos(angle + M_PI / 16) - offsetX, this->y + outerRadius * sin(angle + M_PI / 16) - offsetY);
        glVertex2i(this->x + outerRadius * cos(angle - M_PI / 16) - offsetX, this->y + outerRadius * sin(angle - M_PI / 16) - offsetY);
    }
    glEnd();
}

void Tool::DrawShieldTool() const {
    const unsigned char black[3] = {0, 0, 0};
    int squareSide = 20;
    int radius = squareSide / 2;
    
    int offsetX = 0.8 * squareSide;
    int offsetY = 0.7 * squareSide;

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

     tools.emplace_back(120, 120, TOOL_HEALTH, true, 0, 20);
     tools.emplace_back(560, 360, TOOL_FIRE_RATE, true, 0, 20);
     tools.emplace_back(440, 400, TOOL_LAND_MINE, true, 0, 20);
     tools.emplace_back(880, 640, TOOL_SHIELD, true, 0, 20);
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
                case TOOL_LAND_MINE:
                    tool.DrawLandMineTool();
                    break;
                case TOOL_SHIELD:
                    tool.DrawShieldTool();
                    break;
            }
        }
    }
}

bool IsColliding(int tankX, int tankY, int toolX, int toolY) {
    // Define a collision range
    const int collisionRange = 10;
    return std::abs(tankX - toolX) <= collisionRange && std::abs(tankY - toolY) <= collisionRange;
}

void UpdateTools(std::vector<Tool>& tools, const tank& playerTank, int& sharedRespawnTimer) {
    bool allToolsNotVisible = true;

    tank& nonConstTank = const_cast<tank&>(playerTank);

    for (auto& tool : tools) {
        if (IsColliding(static_cast<int>(nonConstTank.getPosX()), static_cast<int>(nonConstTank.getPosY()), tool.getX(), tool.getY()) && tool.getIsVisible()) {
            tool.setIsVisible(false);
        }
        if (tool.getIsVisible()) {
            allToolsNotVisible = false;
        }
    }

    if (allToolsNotVisible && sharedRespawnTimer == 0) {
        sharedRespawnTimer = 1500; // example respawn time
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
