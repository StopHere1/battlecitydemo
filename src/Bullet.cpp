#define GL_SILENCE_DEPRECATION
#include "../include/Bullet.h"

Bullet::Bullet(double x, double y, double angle) {
    this->Initialize(x, y, angle);
    this->FirstShoot = 1;
}

Bullet::Bullet(double x, double y, double angle, int type) {
    this->Initialize(x, y, angle);
    if (type <= 0) {
        this->BulletType = 0;
    }
    else if (type >= 2) {
        this->BulletType = 2;
    }
    else {
        this->BulletType = type;
    }
    this->FirstShoot = 1;
}

Bullet::Bullet(int type) {
    this->Initialize();
    if (type <= 0) {
        this->BulletType = 0;
    }
    else if (type >= 2) {
        this->BulletType = 2;
    }
    else {
        this->BulletType = type;
    }
    this->FirstShoot = 1;
}

Bullet::Bullet(void) {
    this->Initialize();
    this->FirstShoot = 1;
    this->BulletType = 0;
}

Bullet::~Bullet() {
    this->Reset();
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    count = 0;
}

void Bullet::Draw(double tankx, double tanky, double tankangle) {
    double currentx, currenty;
    if (this->IsShot == 1) {
        if (this->FirstShoot == 1) {
            this->Initialize(tankx, tanky, tankangle);
        }
        this->Motion();
        if (this->BulletType == 2) {
            double a, b, theta;
            glColor3ub(0, 0, 0);
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < 64; ++i) {
                theta = 2.0f * PI * i / 64;
                a = this->ysize * cos(theta);
                b = this->xsize * sin(theta);
                glVertex2d(this->x + b, this->y + a);
            }
            glEnd();
        }
        else {
            glColor3ub(0, 0, 0);
            glBegin(GL_QUADS);
            currentx = this->xsize / 2.0;
            currenty = this->ysize / 2.0;
            Rotate(currentx, currenty, -this->angle);
            glVertex2d(currentx + this->x, currenty + this->y);
            currentx = - this->xsize / 2.0;
            currenty = this->ysize / 2.0;
            Rotate(currentx, currenty, -this->angle);
            glVertex2d(currentx + this->x, currenty + this->y);
            currentx = - this->xsize / 2.0;
            currenty = - this->ysize / 2.0;
            Rotate(currentx, currenty, -this->angle);
            glVertex2d(currentx + this->x, currenty + this->y);
            currentx = + this->xsize / 2.0;
            currenty = - this->ysize / 2.0;
            Rotate(currentx, currenty, -this->angle);
            glVertex2d(currentx + this->x, currenty + this->y);
            glEnd();
        }

        int CollisionCase = this->CheckCollision();
        switch (CollisionCase) {
            case 0:
                break;
            case 1:
                this->damage = DamageTankTable[this->BulletType];
                //sound effect for hit tank
                this->IsShot = 0;
                this->IsHit = 1;
                break;
            case 2:
                if (this->MapDestructible == 1) {
                    this->damage = DamageMapTable[this->BulletType];
                    //sound effect for destroy map
                    this->IsHit = 1;
                    this->IsShot = 0;
                    break;
                }
                else {
                    if (this->reboundable == 1) {
                        //sound effect for rebound
                        this->vx = - this->vx;
                        CollisionCase = 0;
                        MapDestructible = 0;
                        CollideMapX = 0;
                    }
                    else {
                        //sound effect for destroy bullet
                        this->IsHit = 1;
                        this->IsShot = 0;
                    }
                    break;
                }
            case 3:
                if (this->MapDestructible == 1) {
                    this->damage = DamageMapTable[this->BulletType];
                    //sound effect for destroy map
                    this->IsHit = 1;
                    this->IsShot = 0;
                    break;
                }
                else {
                    if (this->reboundable == 1) {
                        //sound effect for rebound
                        this->vy = - this->vy;
                        CollisionCase = 0;
                        MapDestructible = 0;
                        CollideMapY = 0;
                        break;
                    }
                    else {
                        //sound effect for destroy bullet
                        this->IsHit = 1;
                        this->IsShot = 0;
                        break;
                    }
                }
            case 4:
                this->IsHit = 1;
        }
    }
    else if (this->IsHit == 1) {
        if (this->count < 20) {
            this->Hit();
            this->count += 1;
        }
        else {
            this->IsHit = 0;
        }
        this->FirstHit = 0;
    }
    else {
        this->Reset();
    }
}

double Bullet::GetBulletX(void) {
    return this->x;
}

double Bullet::GetBulletY(void) {
    return this->y;
}

bool Bullet::GetBulletStatus(void) {
    return this->IsShot;
}

double Bullet::GetDamage(void) {
    if (this->IsHit == 1 && this->FirstHit) {
        return this->damage;
    }
    else {
        return 0;
    }
}

void Bullet::ChangeBulletType(int type) {//Make a Change
    if (this->IsShot == 0) {
        this->BulletType = type;
        if (type > 2 || type<0) {
            printf("BulletType Error!\n");
        }
    }
}

