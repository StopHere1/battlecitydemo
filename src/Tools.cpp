//
//  Tools.cpp
//  FinalProject
//
//  Created by Jingxia Zhong on 11/13/23.
//

#include <cmath>
#include <string>
#include "tool.hpp"
#include "fssimplewindow.h"

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

void DrawHealthTool(int x, int y) {
    // Red heart shape
    const unsigned char black[3] = {0, 0, 0};
    const unsigned char red[3] = {255, 0, 0};

    // Increase the size of the heart's circles and triangle
    int circleRadius = 7; // Adjusted radius for the circles of the heart
    int triangleSize = 15; // Adjusted size for the triangle of the heart

    DrawCircle(x - circleRadius, y, circleRadius, red); // Left circle of the heart
    DrawCircle(x + circleRadius, y, circleRadius, red); // Right circle of the heart

    int squareSize = 30; // Adjusted size for the square
    glColor3ubv(black); // Set color to black for the square
    glBegin(GL_LINE_LOOP);
    glVertex2i(x - squareSize / 2, y - squareSize / 2);
    glVertex2i(x + squareSize / 2, y - squareSize / 2);
    glVertex2i(x + squareSize / 2, y + squareSize / 2);
    glVertex2i(x - squareSize / 2, y + squareSize / 2);
    glEnd();
    
    // Adjusted triangle part of the heart
    glColor3ubv(red);
    glBegin(GL_TRIANGLES);
    glVertex2i(x - triangleSize, y);
    glVertex2i(x + triangleSize, y);
    glVertex2i(x, y + triangleSize);
    glEnd();
}

void DrawFireRateTool(int x, int y) {
    const unsigned char black[3] = {0, 0, 0};
    const unsigned char gold[3] = {255, 215, 0};

    // Draw square around the tool
    int squareSize = 30; // Adjust size as needed
    glColor3ubv(black); // Set color to black for the square
    glBegin(GL_LINE_LOOP);
    glVertex2i(x - squareSize / 2, y - squareSize / 2);
    glVertex2i(x + squareSize / 2, y - squareSize / 2);
    glVertex2i(x + squareSize / 2, y + squareSize / 2);
    glVertex2i(x - squareSize / 2, y + squareSize / 2);
    glEnd();

    // Draw the bullet (rectangle with a triangle on top)
    glColor3ubv(gold); // Set color to gold for the bullet

    // Bullet triangle (tip)
    int bulletWidth = 6;
    int bulletHeight = 10;
    int triangleHeight = 5;
    glBegin(GL_TRIANGLES);
    glVertex2i(x, y - triangleHeight); // Top vertex of the triangle
    glVertex2i(x - bulletWidth / 2, y); // Bottom left vertex of the triangle
    glVertex2i(x + bulletWidth / 2, y); // Bottom right vertex of the triangle
    glEnd();
    
    // Bullet rectangle
    glBegin(GL_QUADS);
    glVertex2i(x - bulletWidth / 2, y);
    glVertex2i(x + bulletWidth / 2, y);
    glVertex2i(x + bulletWidth / 2, y + bulletHeight);
    glVertex2i(x - bulletWidth / 2, y + bulletHeight);
    glEnd();

    // Draw the "+" sign to the right of the bullet
    int plusSize = 10;
    glColor3ubv(black); // Black color for the "+" sign
    glBegin(GL_LINES);
    // Horizontal line of "+"
    glVertex2i(x + bulletWidth / 2 + 3, y - bulletHeight / 2);
    glVertex2i(x + bulletWidth / 2 + 3 + plusSize, y - bulletHeight / 2);
    // Vertical line of "+"
    glVertex2i(x + bulletWidth / 2 + 3 + plusSize / 2, y - bulletHeight / 2 - plusSize / 2);
    glVertex2i(x + bulletWidth / 2 + 3 + plusSize / 2, y - bulletHeight / 2 + plusSize / 2);
    glEnd();
}

void DrawLandMineTool(int centerX, int centerY, int size, const unsigned char color[3]) {
    int halfSize = size / 2;
    int quarterSize = size / 4;
    glColor3ubv(color);
    DrawCircle(centerX, centerY, halfSize, color);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; ++i) {
        double angle = i * M_PI / 4.0;
        glVertex2i(centerX, centerY);
        glVertex2i(centerX + halfSize * cos(angle - M_PI / 8), centerY + halfSize * sin(angle - M_PI / 8));
        glVertex2i(centerX + halfSize * cos(angle + M_PI / 8), centerY + halfSize * sin(angle + M_PI / 8));
    }
    glEnd();
    DrawCircle(centerX, centerY, quarterSize, color);
    int dotRadius = size / 10;
    DrawCircle(centerX, centerY, dotRadius, color);
}

void DrawShieldTool(int x, int y) {
    // Green square
    const unsigned char green[3] = {0, 255, 0};
    glColor3ubv(green);
    glBegin(GL_QUADS);
    glVertex2i(x - 5, y - 5);
    glVertex2i(x + 5, y - 5);
    glVertex2i(x + 5, y + 5);
    glVertex2i(x - 5, y + 5);
    glEnd();
}

void DisplayTools(const std::vector<Tool>& tools) {
    for (const auto& tool : tools) {
        if (tool.getIsVisible()) {
            switch (tool.getType()) {
                case TOOL_HEALTH:
                    DrawHealthTool(tool.getX(), tool.getY());
                    break;
                case TOOL_FIRE_RATE:
                    DrawFireRateTool(tool.getX(), tool.getY());
                    break;
                case TOOL_LAND_MINE:
                    static const unsigned char blueColor[3] = {0, 0, 255};
                    DrawLandMineTool(tool.getX(), tool.getY(), 10, blueColor);
                    break;
                case TOOL_SHIELD:
                    DrawShieldTool(tool.getX(), tool.getY());
                    break;
            }
        }
    }
}

// Helper function for checking collision
bool IsColliding(int tankX, int tankY, int toolX, int toolY) {
    // Define a collision range
    const int collisionRange = 10;
    return std::abs(tankX - toolX) <= collisionRange && std::abs(tankY - toolY) <= collisionRange;
}

void UpdateTools(std::vector<Tool>& tools, const SimulatedTank& tank, int& sharedRespawnTimer) {
    bool allToolsNotVisible = true;

    // Check for collision and make tools disappear
    for (auto& tool : tools) {
        if (IsColliding(tank.getX(), tank.getY(), tool.getX(), tool.getY()) && tool.getIsVisible()) {
            tool.setIsVisible(false);
        }
        if (tool.getIsVisible()) {
            allToolsNotVisible = false;
        }
    }

    // If all tools are not visible and the timer has not started, start it
    if (allToolsNotVisible && sharedRespawnTimer == 0) {
        sharedRespawnTimer = 1500; // example respawn time
    }

    // Handle the shared respawn timer
    if (sharedRespawnTimer > 0) {
        sharedRespawnTimer--;
        if (sharedRespawnTimer <= 0) {
            // Respawn all tools when the timer reaches zero
            for (auto& tool : tools) {
                tool.setIsVisible(true);
            }
        }
    }
}
