//
// Created by anthonyshen on 11/13/23.
//
#include "../include/tank.h"
#include <iostream>
#include <cstring>

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
int tank::getLoad() {
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
int tank::getMagSize() {
    return magSize;
}
float tank::getFireAngle() {
    return fireAngle;
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
void tank::setLoad(int input) {
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
void tank::setMagSize(int input) {
    magSize = input;
}
void tank::setFireAngle(float input) {
    fireAngle = input;
}
float calSpeed(float power, int load, float weight) {
    return power/(load+weight);
}

int tank::init(Type type) {
    if(type == type1){//standard tank
        this->tankType = type1;
        this->posX = 0;
        this->posY = 0;
        this->armor = 100;
        this->weight = 100;
        this->health = 100;
        this->healthMax = 100;
        this->load = 100;
        this->magSize = 10;
        this->fireAngle = 0;
        this->power = 100;
        this->speed = 10;
        return 0;
    } else if (type == type2){//fast tank
        this->tankType = type2;
        this->posX = 0;
        this->posY = 0;
        this->armor = 50;
        this->weight = 50;
        this->health = 100;
        this->healthMax = 100;
        this->load = 50;
        this->magSize = 5;
        this->fireAngle = 0;
        this->power = 100;
        this->speed = 20;
        return 0;
    } else if (type == type3){//heavy tank
        this->tankType = type3;
        this->posX = 0;
        this->posY = 0;
        this->armor = 200;
        this->weight = 200;
        this->health = 100;
        this->healthMax = 100;
        this->load = 100;
        this->magSize = 20;
        this->fireAngle = 0;
        this->power = 200;
        this->speed = 5;
        return 0;
    } else if (type == type4){//Load tank
        this->tankType = type4;
        this->posX = 0;
        this->posY = 0;
        this->armor = 80;
        this->weight = 150;
        this->health = 100;
        this->healthMax = 100;
        this->load = 200;
        this->magSize = 10;
        this->fireAngle = 0;
        this->power = 200;
        this->speed = 10;
        return 0;
    } else {
        printf("Error: tank Type not found");
        return 1;
    }
}

void tank::move(int key)
{

    if(key == FSKEY_W || key == FSKEY_UP){
        this->posY -= speed;
    }
    if(key == FSKEY_S || key == FSKEY_DOWN){
        this->posY += speed;
    }
    if(key == FSKEY_A || key == FSKEY_LEFT){
        this->posX -= speed;
    }
    if(key == FSKEY_D || key == FSKEY_RIGHT){
        this->posX += speed;
    }
}

void tank::singleReload(){//load one bullet from bulletLoad to bulletMag, less time cost
    //use splice to move the first element of bulletLoad to the end of bulletMag
    if(bulletMag.size() < magSize) {
        while (!bulletLoad.empty() && bulletMag.size() < magSize) {
            bulletMag.splice(bulletMag.end(), bulletLoad, bulletLoad.begin());
        }
        std::cout << "Reload Success!" << std::endl;
    } else {
        std::cout << "Error: Mag Is Full!" << std::endl;
    }
}

void tank::reload() {//load a full mag from bulletLoad to bulletMag, more time cost
    if(bulletMag.size() < magSize){
        while(!bulletLoad.empty() && bulletMag.size() < magSize){
            bulletMag.splice(bulletMag.end(), bulletLoad, bulletLoad.begin());
        }
        std::cout << "Reload Success!" << std::endl;
    } else {
        std::cout << "Error: Mag Is Full!" << std::endl;
    }
}

void tank::fire() {
    if(!bulletMag.empty()){
        //use splice to move the first element of bulletMag to the end of bulletShot
        bulletShot = bulletMag.front();
        bulletMag.pop_front();
        bulletShot.ShootBullet();
        bulletShot.Draw(posX, posY, fireAngle);
        std::cout << "Fire Success!" << std::endl;
    } else {
        std::cout << "Error: Need Reload!" << std::endl;
    }
}

void tank::checkLoad() {//check the bulletLoad and healthLoad
    if(!bulletLoad.empty()){
        std::cout << "Bullet Pack Remains: " << bulletLoad.size() << std::endl;
    } else {
        std::cout << "Error: Bullet Load Empty!" << std::endl;
    }
    if(!healthLoad.empty()){
        std::cout << "Health Pack Remains: " << healthLoad.size() << std::endl;
    } else {
        std::cout << "Error: Health Load Empty!" << std::endl;
    }
}

void tank::printBulletMag() {//print the bullets in the mag
    if(bulletMag.empty()){
        std::cout << "Error: No Bullet In Mag!" << std::endl;
    }
    else {
        std::cout << "Bullets In the Mag: ";
        for(auto i : bulletMag){
            std::cout << i.GetBulletType() << " ";
        }
        std::cout << std::endl;
    }
}

void tank::heal() {//heal the tank
    if(!healthLoad.empty()){
        if(health + 50 <= healthMax){
            health += 50;
            healthLoad.pop_front();
        } else {
            health = healthMax;
            healthLoad.pop_front();
        }
    } else {
        std::cout << "Error: Health Load Empty!" << std::endl;
    }
}

void tank::pickUpBullet(std::list<Bullet> bulletPack) {//pick up bullet package to bulletLoad
    if(bulletLoad.size() >= load){
        std::cout << "Error: Bullet Load Full!" << std::endl;
    }
    else {
        while (!bulletPack.empty() && bulletLoad.size() < load) {
            //use splice to move the first element of bulletPack to the end of bulletLoad
            bulletLoad.splice(bulletLoad.end(), bulletPack, bulletPack.begin());
        }
        std::cout << "Bullet Resupply Success!" << std::endl;
    }
}

void tank::pickUpHealth(std::list<Tool> healthPack) {//pick up health package to healthLoad
    if(healthLoad.size() >= load){
        std::cout << "Error: Health Load Full!" << std::endl;
    }
    else {
        while (!healthPack.empty() && healthLoad.size() < load) {
            //use splice to move the first element of healthPack to the end of healthLoad
            healthLoad.splice(healthLoad.end(), healthPack, healthPack.begin());
        }
        std::cout << "Health Resupply Success!" << std::endl;
    }
}

void tank::printBulletLoad() {//print the bullets in the bulletLoad
    if(bulletLoad.empty()){
        std::cout << "Error: No Bullet In Load!" << std::endl;
    }
    else {
        std::cout << "Bullet Pack Remains: ";
        for(auto i : bulletLoad){
            std::cout << i.GetBulletType() << " ";
        }
        std::cout << std::endl;
    }
}

void drawBlk(float x, float y, float width) {//draw black block, standard size 40, posX, posY is the center of the block
    float ratio = width/40;
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(x-4*ratio, y-2*ratio);
    glVertex2f(x+4*ratio, y-2*ratio);
    glVertex2f(x+4*ratio, y+2*ratio);
    glVertex2f(x-4*ratio, y+2*ratio);
    glEnd();
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

void drawBody(float x, float y, float width) {//draw tank body, standard size 40, posX, posY is the center of the tank
    float ratio = width/40;
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

void tank::draw(float width) {//draw tank according to its Type, standard size 40, posX, posY is the center of the tank
    float ratio = width/40;
    bulletShot.Draw(posX, posY, fireAngle);
    if(this->tankType == type1){
        //draw the tank wheel with red color
        glColor3ub(128, 30, 0);
        drawBody(posX, posY, width);
        //draw the wheel gap with black color
        for(int i= 0; i < 5; i++){
            drawBlk(posX-16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        for(int i= 0; i < 5; i++){
            drawBlk(posX+16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        //draw the tank head with red color
        glColor3ub(255, 30, 0);
        drawAim(posX, posY, width, fireAngle);
    } else if(this->tankType == type2){
        glColor3ub(30,128,0);
        drawBody(posX, posY, width);
        //draw the wheel gap with black color
        for(int i= 0; i < 5; i++){
            drawBlk(posX-16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        for(int i= 0; i < 5; i++){
            drawBlk(posX+16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        glColor3ub(30,255,0);
        drawAim(posX, posY, width, fireAngle);
    } else if(this->tankType == type3){
        glColor3ub(0,30,128);
        drawBody(posX, posY, width);
        //draw the wheel gap with black color
        for(int i= 0; i < 5; i++){
            drawBlk(posX-16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        for(int i= 0; i < 5; i++){
            drawBlk(posX+16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        glColor3ub(0,30,255);
        drawAim(posX, posY, width, fireAngle);
    } else if(this->tankType == type4){
        glColor3ub(128,128,0);
        drawBody(posX, posY, width);
        //draw the wheel gap with black color
        for(int i= 0; i < 5; i++){
            drawBlk(posX-16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        for(int i= 0; i < 5; i++){
            drawBlk(posX+16*ratio, posY-16*ratio+8*ratio*i, width);
        }
        glColor3ub(200,200,0);
        drawAim(posX, posY, width, fireAngle);
    }
    else {
        printf("Error: tank Type not found");
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
    if(key == FSKEY_J || key == FSKEY_5){//clockwise
        this->fireAngle -= stepAngle;
        wrap2pi(this->fireAngle);
    } else if (key == FSKEY_K || key == FSKEY_6){//counter-clockwise
        this->fireAngle += stepAngle;
        wrap2pi(this->fireAngle);
    }
}

void tank::checkFire(int key) {
    if(key == FSKEY_SPACE){
        if(!bulletShot.GetIsHit()){
            this->fire();
        }
        else {
            std::cout << "Error: Bullet Is Still Alive" << std::endl;
        }
    }
}

