//
// Created by anthonyshen on 11/13/23.
//

#ifndef BATTLECITYDEMO_TANK_H
#define BATTLECITYDEMO_TANK_H
#include <list>
#include "../include/Bullet.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"


class tank {
public:
    tank() { posX = 0; posY = 0; armor = 0; health = 0; load = 0; speed = 0; power = 0; weight = 0; state = 0; magSize = 0; std::list<Bullet> bulletMag; std::list<Bullet> bulletLoad ;};
    enum Type {type1, type2, type3, type4};// tank Type
    float getPosX();
    float getPosY();
    float getArmor();
    float getHealth();
    float getHealthMax();
    int getLoad();
    float getSpeed();
    float getPower();
    float getWeight();
    int getState();
    int getMagSize();
    float getFireAngle();
    void setPosX(float input);
    void setPosY(float input);
    void setArmor(float input);
    void setHealth(float input);
    void setHealthMax(float input);
    void setLoad(int input);
    void setSpeed(float input);
    void setPower(float input);
    void setWeight(float input);
    void setState(int input);
    void setMagSize(int input);
    void setFireAngle(float input);

    int init(Type type);
    void move(int key);
    void singleReload();
    void reload();
    void fire();
    void checkFire(int key);
    // void checkLoad();
    void printBulletMag();
    void printBulletLoad();
    // void heal();//heal tank
    void pickUpBullet(std::list<Bullet> bulletPack);//pick up bullet package
    // void pickUpHealth(std::list<Tool> healthPack);//pick up health package
    void draw(float size);//draw tank according to its Type and size, location is determined by posX and posY
    void rotate(int key);//rotate tank aiming direction

    Type getTankType() const { return tankType; }
    void setTankType(Type type) { tankType = type; }

    ~tank()= default;
protected:
    float posX; // position x of tank
    float posY; // position y of tank
    float armor; // armor of tank
    float weight; // weight of tank
    float health; // health of tank
    float healthMax; // max health of tank
    int load; // load of tank, count of the bullet package and health package
    int magSize; // size of ammo mag
    float power; // power of tank
    float speed; // speed of tank, related to load and power
    int state; // state of tank, 0 for alive, 1 for dead
    float fireAngle; // angle of tank aiming direction
    Type tankType;
    std::list<Bullet> bulletMag; // list for ammo mag
//    std::list<Bullet> bulletShot; // list for storing bullet shot
    Bullet bulletShot; // bullet shot only one at a time
    std::list<Bullet> bulletLoad; // list for storing bullet packages
    // std::list<Tool> healthLoad; // list for storing health packages
};


#endif //BATTLECITYDEMO_TANK_H
