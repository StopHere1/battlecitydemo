#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "menu.h"
#include "../fssimplewindow_src/fssimplewindow.h"

int main(){
    std::cout<<"hello world"<<std::endl;
    menu menu;
    menu.test();
    menu.openwindow();
}