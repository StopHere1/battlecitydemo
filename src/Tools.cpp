//
//  Tools.cpp
//  FinalProject
//
//  Created by Jingxia Zhong on 11/13/23.
//

#include <cmath>
#include <string>
#include "tool.h"
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
    int circleRadius = 7;
    int triangleSize = 15;
    DrawCircle(this->x - circleRadius, this->y, circleRadius, red);
    DrawCircle(this->x + circleRadius, this->y, circleRadius, red);
    
    glColor3ubv(red);
    glBegin(GL_TRIANGLES);
    glVertex2i(this->x - triangleSize, this->y);
    glVertex2i(this->x + triangleSize, this->y);
    glVertex2i(this->x, this->y + triangleSize);
    glEnd();
}

void Tool::DrawFireRateTool() const {
    const unsigned char black[3] = {0, 0, 0};
    const unsigned char gold[3] = {255, 215, 0};

    glColor3ubv(gold);
    int bulletWidth = 9;
    int bulletHeight = 15;
    int triangleHeight = 7.5;
    glBegin(GL_TRIANGLES);
    glVertex2i(this->x, this->y - triangleHeight);
    glVertex2i(this->x - bulletWidth / 2, this->y);
    glVertex2i(this->x + bulletWidth / 2, this->y);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(this->x - bulletWidth / 2, this->y);
    glVertex2i(this->x + bulletWidth / 2, this->y);
    glVertex2i(this->x + bulletWidth / 2, this->y + bulletHeight);
    glVertex2i(this->x - bulletWidth / 2, this->y + bulletHeight);
    glEnd();

    int plusSize = 15;
    glColor3ubv(black);
    glBegin(GL_LINES);
    glVertex2i(this->x + bulletWidth / 2 + 4.5, this->y - bulletHeight / 2);
    glVertex2i(this->x + bulletWidth / 2 + 4.5 + plusSize, this->y - bulletHeight / 2);
    glVertex2i(this->x + bulletWidth / 2 + 4.5 + plusSize / 2, this->y - bulletHeight / 2 - plusSize / 2);
    glVertex2i(this->x + bulletWidth / 2 + 4.5 + plusSize / 2, this->y - bulletHeight / 2 + plusSize / 2);
    glEnd();
}

void Tool::DrawLandMineTool() const {
    const unsigned char color[3] = {0, 0, 0};
    int size = 25;
    int halfSize = size / 2;
    int quarterSize = size / 4;
    int dotRadius = size / 10;

    glColor3ubv(color);
    DrawCircle(this->x, this->y, halfSize, color);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; ++i) {
        double angle = i * M_PI / 4.0;
        glVertex2i(this->x, this->y);
        glVertex2i(this->x + halfSize * cos(angle - M_PI / 8), this->y + halfSize * sin(angle - M_PI / 8));
        glVertex2i(this->x + halfSize * cos(angle + M_PI / 8), this->y + halfSize * sin(angle + M_PI / 8));
    }
    glEnd();

    DrawCircle(this->x, this->y, quarterSize, color);
    DrawCircle(this->x, this->y, dotRadius, color);
}

void Tool::DrawShieldTool() const {
    const unsigned char black[3] = {0, 0, 0};
    int squareSide = 30;
    int radius = squareSide / 2;

    glColor3ubv(black);
    glBegin(GL_QUADS);
    glVertex2i(this->x - radius, this->y - radius);
    glVertex2i(this->x + radius, this->y - radius);
    glVertex2i(this->x + radius, this->y + radius);
    glVertex2i(this->x - radius, this->y + radius);
    glEnd();

    DrawCircle(this->x, this->y + radius, radius, black);
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
