#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <string.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <fstream>
#include "../../public/src/fssimplewindow/src/fssimplewindow.h"
#include "../../public/src/ysbitmapfont/src/ysglfontdata.h"
#include "../../public/src/ysbitmap/src/yspng.h"
#include "../../public/src/yssimplesound/src/yssimplesound.h"

std::vector <std::string> Parse(std::string incoming)
{
	int state=0;
	std::vector <std::string> words;
	std::string currentWord;
	for(auto c : incoming)
	{
		if(0==state)
		{
			if(' '!=c && '\n'!=c && '\t'!=c && '\r'!=c)
			{
				state=1;
				currentWord.push_back(c);
			}
		}
		else
		{
			if(' '!=c && '\n'!=c && '\t'!=c && '\r'!=c)
			{
				currentWord.push_back(c);
			}
			else
			{
				state=0;
				words.push_back(currentWord);
				currentWord="";
			}
		}
	}
	if(0!=state)
	{
		words.push_back(currentWord);
	}
	return words;
}

class UserInfoManager{
    protected:
        std::vector<std::string> username;
        std::vector<std::string> password;
        std::string filepath="";
        int nUser = 0;
    public:
        std::vector<std::string> getUsername(){
            return username;
        }
        std::vector<std::string> getPassword(){
            return password;
        }
        void update(){
            username.clear();
            password.clear();
            nUser = 0;
            std::ifstream ifp(filepath);
            if(true==ifp.is_open())
            {
                std::string str;
                std::getline(ifp,str);
                nUser = atoi(str.c_str());
                int nUserRead=0;
                while(true!=ifp.eof() && nUserRead<nUser)
                {
                    std::getline(ifp,str);
                    auto words=Parse(str);
                    if(2<=words.size())
                    {
                        username.push_back(words[0]);
                        password.push_back(words[1]);
                        ++nUserRead;
                    }
                }
		}
        }
        int getNumUser(){
            return nUser;
        }
        UserInfoManager(std::string fileName){
            this->filepath = fileName;
            this->update();
        }

};
class TextString
{
protected:
	char *str=nullptr;

public:
	TextString()
	{
	}
	TextString(const TextString &incoming)
	{
		CopyFrom(incoming);
	}
	TextString &operator=(const TextString &incoming)
	{
		CopyFrom(incoming);
		return *this;
	}
	void CopyFrom(const TextString &incoming)
	{
		if(this!=&incoming)
		{
			int L=incoming.size();
			clear();
			str=new char [L+1];
			strcpy(str,incoming.c_str());
		}
	}


	TextString(const char incoming[])
	{
		set(incoming);
	}
	TextString &operator=(const char incoming[])
	{
		set(incoming);
		return *this;
	}
	void set(const char incoming[])
	{
		if(incoming!=str)
		{
			clear();
			str=new char [strlen(incoming)+1];
			strcpy(str,incoming);
		}
	}


	~TextString()
	{
		clear();
	}
	void clear(void)
	{
		if(nullptr!=str)
		{
			delete [] str;
		}
		str=nullptr;
	}


	void push_back(char c)
	{
		if(nullptr==str)
		{
			str=new char [2];
			str[0]=c;
			str[1]=0;
		}
		else
		{
			int L=strlen(str);

			char *newStr=new char [L+2];
			strcpy(newStr,str);
			newStr[L]=c;
			newStr[L+1]=0;

			delete [] str;

			str=newStr;
		}
	}

	void pop_back(void)
	{
		auto L=size();
		if(0<L)
		{
			str[L-1]=0;

			char *newStr=new char [L];
			strcpy(newStr,str);

			delete [] str;

			str=newStr;
		}
	}

	const char *c_str(void) const
	{
		if(nullptr!=str)
		{
			return str;
		}
		return "";
	}

	size_t size(void) const
	{
		return strlen(c_str());
	}
};


