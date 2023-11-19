#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <string.h>
#include <cmath>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

class vector2f {
protected:
   float x = 0;
   float y = 0;
public:
    vector2f(float x, float y);
    bool checkColinearity(vector2f a);
    float getx(){
        return x;
    }
    float gety(){
        return y;
    }
    float getLen(){
        return sqrt(x*x+y*y);
    }
    float dot(vector2f input){
        return this->x*input.x+this->y*input.y;
    }
    
};

vector2f::vector2f(float x, float y){
    this->x = x;
    this->y = y;
}
bool vector2f::checkColinearity(vector2f a){
    if(a.x/this->x == a.y/this->y){
        return true;
    }else if(a.x/this->x == -a.y/this->y){
        return true;
    }
    return false;
}

class polygon{
    protected:
        vector2f center = vector2f(0.0f,0.0f);
        std::vector<vector2f> vertex;
    public:
        virtual bool checkCollision(polygon target);

};

bool polygon::checkCollision(polygon target){
    std::vector<vector2f> axis;
    for(size_t index = 0; index < target.vertex.size(); ++index){
        if(axis.size()==0){
            axis.push_back(vector2f(vertex[(index+1)%target.vertex.size()].getx()-target.vertex[index].getx(),vertex[(index+1)%target.vertex.size()].gety()-target.vertex[index].gety()));
        }
        else{
            bool flag = false;
            for (size_t i = 0; i < axis.size(); i++)
            {
                if(vector2f(vertex[(index+1)%target.vertex.size()].getx()-target.vertex[index].getx(),vertex[(index+1)%target.vertex.size()].gety()-target.vertex[index].gety()).checkColinearity(axis[i])){
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                axis.push_back(vector2f(vertex[(index+1)%target.vertex.size()].getx()-target.vertex[index].getx(),vertex[(index+1)%target.vertex.size()].gety()-target.vertex[index].gety()));
            }
            
        }
        
    }
    for(size_t index = 0; index < this->vertex.size(); ++index){
        if(axis.size()==0){
            axis.push_back(vector2f(vertex[(index+1)%this->vertex.size()].getx()-this->vertex[index].getx(),vertex[(index+1)%target.vertex.size()].gety()-this->vertex[index].gety()));
        }
        else{
            bool flag = false;
            for (size_t i = 0; i < axis.size(); i++)
            {
                if(vector2f(vertex[(index+1)%this->vertex.size()].getx()-this->vertex[index].getx(),vertex[(index+1)%this->vertex.size()].gety()-this->vertex[index].gety()).checkColinearity(axis[i])){
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                axis.push_back(vector2f(vertex[(index+1)%this->vertex.size()].getx()-this->vertex[index].getx(),vertex[(index+1)%this->vertex.size()].gety()-this->vertex[index].gety()));
            }
        }
    }
    for(size_t idx = 0; idx <= axis.size(); ++idx){
        float targetMin = INFINITY;
        float targetMax = -INFINITY;
        for(size_t index = 0; index < target.vertex.size(); ++index){
            if(targetMin > target.vertex[index].dot(axis[idx])/axis[idx].getLen()){
                targetMin = target.vertex[index].dot(axis[idx])/axis[idx].getLen();
            }else if(targetMax < target.vertex[index].dot(axis[idx])/axis[idx].getLen()){
                targetMax = target.vertex[index].dot(axis[idx])/axis[idx].getLen();
            }
        }
        float thisMin = INFINITY;
        float thisMax = -INFINITY;
        for(size_t index = 0; index < this->vertex.size(); ++index){
            if(thisMin > this->vertex[index].dot(axis[idx])/axis[idx].getLen()){
                thisMin = this->vertex[index].dot(axis[idx])/axis[idx].getLen();
            }else if(thisMax < this->vertex[index].dot(axis[idx])/axis[idx].getLen()){
                thisMax = this->vertex[index].dot(axis[idx])/axis[idx].getLen();
            }
        }
        if(targetMax<thisMin||thisMax<targetMin){
            return false;
        }
    }
    return true;
}

/* begin of bottom class*/
class buttom
{
protected:
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    int state = 0;
    char *title = nullptr;

public:
    buttom(float x, float y, float width, float height, char *title);
    float getstate();
    float getx();
    float gety();
    float getwidth();
    float getheight();
    void setstate(int input);
    void draw();
    bool isinsidebuttom(int mx, int my);
};

buttom::buttom(float ix, float iy, float iwidth, float iheight, char *title)
{
    x = ix;
    y = iy;
    width = iwidth;
    height = iheight;
    state = 0;
    this->title = title;
}

bool buttom::isinsidebuttom(int mx, int my)
{
    return (mx >= x - width / 2.0f) && (mx <= x + width / 2.0f) && (my >= y - height / 2.0f) && (my <= y + height / 2.0f);
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
    glColor3ub(120,0,0);
    glVertex2f(x - width / 2.0f-10.0f, y - height / 2.0f-10.0f);
    glVertex2f(x + width / 2.0f+10.0f, y - height / 2.0f-10.0f);
    glVertex2f(x + width / 2.0f+10.0f, y + height / 2.0f+10.0f);
    glVertex2f(x - width / 2.0f-10.0f, y + height / 2.0f+10.0f);
    glEnd();

    glBegin(GL_QUADS);
    if (state == 0)
    {
        glColor3ub(230, 120, 120);
    }
    else
    {
        glColor3ub(120, 20, 20);
    }
    glVertex2f(x - width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y + height / 2.0f);
    glVertex2f(x - width / 2.0f, y + height / 2.0f);
    glEnd();
    
    glColor3ub(0, 0, 0);
    glRasterPos2f(x - 8.0f*(float)(strlen(title)/2), y + 6.0f);
    YsGlDrawFontBitmap8x12(title);
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
    void drawBackground(YsRawPngDecoder &background);
    void setstage(int input);
    void run(std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2,
     std::vector<buttom> &stage3,std::vector<buttom> &stage4,std::vector<buttom> &stage5, YsRawPngDecoder &background);
};
menu::menu()
{
    stage = 0;
}
void menu::test()
{
    std::cout << "hello world from menu!" << std::endl;
}
void menu::drawBackground(YsRawPngDecoder &background){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glRasterPos2f(0.1f,719.0f);
    glDrawPixels(background.wid,background.hei,GL_RGBA,GL_UNSIGNED_BYTE,background.rgba);
    glDisable(GL_BLEND);
}
void menu::setstage(int input){
    stage = input;
}
/*
stages:
stage0: home menu
stage1: game mode selection
stage2: setting
stage3: deathbattle
stage4: occupation
stage5: timelimited occupation
*/
void menu::run(std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2, std::vector<buttom> &stage3,std::vector<buttom> &stage4,std::vector<buttom> &stage5, YsRawPngDecoder &background)
{
    if (stage == 0)
    {
        for (;;)
        {
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                stage = -1;
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

            if (stage0[1].isinsidebuttom(mx, my))
            {
                stage0[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 2;
                    break;
                }
            }
            else
            {
                stage0[1].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage0.size(); i++)
            {
                stage0[i].draw();
            }
            FsSwapBuffers();
        }
    }
    else if (stage == 1)
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

            if (stage1[0].isinsidebuttom(mx, my))
            {
                stage1[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 3;
                    break;
                }
            }
            else
            {
                stage1[0].setstate(0);
            }

            if (stage1[1].isinsidebuttom(mx, my))
            {
                stage1[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 4;
                    break;
                }
            }
            else
            {
                stage1[1].setstate(0);
            }
            if (stage1[2].isinsidebuttom(mx, my))
            {
                stage1[2].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 5;
                    break;
                }
            }
            else
            {
                stage1[2].setstate(0);
            }

            if (stage1[3].isinsidebuttom(mx, my))
            {
                stage1[3].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 0;
                    break;
                }
            }
            else
            {
                stage1[3].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage1.size(); i++)
            {
                stage1[i].draw();
            }
            FsSwapBuffers();
        }
    }
    else if (stage == 2)
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

            if (stage2[0].isinsidebuttom(mx, my))
            {
                stage2[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /*  increase the volumn */

                }
            }
            else
            {
                stage2[0].setstate(0);
            }

            if (stage2[1].isinsidebuttom(mx, my))
            {
                stage2[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /*  decrease the volumn */
                }
            }
            else
            {
                stage2[1].setstate(0);
            }

            if (stage2[2].isinsidebuttom(mx, my))
            {
                stage2[2].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                   /*set winning condition*/
                }
            }
            else
            {
                stage2[2].setstate(0);
            }

            if (stage2[3].isinsidebuttom(mx, my))
            {
                stage2[3].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 0;
                    break;
                }
            }
            else
            {
                stage2[3].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage2.size(); i++)
            {
                stage2[i].draw();
            }
            FsSwapBuffers();
        }
    }else if(stage == 3){
        for (;;)
        {
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                stage = -1;
                break;
            }
            int lb, mb, rb, mx, my;
            int mouseEvent;
            mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

            if (stage3[0].isinsidebuttom(mx, my))
            {
                stage3[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 1;
                    break;
                }
            }
            else
            {
                stage3[0].setstate(0);
            }

            if (stage3[1].isinsidebuttom(mx, my))
            {
                stage3[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /* pause */
                }
            }
            else
            {
                stage3[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < stage3.size(); i++)
            {
                stage3[i].draw();
            }
            FsSwapBuffers();
        }
    }else if(stage == 4){
        for (;;)
        {
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                stage = -1;
                break;
            }
            int lb, mb, rb, mx, my;
            int mouseEvent;
            mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

            if (stage4[0].isinsidebuttom(mx, my))
            {
                stage4[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 1;
                    break;
                }
            }
            else
            {
                stage4[0].setstate(0);
            }

            if (stage4[1].isinsidebuttom(mx, my))
            {
                stage4[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /* pause */
                }
            }
            else
            {
                stage4[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < stage4.size(); i++)
            {
                stage4[i].draw();
            }
            FsSwapBuffers();
        }
    }else if(stage == 5){
        for (;;)
        {
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                stage = -1;
                break;
            }
            int lb, mb, rb, mx, my;
            int mouseEvent;
            mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

            if (stage5[0].isinsidebuttom(mx, my))
            {
                stage5[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 1;
                    break;
                }
            }
            else
            {
                stage5[0].setstate(0);
            }

            if (stage5[1].isinsidebuttom(mx, my))
            {
                stage5[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /* pause */
                }
            }
            else
            {
                stage5[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < stage5.size(); i++)
            {
                stage5[i].draw();
            }
            FsSwapBuffers();
        }
    }
}

