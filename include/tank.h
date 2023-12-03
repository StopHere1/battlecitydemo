//
// Created by anthonyshen on 11/13/23.
//

#ifndef TANK_H
#define TANK_H
#include <list>
#include "../include/Bullet.h"
#include "../include/sound.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"


class tank {
public:
    tank() { posX = 0; posY = 0; armor = 0; health = 0; load = 0; speed = 0; power = 0;
        weight = 0; state = 0; magSize = 0; fireAngle = 0; direction =0 ;healthMax = 100; tankType = type1; user = 0; currentBulletType = 0;}
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
    int getDirection();
    float getFireAngle();
    int getUser();
    std::vector<int> getBulletCount();
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
    void setDirection(int input);
    void setUser(int input);
    void setSoundPlayer(Sound *soundplayer);

    int init(Type type, int user);
    void move(int key);
    void singleReload(int key);
    void reload(int key);
    void fire();
    void checkFire(int key);
//    void checkLoad();
    void printBulletMag();
    void printBulletLoad();
//    void heal();//heal tank
    void pickUpBullet(std::list<Bullet> bulletPack);//pick up bullet package
//    void pickUpHealth(std::list<Tool> healthPack);//pick up health package
    void draw(float size);//draw tank according to its Type and size, location is determined by posX and posY
    void rotate(int key);//rotate tank aiming direction
    void newFire(int key);//fire a new bullet
    void checkBulletCount();//check the count of each type of bullet
    void changeFireBullet(int key);//change the type of bullet to fire
    void newPickUpBullet(std::vector<int> bulletPack);//pick up bullet package
    void passSoundPlayer();//pass the sound player to the bullet
    bool checkTankHealth();//check if the tank is dead

    Type getTankType() const { return tankType; }
    void setTankType(Type type) { tankType = type; }
    Bullet* getBullet(){return &tankBullet;}

    ~tank()= default;
protected:
    int user; //0 for player 1, 1 for player2
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
    int direction; // direction of tank, 0 for vertical, 1 for horizontal
    float fireAngle; // angle of tank aiming direction
    Type tankType;
    std::list<Bullet> bulletMag; // list for ammo mag
//    std::list<Bullet> bulletShot; // list for storing bullet shot
    Bullet bulletShot; // bullet shot only one at a time
    std::list<Bullet> bulletLoad; // list for storing bullet packages
//    std::list<Tool> healthLoad; // list for storing health packages
    Bullet tankBullet = Bullet(0); // bullet for tank
    std::vector<int> BulletCount = {5, 5, 5}; // count of each type of bullet
    int currentBulletType = 0; // current bullet type
    Sound *soundPlayer;
};


#endif //TANK_H
