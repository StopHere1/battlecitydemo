//
// Created by anthonyshen on 11/13/23.
//
#include "../include/tank.h"
#include <iostream>
#include <cstdio>

float tank::getPosX() {
    return posX;
}
float tank::getPosY() {
    return posY;
}
float tank::getArmor() {
    return armor;
}
float tank::getHealth() {
    return health;
}
float tank::getHealthMax() {
    return healthMax;
}
float tank::getSpeed() {
    return speed;
}
int tank::getState() {
    return state;
}
float tank::getFireAngle() {
    return fireAngle;
}
int tank::getDirection() {
    return direction;
}
int tank::getUser() {
    return user;
}
std::vector<int> tank::getBulletCount() {
    return BulletCount;
}
void tank::setPosX(float input) {
    posX = input;
}
void tank::setPosY(float input) {
    posY = input;
}
void tank::setArmor(float input) {
    armor = input;
}
void tank::setHealth(float input) {
    health = input;
}
void tank::setHealthMax(float input) {
    healthMax = input;
}
void tank::setSpeed(float input) {
    speed = input;
}
void tank::setState(int input) {
    state = input;
}
void tank::setFireAngle(float input) {
    fireAngle = input;
}
void tank::setDirection(int input) {
    direction = input;
}
void tank::setBulletCount(std::vector<int> count) {
    BulletCount = count;
}
void tank::setUser(int input) {
    if(input == 0 || input == 1){
        user = input;
    } else {
        printf("Error: User Type not found");
    }
}

int tank::init(Type type, int User) {
    if(User != 0 && User != 1){
        printf("Error: User Type not found");
        return 1;
    } else {
        this->user = User;
        if (type == type1) {//standard tank
            this->tankType = type1;
            this->armor = 50;
            this->health = 50;
            this->healthMax = 50;
            this->fireAngle = 0;
            this->direction = 0;
            this->speed = 10;
            return 0;
        } else if (type == type2) {//fast tank
            this->tankType = type2;
            this->armor = 30;
            this->health = 50;
            this->healthMax = 50;
            this->direction = 0;
            this->fireAngle = 0;
            this->speed = 20;
            return 0;
        } else if (type == type3) {//heavy tank
            this->tankType = type3;
            this->armor = 100;
            this->health = 50;
            this->healthMax = 50;
            this->fireAngle = 0;
            this->direction = 0;
            this->speed = 5;
            return 0;
        } else if (type == type4) {//Load tank
            this->tankType = type4;
            this->armor = 40;
            this->health = 80;
            this->healthMax = 80;
            this->fireAngle = 0;
            this->direction = 0;
            this->speed = 10;
            this->BulletCount = {10, 20, 10};
            return 0;
        } else {
            printf("Error: tank Type not found");
            return 1;
        }
    }
}

void tank::move()
{
    if(this->health >0) {
        if(this->canMove){
            this->posX = this->nextPosX;
            this->posY = this->nextPosY;
        }
    }
}

void drawBlk(float x, float y, float width, int direction) {//draw black block, standard size 40, posX, posY is the center of the block
    float ratio = width / 40;
    glColor3ub(0, 0, 0);
    if (direction == 0) {
        glBegin(GL_QUADS);
        glVertex2f(x - 4 * ratio, y - 2 * ratio);
        glVertex2f(x + 4 * ratio, y - 2 * ratio);
        glVertex2f(x + 4 * ratio, y + 2 * ratio);
        glVertex2f(x - 4 * ratio, y + 2 * ratio);
        glEnd();
    }
    else {
        glBegin(GL_QUADS);
        glVertex2f(x - 2 * ratio, y - 4 * ratio);
        glVertex2f(x + 2 * ratio, y - 4 * ratio);
        glVertex2f(x + 2 * ratio, y + 4 * ratio);
        glVertex2f(x - 2 * ratio, y + 4 * ratio);
        glEnd();
    }
}

void drawAim(float x, float y, float width, float angle) {//draw aim, standard size 40, posX, posY is the center of the aim
    float ratio = width/40;
    glPushMatrix();
    // translate to the position of the tank
    glTranslatef(x, y, 0);
    // Rotate the turret around the center of the tank
    glRotatef(-angle*180/PI + 90, 0, 0, 1);
    // Move the turret back to its original position
    glTranslatef(0, -15*ratio, 0);
    glBegin(GL_QUADS);
    glVertex2f(-3*ratio, -15*ratio);
    glVertex2f(3*ratio, -15*ratio);
    glVertex2f(3*ratio, 15*ratio);
    glVertex2f(-3*ratio, 15*ratio);
    glEnd();
    glPopMatrix();
}

