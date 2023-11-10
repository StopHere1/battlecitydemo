#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"
/* begin of bottom class*/
class buttom
{
protected:
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    int state = 0;

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

buttom::buttom(float ix, float iy, float iwidth, float iheight)
{
    x = ix;
    y = iy;
    width = iwidth;
    height = iheight;
    state = 0;
}

bool buttom::isinsidebuttom(int mx, int my)
{
    return (mx >= x - width / 2.0f) && (mx <= x + width / 2.0f) && (my >= y - height / 2.0f) && (my <= x + height / 2.0f);
}
float buttom::getstate()
{
    return state;
}

float buttom::getx()
{
    return x;
}

float buttom::gety()
{
    return y;
}

float buttom::getheight()
{
    return height;
}

float buttom::getwidth()
{
    return width;
}

void buttom::setstate(int input)
{
    this->state = input;
}

void buttom::draw()
{
    glBegin(GL_QUADS);
    if (state == 0)
    {
        glColor3ub(120, 120, 120);
    }
    else
    {
        glColor3ub(230, 230, 230);
    }
    glVertex2f(x - width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y + height / 2.0f);
    glVertex2f(x - width / 2.0f, y + height / 2.0f);
    glEnd();
}

/* begin of menu class*/
class menu
{
public:
protected:
    int stage = 0;

public:
    menu();
    void test();
    void start();
    void run(std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2);
};
menu::menu()
{
    stage = 0;
}
void menu::test()
{
    std::cout << "hello world from menu!" << std::endl;
}

void menu::run(std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2)
{
    if (stage == 0)
    {
        for (;;)
        {
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                break;
            }
            int lb, mb, rb, mx, my;
            int mouseEvent;
            mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
            if (stage0[0].isinsidebuttom(mx, my))
            {
                stage0[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 1;
                    break;
                }
            }
            else
            {
                stage0[0].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            stage0[0].draw();
            glRasterPos2d(100,100);
            YsGlDrawFontBitmap8x12("ABCD");
            FsSwapBuffers();
            FsSleep(100);
        }
    }
    else if (stage == 1)
    {
    }
}

void menu::start()
{
    FsOpenWindow(0, 0, 1920, 1080, 1);
    buttom buttom1(200.0f, 200.0f, 100.0f, 100.0f);
    std::vector<buttom> stage0;
    std::vector<buttom> stage1;
    std::vector<buttom> stage2;
    stage0.push_back(buttom1);
    run(stage0, stage1, stage2);
}
