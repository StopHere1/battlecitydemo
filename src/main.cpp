#include"fssimplewindow.h"
//#include "../../public/src/fssimplewindow/src/fssimplewindow.h"

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<chrono>
#include<iostream>

#include"map.h"
#include"menu.h"
//#include"../include/map.h"
//#include"../include/menu.h"


int main() {
	menu menu;
	menu.start();

	Map map;
	
	map.choosemap(map.choice);

	FsOpenWindow(0, 0, 1280, 720, 2);

	int x, y, d;
	x = 0, y = 40, d = 5;
	int bx, by;
	bx = 100, by = 40;

	while (map.ter != 1) {
		map.c();

		map.testbox(x, y);
		map.testbullet(bx, by);
		map.print_map(map.mapf);

		map.countdown(map.choice, 6000);  //map.timeInt

		int prex = x, prey = y;
		int prebx = bx, preby = by;

		map.do_delete(x, y, map.mapf);
		map.do_delete2(bx, by, map.mapf);

		map.change_block(x, y, map.mapf);
		//map.change_block(bx, by, map.mapf);


		FsPollDevice();		auto key = FsInkey();
		switch (key) {
		case FSKEY_ESC:
			map.ter = 1; break;
		case FSKEY_W:
			y -= d; break;
		case FSKEY_S:
			y += d; break;
		case FSKEY_A:
			x -= d; break;
		case FSKEY_D:
			x += d; break;

		case FSKEY_UP:
			by -= d; break;
		case FSKEY_DOWN:
			by += d; break;
		case FSKEY_LEFT:
			bx -= d; break;
		case FSKEY_RIGHT:
			bx += d; break;
		}

		map.not_move(x, y, prex, prey);
		map.not_move2(bx, by, prebx, preby);



		//printf("score=%d ", map.score);

		FsSwapBuffers();
		FsSleep(20);
	}
	return 0;
}
//