void Print(const TextString &str)
{
	printf("%s\n",str.c_str());
}



class TextInput
{
protected:
	TextString title;
	TextString str;

public:
	TextString GetString(void)
	{
		return str;
	}
    void clearStr(){
        str.set("");
    }
	void SetTitle(const char title[])
	{
		this->title=title;
	}
    TextString GetTitle(){
        return title;
    }
	void RunOneStep(int fskey,char c)
	{
		if(0!=isprint(c))
		{
			str.push_back(c);
		}
		if(FSKEY_ESC==fskey)
		{
			str.clear();
		}
		if(FSKEY_BS==fskey)
		{
			str.pop_back();
		}
	}

	void Draw(void) const
	{
        glColor3ub(0,0,0);
        glRasterPos2f(640.0f - 8.0f*(float)(strlen(title.c_str())/2),380.0f + 6.0f);
        YsGlDrawFontBitmap8x12(title.c_str());
		auto cpy=str;
		if(0==time(NULL)%2)
		{
			cpy.push_back('|');
		}
		else
		{
			cpy.push_back('_');
		}
        glRasterPos2d(640.0f - 8.0f*(float)(strlen(title.c_str())/2), 400.0f + 6.0f);
        YsGlDrawFontBitmap8x12(cpy.c_str());
	}
};

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

