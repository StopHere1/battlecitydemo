#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "menu.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

int main(){
    std::cout<<"hello world"<<std::endl;
    menu menu;
    menu.start();
}