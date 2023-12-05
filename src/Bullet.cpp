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
    count_rebound = 10;
}

void Bullet::Draw(double tankx, double tanky, double tankangle) {
    double currentx, currenty;
    if (this->IsShot == 1) {
        if (this->FirstShoot == 1) {
            this->Initialize(tankx, tanky, tankangle);
            if (this->BulletType == 0) {
                sound->playShootBullet1(); // shoot bullet type 0
            }
            else if (this->BulletType == 1) {
                sound->playShootBullet2(); // shoot bullet type 1
            }
            else if (this->BulletType == 2) {
                sound->playShootBullet3(); // shoot bullet type 2
            }
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
        // printf("collision case: %d", CollisionCase);
        switch (CollisionCase) {
            case 0:
                break;
            case 1:
                this->damage = DamageTankTable[this->BulletType];
                //sound effect for hit tank
                sound->playHitTank();
                this->IsShot = 0;
                this->IsHit = 1;
                break;
            case 2:
                if (this->MapDestructible == 1) {
                    this->damagemap = DamageMapTable[this->BulletType];
                    //sound effect for destroy map
                    sound->playHitWall();
                    this->IsHit = 1;
                    this->IsShot = 0;
                    break;
                }
                // else {
                //     if (this->reboundable == 1 && this->count_rebound != 0 && this->count_rebound_time == 0) {
                //         printf("rebound\n");
                //         printf("before vx: %f, vy: %f", this->vx, this->vy);
                //         // printf("angle before:%f",angle);
                //         //sound effect for rebound
                //         sound->playHitRebound();
                //         this->ReboundCase();
                //         printf("after vx: %f, vy: %f", this->vx, this->vy);
                //         // this->vx = -this->vx;
                //         // this->vy = -this->vy;
                //         // printf("angle after:%f",angle);
                //         this->CollisionCase = 0;
                //         this->MapDestructible = 0;
                //         this->CollideMap = 0;
                //         this->count_rebound -= 1;
                //         this->count_rebound_time = 0;
                //     }
                //     // else if(this->reboundable == 1 && this->count_rebound != 0 && this->count_rebound_time != 0){
                //     //     this->count_rebound_time -= 1;
                //     //     if (this->count_rebound_time<0){
                //     //         this->count_rebound_time=0;
                //     //     }
                //     // }
                    else {
                        //sound effect for destroy bullet
                        sound->playHitWall();
                        this->IsHit = 1;
                        this->IsShot = 0;
                    // }
                    break;
                }
            // case 3:
            //     if (this->MapDestructible == 1) {
            //         this->damagemap = DamageMapTable[this->BulletType];
            //         //sound effect for destroy map
            //         sound->playHitWall();
            //         this->IsHit = 1;
            //         this->IsShot = 0;
            //         break;
            //     }
            //     else {
            //         if (this->reboundable == 1 && this->count_rebound != 0) {
            //             //sound effect for rebound
            //             sound->playHitRebound();
            //             this->vy = - this->vy;
            //             CollisionCase = 0;
            //             MapDestructible = 0;
            //             CollideMapY = 0;
            //             count_rebound -= 1;
            //             break;
            //         }
            //         else {
            //             //sound effect for destroy bullet
            //             sound->playHitWall();
            //             this->IsHit = 1;
            //             this->IsShot = 0;
            //             break;
            //         }
            //     }
            // case 4:
            //     this->IsHit = 1;
        }
    }
    else if (this->IsHit == 1) {
        this->damage = 0;
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
    // if (this->IsHit == 1 && this->FirstHit) {
    return this->damage;
    // }
    // else {
    //     return 0;
    // }
}

int Bullet::GetDamageMap(void){
    return this->damagemap;
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

void Bullet::IsCollideMap(void) {
    this->CollideMap = 1;
}

// void Bullet::IsCollideMapX(void) {
//     this->CollideMapX = 1;
// }

// void Bullet::IsCollideMapY(void) {
//     this->CollideMapY = 1;
// }

void Bullet::IsCollideBullet(void) {
    this->CollideBullet = 1;
}

void Bullet::IsMapDestructible(void) {
    this->MapDestructible = 1;
}

bool Bullet::GetIsHit() {
    return this->IsHit;
}

void Bullet::setSoundPlayer(Sound *soundPlayer) {//setter
    this->sound = soundPlayer;
}

bool Bullet::CheckTankCollision(const double &tankx, const double &tanky) {
	double tankupperbound = tanky+20;
    double tanklowerbound = tanky-20;
    double tankleftbound = tankx -20;
    double tankrightbound = tankx + 20;

    if (this->x >= tankleftbound && this->x <= tankrightbound && this->y <= tankupperbound && this->y >= tanklowerbound){
        // printf("collision detected!");
	    return true;  // Collision detected
    }
    else{
        return false;
    }
}

// bool Bullet::CheckMapCollision(){

// }

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
    this->damagemap = 0;
    this->count_rebound = 10;
}

void Bullet::Initialize(void) {
    this->FirstShoot = 0;
    this->FirstHit = 1;
    // this->vx = VTable[this->BulletType] * cos(-this->angle);
    // this->vy = VTable[this->BulletType] * sin(-this->angle);
    // this->ax = AXTable[this->BulletType];
    // this->ay = AYTable[this->BulletType];
    this->xsize = XSize[this->BulletType];
    this->ysize = YSize[this->BulletType];
    this->reboundable = ReboundTable[this->BulletType];
    // this->x = x0;
    // this->y = y0;
    this->dt = 0.1;
    this->CollisionCase = 0;
    this->CollideTank = 0;
    this->CollideMap = 0;
    // this->CollideMapX = 0;
    // this->CollideMapY = 0;
    this->CollideBullet = 0;
    this->MapDestructible = 0;
    this->count = 0;
    this->damage = 0;
    this->damagemap = 0;
    this->count_rebound = 10;

}

void Bullet::Reset(void) {
    this->FirstShoot = 1;
    this->FirstHit = 1;
    this->IsShot = 0;
    this->IsHit = 0;
    this->count = 0;
    this->CollisionCase = 0;
    this->CollideTank = 0;
    this->CollideMap = 0;
    // this->CollideMapX = 0;
    // this->CollideMapY = 0;
    this->CollideBullet = 0;
    this->MapDestructible = 0;
    this->damage = 0;
    this->damagemap = 0;
    this->count_rebound = 10;
    this->x = -50;
    this->y = -50;
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
    
    // this->vx = VTable[this->BulletType] * cos(-this->angle);
    // this->vy = VTable[this->BulletType] * sin(-this->angle);
    this->x = this->x + this->vx * this->dt;
    this->y = this->y + this->vy * this->dt;

}

int Bullet::CheckCollision(void) {
    //CheckCollisionTank
    //CheckCollisionMap
    if (this->x >= 1000 || this->x <= 0||this->y >= 720 || this->y <= 0) {
        CollideMap = 1;
    }
    // else if () {
    //     CollideMapY = 1;
    // }
    if (CollideTank == 1) {
        return 1;
    }
    else if (CollideMap == 1) { 
        // this->CheckMapDestructible();
        return 2;
    }
    // else if (CollideMapY == 1) {
    //     this->CheckMapDestructible();
    //     return 3;
    // }
    // else if (CollideBullet == 1) {
    //     return 4;
    // }
    // else {
    //     return 0;
    // }
}

// void Bullet::CheckMapDestructible(void) {
//     //Map map;
//     //MapDestructible = map.CheckDestructible(this->x,this->y);
// }

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

void Bullet::ReboundCase(void){
 	double x2max = floor(this->x/40)*40+40;
    double x2min = floor(this->x/40)*40-40;    
    double y2max = floor(this->y/40)*40+40;
    double y2min = floor(this->y/40)*40-40;
    if (abs(this->x-x2max)<1 || abs(this->x-x2min)<1)
    {
        printf("xdir");
        this->vx = -this->vx;
    }
    else if (abs(this->y-y2max<1 ||abs(this->y-y2min)<1))
    {
        printf("ydir");
        this->vy = -this->vy;
    }
    else{
        printf("neither");
    }

    // if (abs(this->x-x2max)<1 || abs(this->x-x2min)<1)
    // {
    //     this->vy = -this->vy;
    // }
    // double y2 = floor(this->y/40)*40+20;
    // double dx = std::abs(this->x-x2);
    // double dy = std::abs(this->y-y2);
    // if (dx>dy){
    //     this->vx = -this->vx;
    // }
    // else if(dy>dx){
    //     this->vy = -this->vy;
    // }
    // else{
    //     this->vx = -this->vx;
    //     this->vy = -this->vy;
    // }
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


