#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "../fssimplewindow_src/fssimplewindow.h"
class menu{
    public:
    protected:

    public:
    void test();
    void openwindow();
};

void menu::test(){
    std::cout<<"hello world from menu!"<<std::endl;
}

void menu::openwindow(){
    FsOpenWindow(0,0,1920,1080,1);
    for(;;){
        FsPollDevice();
        auto key = FsInkey();
        if(key == FSKEY_ESC){
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        FsSwapBuffers();
        FsSleep(100);
    }
}