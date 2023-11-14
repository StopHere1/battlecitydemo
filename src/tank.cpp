//
// Created by anthonyshen on 11/13/23.
//
#include "../include/tank.h"
#include <iostream>
#include <cstring>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

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
float tank::getLoad() {
    return load;
}
float tank::getSpeed() {
    return speed;
}
float tank::getPower() {
    return power;
}
float tank::getWeight() {
    return weight;
}
int tank::getState() {
    return state;
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
void tank::setLoad(float input) {
    load = input;
}
void tank::setSpeed(float input) {
    speed = input;
}
void tank::setPower(float input) {
    power = input;
}
void tank::setWeight(float input) {
    weight = input;
}
void tank::setState(int input) {
    state = input;
}
float calSpeed(float power, float load, float weight) {
    return power/(load+weight);
}

int tank::init(type type) {
    if(type == type1){//standard tank
        this->posX = 0;
        this->posY = 0;
        this->armor = 100;
        this->weight = 100;
        this->health = 100;
        this->load = 100;
        this->power = 100;
        this->speed = calSpeed(power, load, weight);
        return 0;
    } else if (type == type2){//fast tank
        this->posX = 0;
        this->posY = 0;
        this->armor = 50;
        this->weight = 50;
        this->health = 100;
        this->load = 50;
        this->power = 100;
        this->speed = calSpeed(power, load, weight);
        return 0;
    } else if (type == type3){//heavy tank
        this->posX = 0;
        this->posY = 0;
        this->armor = 200;
        this->weight = 200;
        this->health = 100;
        this->load = 100;
        this->power = 200;
        this->speed = calSpeed(power, load, weight);
        return 0;
    } else if (type == type4){//Load tank
        this->posX = 0;
        this->posY = 0;
        this->armor = 80;
        this->weight = 150;
        this->health = 100;
        this->load = 200;
        this->power = 200;
        this->speed = calSpeed(power, load, weight);
        return 0;
    } else {
        printf("Error: tank type not found");
        return 1;
    }
}

void tank::move(int key, int player)
{
    if(player == 0){
        if(key == FSKEY_W){
            this->posY -= 1;
        }
        if(key == FSKEY_S){
            this->posY += 1;
        }
        if(key == FSKEY_A){
            this->posX -= 1;
        }
        if(key == FSKEY_D){
            this->posX += 1;
        }
    }
    if(player == 1){
        if(key == FSKEY_UP){
            this->posY -= 1;
        }
        if(key == FSKEY_DOWN){
            this->posY += 1;
        }
        if(key == FSKEY_LEFT){
            this->posX -= 1;
        }
        if(key == FSKEY_RIGHT){
            this->posX += 1;
        }
    }
}