int Bullet::GetBulletType(void) {
    return this->BulletType;
}

void Bullet::IsCollideTank(void) {
    this->CollideTank = 1;
}

void Bullet::IsCollideMapX(void) {
    this->CollideMapX = 1;
}

void Bullet::IsCollideMapY(void) {
    this->CollideMapY = 1;
}

void Bullet::IsCollideBullet(void) {
    this->CollideBullet = 1;
}

void Bullet::IsMapDestructible(void) {
    this->MapDestructible = 1;
}

bool Bullet::GetIsHit() {
    return this->IsHit;
}

//Protected
void Bullet::Initialize(double tankx, double tanky, double tankangle) {
    this->FirstShoot = 0;
    this->FirstHit = 1;
    this->angle = tankangle;
    this->vx = VTable[this->BulletType] * cos(-this->angle);
    this->vy = VTable[this->BulletType] * sin(-this->angle);
    this->ax = AXTable[this->BulletType];
    this->ay = AYTable[this->BulletType];
    this->xsize = XSize[this->BulletType];
    this->ysize = YSize[this->BulletType];
    this->reboundable = ReboundTable[this->BulletType];
    this->x0 = tankx;
    this->y0 = tanky;
    this->x = x0;
    this->y = y0;
    this->dt = 0.1;
    this->CollisionCase = 0;
    this->CollideTank = 0;
    this->CollideMapX = 0;
    this->CollideMapY = 0;
    this->CollideBullet = 0;
    this->MapDestructible = 0;
    this->count = 0;
    this->damage = 0;
}

void Bullet::Initialize(void) {
    this->FirstShoot = 0;
    this->FirstHit = 1;
    this->vx = VTable[this->BulletType] * cos(-this->angle);
    this->vy = VTable[this->BulletType] * sin(-this->angle);
    this->ax = AXTable[this->BulletType];
    this->ay = AYTable[this->BulletType];
    this->xsize = XSize[this->BulletType];
    this->ysize = YSize[this->BulletType];
    this->reboundable = ReboundTable[this->BulletType];
    this->x = x0;
    this->y = y0;
    this->dt = 0.1;
    this->CollisionCase = 0;
    this->CollideTank = 0;
    this->CollideMapX = 0;
    this->CollideMapY = 0;
    this->CollideBullet = 0;
    this->MapDestructible = 0;
    this->count = 0;
    this->damage = 0;

}

void Bullet::Reset(void) {
    this->FirstShoot = 1;
    this->FirstHit = 1;
    this->IsShot = 0;
    this->IsHit = 0;
    this->count = 0;
    this->CollisionCase = 0;
    this->CollideTank = 0;
    this->CollideMapX = 0;
    this->CollideMapY = 0;
    this->CollideBullet = 0;
    this->MapDestructible = 0;
    this->damage = 0;
}

void Bullet::ShootBullet(void) {
    if (this->IsShot == 1) {
        //sound effect cannot shoot
    }
    else {
        this->IsShot = 1;
    }
}

void Bullet::Motion(void) {
    this->x = this->x + this->vx * this->dt;
    this->y = this->y + this->vy * this->dt;
    this->vx += this->ax * this->dt;
    this->vy += this->ay * this->dt;
}

int Bullet::CheckCollision(void) {
    //CheckCollisionTank
    //CheckCollisionMap
    if (this->x >= 1280 || this->x <= 0) {
        CollideMapX = 1;
    }
    else if (this->y >= 720 || this->y <= 0) {
        CollideMapY = 1;
    }
    if (CollideTank == 1) {
        return 1;
    }
    else if (CollideMapX == 1) {
        this->CheckMapDestructible();
        return 2;
    }
    else if (CollideMapY == 1) {
        this->CheckMapDestructible();
        return 3;
    }
    else if (CollideBullet == 1) {
        return 4;
    }
    else {
        return 0;
    }
}

void Bullet::CheckMapDestructible(void) {
    //Map map;
    //MapDestructible = map.CheckDestructible(this->x,this->y);
}

void Bullet::Hit(void) {
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3ub(255, 0, 0);
    double xr, yr;
    for (int i = 0; i < 5; i++) {
        int d = ysize * 20;
        double r = rand() % d;
        r = r / 10.0;
        double theta = rand() % 10;
        theta = 2 * PI / 10.0 * theta;
        xr = r * cos(theta);
        yr = r * sin(theta);
        glVertex2d(this->x + xr, this->y + yr);
    }
    glEnd();
}

void Bullet::Rotate(double& x, double& y, double theta) {
    double newx, newy;
    newx = cos(theta) * x - sin(theta) * y;
    newy = sin(theta) * x + cos(theta) * y;
    x = newx;
    y = newy;
}

bool Bullet::GetIsShot() {//add
    return this->IsShot;
}

void Bullet::setSoundPlayer(Sound *soundPlayer) {//setter
    this->soundPlayer = soundPlayer;
}


