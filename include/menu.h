#ifndef MENU_23341234124341
#define MENU_23341234124341
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

class buttom{
    protected:
        float x ;
        float y ;
        float width ;
        float height ;
        int state ;
    public:
        buttom(float x, float y, float width, float height);
        float getstate();
        float getx();
        float gety();
        float getwidth();
        float getheight();
        void setstate(int input);
        void draw();
        bool isinsidebuttom(int mx, int my);
};

class menu{
    public:
    protected:
        int stage;
    public:
    menu();
    void test();
    void start();
    void run(std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2);
};

#endif