//
// Created by anthonyshen on 11/13/23.
//

#ifndef BATTLECITYDEMO_TANK_H
#define BATTLECITYDEMO_TANK_H


class tank {
protected:
    enum type {type1, type2, type3, type4};// tank type
    float posX; // position x of tank
    float posY; // position y of tank
    float armor; // armor of tank
    float weight; // weight of tank
    float health; // health of tank
    float load; // load of tank
    float power; // power of tank
    float speed; // speed of tank, related to load and power
    int state; // state of tank, 0 for alive, 1 for dead
public:
    tank() { posX = 0; posY = 0; armor = 0; health = 0; load = 0; speed = 0; power = 0; weight = 0; state = 0;};
    float getPosX();
    float getPosY();
    float getArmor();
    float getHealth();
    float getLoad();
    float getSpeed();
    float getPower();
    float getWeight();
    int getState();
    void setPosX(float input);
    void setPosY(float input);
    void setArmor(float input);
    void setHealth(float input);
    void setLoad(float input);
    void setSpeed(float input);
    void setPower(float input);
    void setWeight(float input);
    void setState(int input);

    int init(type type);
    void move(int key, int player);
//    void shoot();
//    void draw();//draw tank according to its type
    ~tank(){};
};


#endif //BATTLECITYDEMO_TANK_H