void drawBody(float x, float y, float width, int direction) {//draw tank body, standard size 40, posX, posY is the center of the tank
    float ratio = width / 40;
    if (direction == 1) {//horizontal
        glBegin(GL_QUADS);
        glVertex2f(x - 20 * ratio, y - 20 * ratio);
        glVertex2f(x - 20 * ratio, y - 12 * ratio);
        glVertex2f(x + 20 * ratio, y - 12 * ratio);
        glVertex2f(x + 20 * ratio, y - 20 * ratio);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(x + 20 * ratio, y + 20 * ratio);
        glVertex2f(x + 20 * ratio, y + 12 * ratio);
        glVertex2f(x - 20 * ratio, y + 12 * ratio);
        glVertex2f(x - 20 * ratio, y + 20 * ratio);
        glEnd();
        //draw the tank body with red color
        glBegin(GL_QUADS);
        glVertex2f(x - 13 * ratio, y - 12 * ratio);
        glVertex2f(x + 13 * ratio, y - 12 * ratio);
        glVertex2f(x + 13 * ratio, y + 12 * ratio);
        glVertex2f(x - 13 * ratio, y + 12 * ratio);
        glEnd();
    }
    else if(direction == 0){//vertical
        glBegin(GL_QUADS);
        glVertex2f(x-20*ratio, y-20*ratio);
        glVertex2f(x-12*ratio, y-20*ratio);
        glVertex2f(x-12*ratio, y+20*ratio);
        glVertex2f(x-20*ratio, y+20*ratio);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(x+20*ratio, y-20*ratio);
        glVertex2f(x+12*ratio, y-20*ratio);
        glVertex2f(x+12*ratio, y+20*ratio);
        glVertex2f(x+20*ratio, y+20*ratio);
        glEnd();
        //draw the tank body with red color
        glBegin(GL_QUADS);
        glVertex2f(x-12*ratio, y-13*ratio);
        glVertex2f(x+12*ratio, y-13*ratio);
        glVertex2f(x+12*ratio, y+13*ratio);
        glVertex2f(x-12*ratio, y+13*ratio);
        glEnd();
    }
}

void tank::draw(float width) {//draw tank according to its Type, standard size 40, posX, posY is the center of the tank
    float ratio = width/40;
//    bulletShot.Draw(posX, posY, fireAngle);
    tankBullet.Draw(posX, posY, fireAngle);
    if(this->health >0) {//tank still alive
        if (this->tankType == type1) {
            //draw the tank wheel with red color
            glColor3ub(128, 30, 0);
            drawBody(posX, posY, width, this->direction);
            //draw the wheel gap with black color
            if (this->direction == 0) {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX + 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY - 16 * ratio, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY + 16 * ratio, width, this->direction);
                }
            }
            //draw the tank head with red color
            glColor3ub(255, 30, 0);
            drawAim(posX, posY, width, fireAngle);
        } else if (this->tankType == type2) {
            glColor3ub(30, 128, 0);
            drawBody(posX, posY, width, this->direction);
            //draw the wheel gap with black color
            if (this->direction == 0) {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX + 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY - 16 * ratio, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY + 16 * ratio, width, this->direction);
                }
            }
            glColor3ub(30, 255, 0);
            drawAim(posX, posY, width, fireAngle);
        }else if (this->tankType == type3) {
            glColor3ub(0, 30, 128);
            drawBody(posX, posY, width, this->direction);
            //draw the wheel gap with black color
            if (this->direction == 0) {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX + 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY - 16 * ratio, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY + 16 * ratio, width, this->direction);
                }
            }
            glColor3ub(0, 30, 255);
            drawAim(posX, posY, width, fireAngle);
        } else if (this->tankType == type4) {
            glColor3ub(128, 128, 0);
            drawBody(posX, posY, width, this->direction);
            //draw the wheel gap with black color
            if (this->direction == 0) {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX + 16 * ratio, posY - 16 * ratio + 8 * ratio * i, width, this->direction);
                }
            } else {
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY - 16 * ratio, width, this->direction);
                }
                for (int i = 0; i < 5; i++) {
                    drawBlk(posX - 16 * ratio + 8 * ratio * i, posY + 16 * ratio, width, this->direction);
                }
            }
            glColor3ub(200, 200, 0);
            drawAim(posX, posY, width, fireAngle);
        } else {
            printf("Error: tank Type not found");
        }
    }
}

void wrap2pi(float &angle) {
    if(angle > 2*PI){
        angle -= 2*PI;
    }
    if(angle < 0){
        angle += 2*PI;
    }
}

void tank::rotate(int key) {
    float stepAngle = 45*PI/180;
    if(this->health >0) {
        if ((key == FSKEY_J && user == 0) || (key == FSKEY_5 && user == 1)) {//clockwise
            this->fireAngle -= stepAngle;
            wrap2pi(this->fireAngle);
        } else if ((key == FSKEY_K && user == 0) || (key == FSKEY_6 && user == 1)) {//counter-clockwise
            this->fireAngle += stepAngle;
            wrap2pi(this->fireAngle);
        }
    }
}

void tank::newFire(int key) {
    if(this->health >0) {
        if ((key == FSKEY_SPACE && this->user == 0) || (key == FSKEY_0 && this->user == 1)) {
            if (BulletCount[currentBulletType] > 0) {
                if (!tankBullet.GetIsHit() && tankBullet.GetIsShot()) {
                    std::cout << "Error: Bullet Not Hit!" << std::endl;
                } else {
                    BulletCount[currentBulletType]--;
                    tankBullet.ChangeBulletType(currentBulletType);
                    tankBullet.ShootBullet();
                    std::cout << "Fire Success!" << std::endl;
                }
            } else {
                std::cout << "Error: No More Bullets!" << std::endl;
            }
        }
    }
}

