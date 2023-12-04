#ifndef MENU_23341234124341
#define MENU_23341234124341
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "../include/sound.h"
#include "../include/Bullet.h"
#include "../include/tank.h"
#include "../include/map.h"
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

std::vector <std::string> Parse(std::string incoming);
class UserInfoManager{
    protected:
        std::vector<std::string> username;
        std::vector<std::string> password;
        int nUser = 0;
    public:
        std::vector<std::string> getUsername();
        std::vector<std::string> getPassword();
        UserInfoManager(std::string fileName);
        int getNumUser();
        void update();
};
class TextString
{
protected:
	char *str;

public:
	TextString();
	TextString(const TextString &incoming);
	TextString &operator=(const TextString &incoming);
	void CopyFrom(const TextString &incoming);
	TextString(const char incoming[]);
	TextString &operator=(const char incoming[]);
	void set(const char incoming[]);
	~TextString();
	void clear(void);
	void push_back(char c);
    void pop_back(void);
	const char *c_str(void) const;
	size_t size(void) const;
};
void Print(const TextString &str);
class TextInput
{
protected:
	TextString title;
	TextString str;

public:
	TextString GetString(void);
    TextString GetTitle();
	void SetTitle(const char title[]);
	void RunOneStep(int fskey,char c);
	void Draw(void) const;
};

class vector2f {
protected:
   float x ;
   float y ;
public:
    vector2f(float x, float y);
    bool checkColinearity(vector2f a);
    float getx();
    float gety();
    float getLen();
    float dot(vector2f input);
};

class polygon{
    protected:
        vector2f center;
        std::vector<vector2f> vertex;
    public:
        virtual bool checkCollision(polygon target);
};

class buttom{
    protected:
        float x ;
        float y ;
        float width ;
        float height ;
        int state ;
        char* title;
    public:
        buttom(float x, float y, float width, float height, char* title);
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
    void bulletTankCollision(Bullet &tank1Bullet, Bullet &tank2Bullet, tank &testTank1, tank &testTank2);
    void bulletMapCollision(Bullet &tank1Bullet, Bullet &tank2Bullet, Map &map);
    void drawBackground(YsRawPngDecoder &background);
    void setstage(int input);
    void run(Sound &soundplayer, UserInfoManager &manager, std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2, std::vector<buttom> &stage3,std::vector<buttom> &stage4,std::vector<buttom> &stage5,std::vector<buttom> &stage6,std::vector<buttom> &stage7, YsRawPngDecoder &background);
};

#endif