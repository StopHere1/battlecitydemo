#ifndef BATTLECITYDEMO_BULLET_H
#define BATTLECITYDEMO_BULLET_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../include/sound.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"
#include "../../battlecitydemo/include/sound.h"

const double PI = 3.1415926;
const double DamageTankTable[3] = { 30,10,10 };
const int DamageMapTable[3] = { 1,1,0 };
const double VTable[3] = { 40, 120, 80 };
const double AXTable[3] = { 0 };
const double AYTable[3] = { 0 };
const int ReboundTable[3] = { 0, 0, 1 };
const double XSize[3] = { 5,10,3 };
const double YSize[3] = { 5,2,3 };

//bullet type 1(square): low speed, high damage, can damge map, cannot rebound
//bullet type 2(rectangle): high speed, low damage, can damage map, cannot rebound
//bullet type 3(circle): medium speed, medium damage, cannot damage map, can rebound

class Bullet {
private:
    bool FirstShoot = 1;
    bool FirstHit = 1;
    double vx, vy;
    double ax, ay;
    double dt;
    bool reboundable;
    int count;
    int CollisionCase = 0;
    Sound *sound;//SHY: pointer to the sound player
    int count_rebound = 10;
    int count_rebound_time = 0;

protected:
    double x, y;//bullet position
    double x0, y0;//bullet initial position
    double damage;
    double damagemap;
    double xsize, ysize;//bullet size
    float angle;
    int BulletType = 0;
    bool IsShot = 0, IsHit = 0;
    bool CollideBullet, CollideTank, CollideMap, CollideMapX, CollideMapY, MapDestructible;

    void Rotate(double& x, double& y, double theta);
    void Initialize(double tankx, double tanky, double tankangle);
    void Initialize(void);
    void Reset(void);
    void Motion(void);
    int CheckCollision(void);
    void CheckMapDestructible(void);
    void Hit(void);

public:
    Bullet(double x, double y, double angle);
    Bullet(double x, double y, double angle, int type);
    explicit Bullet(int type);
    Bullet();
    ~Bullet();
    void Draw(double tankx, double tanky, double tankangle);
    double GetBulletX(void);
    double GetBulletY(void);
    bool GetBulletStatus(void);
    double GetDamage(void);
    int GetDamageMap(void);
    bool GetIsHit();
    bool GetIsShot();
    void ChangeBulletType(int type);
    int GetBulletType(void);
    void IsCollideTank(void);
    void IsCollideMap(void);
    void ReboundCase(void);
    // void IsCollideMapX(void);
    // void IsCollideMapY(void);
    void ShootBullet(void);
    void IsCollideBullet(void);
    void IsMapDestructible(void);
    void setSoundPlayer(Sound *s);
    bool CheckTankCollision(const double &tankx, const double &tanky);
};

#endif //BATTLECITYDEMO_BULLET_H