/* begin of buttom class*/
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
        glColor3ub(230, 150, 150);
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
    void run(UserInfoManager &manager,std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2,
     std::vector<buttom> &stage3,std::vector<buttom> &stage4,std::vector<buttom> &stage5,std::vector<buttom> &stage6,std::vector<buttom> &stage7, YsRawPngDecoder &background);
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
stage1: login phase
stage2: start menu
stage3: game mode selection
stage4: setting
stage5: deathbattle
stage6: occupation
stage7: timelimited occupation
*/
void menu::run(UserInfoManager &manager,std::vector<buttom> &stage0, std::vector<buttom> &stage1, std::vector<buttom> &stage2, std::vector<buttom> &stage3,std::vector<buttom> &stage4,std::vector<buttom> &stage5,std::vector<buttom> &stage6,std::vector<buttom> &stage7, YsRawPngDecoder &background)
{
    if(stage == 0){
        auto t0=std::chrono::high_resolution_clock::now();
        for(;;){
            auto t=std::chrono::high_resolution_clock::now();
		    auto millisec=std::chrono::duration_cast<std::chrono::milliseconds>(t-t0).count();
		    double dt=(double)millisec/1000.0;
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
            if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 1;
                    break;
                }
            char *title = "Click Anywhere to Continue";
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glColor4ub(0,0,0,(int)(dt*50)%255);
            glRasterPos2f(640.0f - 20.0f*(float)(strlen(title)/2), 700.0f + 14.0f);
            YsGlDrawFontBitmap20x28(title);
            glDisable(GL_BLEND);
            FsSwapBuffers();
        }
    }
    if(stage == 1){
        TextInput textInput;
	    textInput.SetTitle("Please Enter User Name");
        manager.update();
        std::string inputUserName = "";
        std::string inputPassword = "";
        bool loginflag = true;
        bool logedin = false;
        for(;;){
            FsPollDevice();
            auto key = FsInkey();
            if (key == FSKEY_ESC)
            {
                stage = -1;
                break;
            }
            if (key == FSKEY_ENTER)
            {
                if(strcmp(textInput.GetTitle().c_str(), "Please Enter User Name")==0){
                    inputUserName = textInput.GetString().c_str();
                    textInput.clearStr();
                    textInput.SetTitle("Please Enter Password");
                }
                else{
                    inputPassword = textInput.GetString().c_str();
                    textInput.clearStr();
                    textInput.SetTitle("Please Enter User Name");
                }
            }
            auto c=FsInkeyChar();
		    textInput.RunOneStep(key,c);
            int lb, mb, rb, mx, my;
            int mouseEvent;
            mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

            if (stage1[0].isinsidebuttom(mx, my))
            {
                stage1[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {   
                    for(size_t index = 0; index < manager.getUsername().size();++index){
                        if(inputUserName.compare(manager.getUsername()[index])==0){
                            if(inputPassword.compare(manager.getPassword()[index])==0){
                                stage = 2;
                                logedin = true;
                                break;
                            }
                          
                        }
                    }
                    loginflag=false;
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
                    for(size_t index = 0; index < manager.getUsername().size();++index){
                        if(inputUserName.compare(manager.getUsername()[index])==0){
                            if(inputPassword.compare(manager.getPassword()[index])==0){
                                stage = 2;
                                logedin = true;
                                break;
                            }
                        }
                    }
                    if (!logedin)
                    {
                        if(inputUserName!=""&&inputPassword!=""){
                            std::ofstream myfile;
                            myfile.open("../src/userinfo.txt");
                            myfile << manager.getNumUser()+1<<"\n";
                            for(size_t index = 0; index < manager.getUsername().size();++index){
                                myfile << manager.getUsername()[index]<<" "<<manager.getPassword()[index]<<"\n";
                            }
                            myfile << inputUserName<<" "<<inputPassword<<"\n";
                            myfile.close();
                        }
                    }
                    stage = 2;
                    logedin = true;
                    break;
                }
            }
            else
            {
                stage1[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage1.size(); i++)
            {
                stage1[i].draw();
            }

            if(!loginflag){
                glColor3ub(0,0,0);
                char *title = "Login in Failed, Please Re-enter User Information";
                glRasterPos2f(640.0f - 8.0f*(float)(strlen(title)/2), 500.0f + 6.0f);
                YsGlDrawFontBitmap8x12(title);
                glDisable(GL_BLEND);
            }
            textInput.Draw();
            FsSwapBuffers();
            if(logedin){
                break;
            }
            
        }
    }
    if (stage == 2)
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

            if (stage2[0].isinsidebuttom(mx, my))
            {
                stage2[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 3;
                    break;
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
                    stage = 4;
                    break;
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
                    stage = 1;
                    break;
                }
            }
            else
            {
                stage2[2].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage2.size(); i++)
            {
                stage2[i].draw();
            }
            FsSwapBuffers();
        }
    }
    else if (stage == 3)
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

            if (stage3[0].isinsidebuttom(mx, my))
            {
                stage3[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 5;
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
                    stage = 6;
                    break;
                }
            }
            else
            {
                stage3[1].setstate(0);
            }
            if (stage3[2].isinsidebuttom(mx, my))
            {
                stage3[2].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 7;
                    break;
                }
            }
            else
            {
                stage3[2].setstate(0);
            }

            if (stage3[3].isinsidebuttom(mx, my))
            {
                stage3[3].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 2;
                    break;
                }
            }
            else
            {
                stage3[3].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
            for (int i = 0; i < stage3.size(); i++)
            {
                stage3[i].draw();
            }
            FsSwapBuffers();
        }
    }
    else if (stage == 4)
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

            if (stage4[0].isinsidebuttom(mx, my))
            {
                stage4[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /*  increase the volumn */

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
                    /*  decrease the volumn */
                }
            }
            else
            {
                stage4[1].setstate(0);
            }
            if (stage4[2].isinsidebuttom(mx, my))
            {
                stage4[2].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                   /*set winning condition*/
                }
            }
            else
            {
                stage4[2].setstate(0);
            }

            if (stage4[3].isinsidebuttom(mx, my))
            {
                stage4[3].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 2;
                    break;
                }
            }
            else
            {
                stage4[3].setstate(0);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            drawBackground(background);
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
                    stage = 3;
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
    }else if(stage == 6){
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

            if (stage6[0].isinsidebuttom(mx, my))
            {
                stage6[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 3;
                    break;
                }
            }
            else
            {
                stage6[0].setstate(0);
            }

            if (stage6[1].isinsidebuttom(mx, my))
            {
                stage6[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /* pause */
                }
            }
            else
            {
                stage6[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < stage6.size(); i++)
            {
                stage6[i].draw();
            }
            FsSwapBuffers();
        }
    }else if(stage == 7){
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

            if (stage7[0].isinsidebuttom(mx, my))
            {
                stage7[0].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    stage = 3;
                    break;
                }
            }
            else
            {
                stage7[0].setstate(0);
            }

            if (stage7[1].isinsidebuttom(mx, my))
            {
                stage7[1].setstate(1);
                if (mouseEvent == FSMOUSEEVENT_LBUTTONUP)
                {
                    /* pause */
                }
            }
            else
            {
                stage7[1].setstate(0);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < stage7.size(); i++)
            {
                stage7[i].draw();
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
    
    std::vector<buttom> stage1;
    UserInfoManager manager = UserInfoManager("../src/userinfo.txt");
    buttom buttom17(540.0f, 600.0f, 150.0f, 50.0f, "Login");
    buttom buttom18(740.0f, 600.0f, 150.0f, 50.0f, "Register");
    stage1.push_back(buttom17);
    stage1.push_back(buttom18);
    std::vector<buttom> stage2;
    buttom buttom1(640.0f, 400.0f, 150.0f, 50.0f, " START ");
    buttom buttom2(640.0f, 500.0f, 150.0f, 50.0f, "SETTING");
    buttom buttom19(50.0f, 50.0f, 70.0f, 50.0f, "Log Out");
    stage2.push_back(buttom1);
    stage2.push_back(buttom2);
    stage2.push_back(buttom19);
    std::vector<buttom> stage3;
    buttom buttom3(640.0f, 400.0f, 150.0f, 50.0f, "DEATHBATTLE");
    buttom buttom4(640.0f, 500.0f, 150.0f, 50.0f, "OCCUPATION");
    buttom buttom5(640.0f, 600.0f, 150.0f, 50.0f, "TIMELIMITED");
    buttom buttom6(50.0f, 50.0f, 50.0f, 50.0f, "BACK");
    stage3.push_back(buttom3);
    stage3.push_back(buttom4);
    stage3.push_back(buttom5);
    stage3.push_back(buttom6);
    std::vector<buttom> stage4;
    buttom buttom7(540.0f, 400.0f, 150.0f, 50.0f, "VOLUME UP");
    buttom buttom8(740.0f, 400.0f, 150.0f, 50.0f, "VOLUMEDOWN");
    buttom buttom9(640.0f, 500.0f, 250.0f, 50.0f, "WINNING CONDITION");
    buttom buttom10(50.0f, 50.0f, 50.0f, 50.0f, "BACK");
    stage4.push_back(buttom7);
    stage4.push_back(buttom8);
    stage4.push_back(buttom9);
    stage4.push_back(buttom10);
    std::vector<buttom> stage5;
    buttom buttom11(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom12(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage5.push_back(buttom11);
    stage5.push_back(buttom12);
    std::vector<buttom> stage6;
    buttom buttom13(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom14(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage6.push_back(buttom13);
    stage6.push_back(buttom14);
    std::vector<buttom> stage7;
    buttom buttom15(50.0f, 50.0f, 50.0f, 50.0f, "EXIT");
    buttom buttom16(1225.0f, 50.0f, 60.0f, 50.0f, "PAUSE");
    stage7.push_back(buttom15);
    stage7.push_back(buttom16);

    /* initialize your parameters*/

    
    std::cout<<"Game Initialized"<<std::endl;

    /* main game loop*/
    for (;;)
    {
        run(manager,stage0, stage1, stage2, stage3, stage4, stage5, stage6, stage7, background);
        FsPollDevice();
        auto key = FsInkey();
        if (key == FSKEY_ESC)
        {
            break;
        }
    }
}