void tank::checkBulletCount() {
    std::cout << "Bullet Count: ";
    for(int i = 0; i < 3; i++){
        std::cout <<"BulletType" << i << ": " << BulletCount[i] << " ";
    }
    std::cout << std::endl;
}

void tank::changeFireBullet(int key) {
    if(this->health >0) {
        if ((key == FSKEY_B && this->user == 0) || (key == FSKEY_7 && this->user == 1)) {
            currentBulletType = (currentBulletType + 1) % 3;
            tankBullet.ChangeBulletType(currentBulletType);
            std::cout << "Current Bullet Type: " << currentBulletType << std::endl;
            checkBulletCount();
        }
    }
}

void tank::newPickUpBullet(std::vector<int> bulletPack) {
    for(int i = 0; i < 3; i++){
        BulletCount[i] += bulletPack[i];
    }
    checkBulletCount();
}

void tank::setSoundPlayer(Sound *sound) {
    this->soundPlayer = sound;
}

void tank::passSoundPlayer() {
    tankBullet.setSoundPlayer(this->soundPlayer);
}

bool tank::checkTankHealth() {
    if(this->health > 0){
        return true;//alive
    } else {
        return false;//dead
    }
}

void tank::setCanMove(bool input) {
    this->canMove = input;
}

void tank::setNextPosX(float input) {
    this->nextPosX = input;
}

void tank::setNextPosY(float input) {
    this->nextPosY = input;
}

float tank::getNextPosX() {
    return this->nextPosX;
}

float tank::getNextPosY() {
    return this->nextPosY;
}

bool tank::getCanMove() {
    return this->canMove;
}

std::vector<float> tank::checkMove(int key) {
    if(this->canMove) {
        if (this->health > 0) {
            if (this->user == 0) {
                if (key == FSKEY_W) {
                    if(nextPosY - 20 <= 0){
                        this->nextPosY = 20;
                        this->canMove = false;
                    } else {
                        this->nextPosY = this->posY - speed;
                    }
                    this->direction = 0;
                }
                if (key == FSKEY_S) {
                    if(nextPosY + 20 >= 720){
                        this->nextPosY = 700;
                        this->canMove = false;
                    } else {
                        this->nextPosY = this->posY + speed;
                    }
                    this->direction = 0;
                }
                if (key == FSKEY_A) {
                    if(nextPosX - 20 <= 0){
                        this->nextPosX = 20;
                        this->canMove = false;
                    } else {
                        this->nextPosX = this->posX - speed;
                    }
                    this->direction = 1;
                }
                if (key == FSKEY_D) {
                    if(nextPosX + 20 >= 1280){
                        this->nextPosX = 1260;
                        this->canMove = false;
                    } else {
                        this->nextPosX = this->posX + speed;
                    }
                    this->direction = 1;
                }
            } else if (this->user == 1) {
                if (key == FSKEY_UP) {
                    if(nextPosY - 20 <= 0){
                        this->nextPosY = 20;
                        this->canMove = false;
                    } else {
                        this->nextPosY = this->posY - speed;
                    }
                    this->direction = 0;
                }
                if (key == FSKEY_DOWN) {
                    if(nextPosY + 20 >= 720){
                        this->nextPosY = 700;
                        this->canMove = false;
                    } else {
                        this->nextPosY = this->posY + speed;
                    }
                    this->direction = 0;
                }
                if (key == FSKEY_LEFT) {
                    if(nextPosX - 20 <= 0){
                        this->nextPosX = 20;
                        this->canMove = false;
                    } else {
                        this->nextPosX = this->posX - speed;
                    }
                    this->direction = 1;
                }
                if (key == FSKEY_RIGHT) {
                    if(nextPosX + 20 >= 1280){
                        this->nextPosX = 1260;
                        this->canMove = false;
                    } else {
                        this->nextPosX = this->posX + speed;
                    }
                    this->direction = 1;
                }
            }
        }
    }
    return {this->nextPosX, this->nextPosY};
}

void tank::setTankType(tank::Type type) {
    this->tankType = type;
    this->changeTankPara();
}

void tank::changeTankPara() {
    if (this->tankType == type1) {//standard tank
        this->armor = 50;
        this->health = 50;
        this->healthMax = 50;
        this->speed = 10;
    } else if (this->tankType == type2) {//fast tank
        this->armor = 30;
        this->health = 50;
        this->healthMax = 50;
        this->speed = 20;
    } else if (this->tankType == type3) {//heavy tank
        this->armor = 100;
        this->health = 50;
        this->healthMax = 50;
        this->speed = 5;
    } else if (this->tankType == type4) {//Load tank
        this->armor = 40;
        this->health = 50;
        this->healthMax = 50;
        this->speed = 10;
        this->BulletCount = {10, 20, 10};
    } else {
        printf("Error: tank Type not found");
    }
}