void menu::start() 
{
    FsOpenWindow(0, 0, 1280, 720, 1);

    /* loading files */
    FsChangeToProgramDir();
    YsRawPngDecoder background;
    if(YSOK!=background.Decode("../src/background.png"))
    {
        std::cout << "PNG load error." << std::endl;
    }
    background.Flip();
    
    /* initialization */
    std::vector<buttom> stage0;
    buttom buttom1(640.0f, 400.0f, 150.0f, 50.0f, " START ");
    buttom buttom2(640.0f, 500.0f, 150.0f, 50.0f, "SETTING");
    stage0.push_back(buttom1);
    stage0.push_back(buttom2);
    std::vector<buttom> stage1;
    buttom buttom3(640.0f, 400.0f, 150.0f, 50.0f, "DEATHBATTLE");
    buttom buttom4(640.0f, 500.0f, 150.0f, 50.0f, "OCCUPATION");
    buttom buttom5(640.0f, 600.0f, 150.0f, 50.0f, "TIMELIMITED");
    buttom buttom6(50.0f, 50.0f, 50.0f, 50.0f, "BACK");
    stage1.push_back(buttom3);
    stage1.push_back(buttom4);
    stage1.push_back(buttom5);
    stage1.push_back(buttom6);
    std::vector<buttom> stage2;
    buttom buttom7(540.0f, 400.0f, 150.0f, 50.0f, "VOLUME UP");
    buttom buttom8(740.0f, 400.0f, 150.0f, 50.0f, "VOLUMEDOWN");
    buttom buttom9(640.0f, 500.0f, 250.0f, 50.0f, "WINNING CONDITION");
    buttom buttom10(50.0f, 50.0f, 50.0f, 50.0f, "BACK");
    stage2.push_back(buttom7);
    stage2.push_back(buttom8);
    stage2.push_back(buttom9);
    stage2.push_back(buttom10);
    std::vector<buttom> stage3;
    buttom buttom11(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom12(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage3.push_back(buttom11);
    stage3.push_back(buttom12);
    std::vector<buttom> stage4;
    buttom buttom13(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom14(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage4.push_back(buttom13);
    stage4.push_back(buttom14);
    std::vector<buttom> stage5;
    buttom buttom15(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom16(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage5.push_back(buttom15);
    stage5.push_back(buttom16);
    std::cout<<"Game Initialized"<<std::endl;

    /* main game loop*/
    for (;;)
    {
        run(stage0, stage1, stage2, stage3, stage4, stage5, background);
        FsPollDevice();
        auto key = FsInkey();
        if (key == FSKEY_ESC)
        {
            break;
        }
    }
}
