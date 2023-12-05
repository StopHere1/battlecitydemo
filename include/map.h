#ifndef MAP_H
#define MAP_H

#include"fssimplewindow.h"
//#include "../../public/src/fssimplewindow/src/fssimplewindow.h"

#include<chrono>

//block:
//1-tree; 2-red cross; 3-brick; 4 gray; 5 red dot landing; 6 gray frame; 7 green dot landing
const int len = 32, wid = 18;

class Map {
private:
	const int L = 40, l = L / 4, m = 5, n = 0.5, offset = 10, of = offset, of2 = 35;
	//const int len = 32, wid = 18;

public:
	int score1 = 0, score2 = 0, ter = 0, choice = 0, timeInt = 20;

	int mapf[18][32] = {};  //wid x len = 18 x 32   //mapf[18][32];    //mapf[wid][len]
	//int map1[18][32], map2[18][32], map3[18][32], map0[18][32];  

	static int map0[wid][len];
	static int map1[wid][len];
	static int map2[wid][len];
	static int map3[wid][len];


	void c(void) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void wall1(int x, int y);
	void wall2(int x, int y);
	void wall3(int x, int y);
	void wall4(int x, int y);
	void wall5(int x, int y);
	void wall7(int x, int y);
	void wall6(int x, int y);
	void print_map(int mapp[wid][len]);   //mapp[wid][len]
	bool checkCollision(int boxX, int boxY, int wallI, int wallJ);
	bool checkCollision2(int boxX, int boxY, int wallI, int wallJ);
	bool checkCollision3(int boxX, int boxY, int wallI, int wallJ);
	void deleteWall(int i, int j);
	void do_delete(int& x, int& y);  //, int mapp[wid][len]
	void do_delete2(int& x, int& y, int&i, int&j);


	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	using Seconds = std::chrono::seconds;

	void change_block(int x, int y);  //,  int mapp[wid][len]
	void change_block2(int x, int y);
	bool not_move(int x, int y);
	bool not_move2(int& x, int& y, int &i, int &j);
	bool bulletCollide(int &x, int &y,int &i, int &j);
	void copymap(int mapp[wid][len]);
	void testbox(int& x, int& y);
	void testbullet(int& x, int& y);
	void choosemap(int choice);

	TimePoint t0 = Clock::now();  //
	void countdown(int mapi, int timenum);

	~Map();
};

#endif
