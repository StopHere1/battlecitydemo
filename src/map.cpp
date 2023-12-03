#include"fssimplewindow.h"
//#include "../../public/src/fssimplewindow/src/fssimplewindow.h"

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<chrono>

#include"map.h"
//#include"../include/map.h"

int Map::map0[wid][len] = {  //test map
	{4,4,4,4,  4,5,6,7,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{4,0,0,0,  4,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{4,0,6,0,  4,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 }, // 6

	{4,4,4,0,  4,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,1,2,3,  4,5,6,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },

	{0,0,0,0,  1,2,3,4,  5,6,7,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  1,2,3,4,  5,6,7,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  1,2,3,4,  5,6,7,0,  0,6,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 }, // 6

	{0,0,0,0,  0,0,0,0,  0,0,6,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 }, // 6
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,6,0,0,  4,0,0,0,  0,0,0,0 }, // 6
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
};
int Map::map1[wid][len] = {  //1280x720  40x40 >> 32x18
	{0,0,0,0,  0,0,1,1,  1,1,1,1,  1,1,1,1,  1,1,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
	{1,3,3,3,  3,3,3,0,  0,0,0,0,  0,0,0,0,  0,3,3,3,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,5,6,3,  3,0,0,4,  3,3,3,1,  1,3,3,3,  4,0,0,3,  3,0,0,1,  4,0,0,0,  0,0,0,0 }, // 6  // 5 test

	{1,0,0,3,  3,0,0,4,  0,3,0,1,  1,0,3,0,  4,0,0,3,  3,0,0,1,  4,0,0,0,  0,0,0,0 },
	{1,0,0,3,  3,0,0,4,  3,3,3,1,  1,3,3,3,  4,0,0,3,  3,0,0,1,  4,0,0,0,  0,0,0,0 },
	{1,3,3,3,  3,3,3,0,  0,0,0,0,  0,0,0,0,  0,3,3,3,  3,3,3,1,  4,0,0,0,  0,0,0,0 },

	{0,0,0,1,  1,0,0,1,  4,1,3,3,  3,3,1,1,  1,0,0,1,  1,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,1,  1,0,0,1,  4,1,3,0,  0,3,1,1,  1,0,0,1,  1,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,4,4,0,  0,0,4,4,  0,6,0,0,  0,4,4,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 }, // 6

	{0,0,0,0,  0,4,4,0,  0,0,6,0,  4,4,0,0,  0,4,4,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 }, // 6
	{0,0,0,1,  1,0,0,1,  1,1,3,0,  0,3,1,4,  1,0,0,1,  1,0,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,0,1,  1,0,0,1,  1,1,3,3,  3,3,1,4,  1,0,0,1,  1,0,0,0,  4,0,0,0,  0,0,0,0 },

	{1,3,3,3,  3,3,3,0,  0,0,0,0,  0,0,0,0,  0,3,3,3,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,0,0,3,  3,0,0,4,  3,3,3,1,  1,3,3,3,  4,0,0,3,  3,0,0,1,  4,0,0,0,  0,0,0,0 },
	{1,0,0,3,  3,0,0,4,  0,3,0,1,  1,0,3,0,  4,0,0,3,  3,0,0,1,  4,0,0,0,  0,0,0,0 },

	{1,0,0,3,  3,0,0,4,  3,3,3,1,  1,3,3,3,  4,0,0,3,  3,6,0,1,  4,0,0,0,  0,0,0,0 }, // 6
	{1,3,3,3,  3,3,3,0,  0,0,0,0,  0,0,0,0,  0,3,3,3,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,1,1,  1,1,1,1,  1,1,1,1,  1,1,0,0,  0,0,0,0,  4,0,0,0,  0,0,0,0 },
};
int Map::map2[wid][len] = {
	{1,1,1,1,  1,0,1,1,  1,0,1,5,  0,1,0,1,  1,1,0,1,  1,1,1,1,  4,0,0,0,  0,0,0,0 },
	{1,3,3,3,  4,0,1,1,  1,0,1,1,  1,1,0,1,  1,1,0,4,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,3,6,3,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  3,5,3,1,  4,0,0,0,  0,0,0,0 }, // 6

	{1,3,3,5,  4,0,4,4,  3,4,4,4,  4,4,4,4,  4,4,0,4,  6,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,4,4,4,  4,0,4,0,  3,0,0,0,  0,0,0,3,  0,4,0,4,  4,4,4,1,  4,0,0,0,  0,0,0,0 },
	{0,0,3,3,  3,3,4,0,  4,4,4,0,  0,4,4,4,  0,4,3,3,  3,3,0,0,  4,0,0,0,  0,0,0,0 },

	{3,3,3,1,  1,0,0,1,  4,1,3,3,  3,3,1,4,  1,0,0,1,  1,3,3,3,  4,0,0,0,  0,0,0,0 },
	{1,1,3,1,  1,0,0,1,  4,1,3,0,  3,3,1,4,  1,0,0,1,  1,3,0,0,  4,0,0,0,  0,0,0,0 },
	{5,1,3,0,  0,4,4,0,  0,0,4,3,  5,6,0,0,  0,4,4,0,  0,3,1,1,  4,0,0,0,  0,0,0,0 }, // 6

	{1,1,3,0,  0,4,4,0,  0,0,6,3,  3,4,0,0,  0,4,4,0,  0,3,1,5,  4,0,0,0,  0,0,0,0 }, // 6
	{0,0,3,1,  1,0,0,1,  4,1,3,0,  0,3,1,4,  1,0,0,1,  1,3,1,1,  4,0,0,0,  0,0,0,0 },
	{3,3,3,1,  1,0,0,1,  4,1,3,3,  3,3,1,4,  1,0,0,1,  1,3,3,3,  4,0,0,0,  0,0,0,0 },

	{0,0,3,3,  3,3,4,0,  4,4,4,0,  0,4,4,4,  0,4,3,3,  3,3,0,0,  4,0,0,0,  0,0,0,0 },
	{1,4,4,4,  4,0,4,0,  3,0,0,0,  0,0,0,3,  0,4,0,4,  4,4,4,1,  4,0,0,0,  0,0,0,0 },
	{1,3,3,6,  4,0,4,4,  3,4,4,4,  4,4,4,3,  4,4,0,4,  5,3,3,1,  4,0,0,0,  0,0,0,0 },

	{1,3,5,3,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  3,6,3,1,  4,0,0,0,  0,0,0,0 }, // 6
	{1,3,3,3,  4,0,1,1,  1,0,1,1,  1,1,0,1,  1,1,0,4,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,0,1,1,  1,0,1,5,  0,1,0,1,  1,1,0,1,  1,1,1,1,  4,0,0,0,  0,0,0,0 },
};
int Map::map3[wid][len] = {
	{1,1,1,1,  1,0,1,1,  1,0,1,0,  0,1,0,1,  1,1,0,1,  1,1,1,1,  4,0,0,0,  0,0,0,0 },
	{1,3,3,3,  4,0,1,1,  1,0,1,1,  1,1,0,1,  1,1,0,4,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,3,6,3,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  3,5,3,1,  4,0,0,0,  0,0,0,0 }, // 6

	{1,3,3,5,  4,0,3,3,  3,4,4,4,  4,4,4,3,  3,3,0,4,  6,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,4,4,4,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  4,4,4,1,  4,0,0,0,  0,0,0,0 },
	{0,0,3,0,  0,0,3,0,  4,4,4,0,  0,4,4,4,  0,3,0,0,  0,3,0,0,  4,0,0,0,  0,0,0,0 },

	{3,3,3,1,  1,0,3,1,  4,1,3,3,  3,3,1,4,  1,3,0,1,  1,3,3,3,  4,0,0,0,  0,0,0,0 },
	{0,0,3,1,  1,0,3,1,  4,1,3,0,  3,3,1,4,  1,3,0,1,  1,3,0,0,  4,0,0,0,  0,0,0,0 },
	{0,0,3,0,  0,4,4,0,  0,0,4,3,  5,6,0,0,  0,4,4,0,  0,3,0,0,  4,0,0,0,  0,0,0,0 }, // 6

	{0,0,3,0,  0,4,4,0,  0,0,6,3,  3,4,0,0,  0,4,4,0,  0,3,0,0,  4,0,0,0,  0,0,0,0 }, // 6
	{0,0,3,1,  1,0,3,1,  4,1,3,0,  0,3,1,4,  1,3,0,1,  1,3,0,0,  4,0,0,0,  0,0,0,0 },
	{3,3,3,1,  1,0,3,1,  4,1,3,3,  3,3,1,4,  1,3,0,1,  1,3,3,3,  4,0,0,0,  0,0,0,0 },

	{0,0,3,0,  0,0,3,0,  4,4,4,0,  0,4,4,4,  0,3,0,0,  0,3,0,0,  4,0,0,0,  0,0,0,0 },
	{1,4,4,4,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  4,4,4,1,  4,0,0,0,  0,0,0,0 },
	{1,3,3,6,  4,0,3,3,  3,4,4,4,  4,4,4,3,  3,3,0,4,  5,3,3,1,  4,0,0,0,  0,0,0,0 },

	{1,3,5,3,  4,0,3,0,  3,0,0,0,  0,0,0,3,  0,3,0,4,  3,6,3,1,  4,0,0,0,  0,0,0,0 }, // 6
	{1,3,3,3,  4,0,1,1,  1,0,1,1,  1,1,0,1,  1,1,0,4,  3,3,3,1,  4,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,0,1,1,  1,0,1,0,  0,1,0,1,  1,1,0,1,  1,1,1,1,  4,0,0,0,  0,0,0,0 },
};




void Map::wall1(int x, int y) { //tree like
	glColor3ub(210, 186, 140);//brown
	glBegin(GL_QUADS);
	glVertex2d(x + l, y); glVertex2d(x + l, y - 2 * l); glVertex2d(x + 3 * l, y - 2 * l); glVertex2d(x + 3 * l, y - 0 * l);
	glEnd();

	glColor3ub(100, 200, 100); //green
	glBegin(GL_QUADS);
	glVertex2d(x, y - 2 * l); glVertex2d(x, y - 4 * l); glVertex2d(x + 4 * l, y - 4 * l); glVertex2d(x + 4 * l, y - 2 * l);
	glEnd();

	glColor3ub(150, 150, 150);//gray
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x + l, y); glVertex2d(x + l, y - 2 * l); glVertex2d(x, y - 2 * l); glVertex2d(x, y - 4 * l);
	glVertex2d(x + 4 * l, y - 4 * l); glVertex2d(x + 4 * l, y - 2 * l); glVertex2d(x + 3 * l, y - 2 * l); glVertex2d(x + 3 * l, y);
	glEnd();
	glLineWidth(1);
}
void Map::wall2(int x, int y) { //red cross
	glColor3f(1, 0, 0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2d(x + l, y - l); glVertex2d(x + 3 * l, y - 3 * l); glVertex2d(x + l, y - 3 * l); glVertex2d(x + 3 * l, y - 1 * l);
	glEnd();

	glLineWidth(5);
	glColor3ub(150, 150, 150);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + m, y - m); glVertex2f(x + m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - m);
	glEnd();
	glLineWidth(1);
}
void Map::wall3(int x, int y) { // brick wall 
	glColor3ub(205, 133, 63);//brick brown
	glBegin(GL_QUADS);
	glVertex2f(x, y); glVertex2f(x, y - 4 * l); glVertex2f(x + 4 * l, y - 4 * l); glVertex2f(x + 4 * l, y);
	glEnd();

	glColor3ub(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2d(x, y - 2 * l); glVertex2d(x + 4 * l, y - 2 * l);   glVertex2d(x + l, y - 2 * l); glVertex2d(x + l, y - 4 * l);
	glVertex2d(x + 3 * l, y - 2 * l); glVertex2d(x + 3 * l, y - 4 * l);    glVertex2d(x + 2 * l, y - 0 * l); glVertex2d(x + 2 * l, y - 2 * l);
	glEnd();

	glColor3ub(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(x, y); glVertex2f(x + 4 * l, y);   glVertex2f(x, y - 4 * l); glVertex2f(x + 4 * l, y - 4 * l);
	glVertex2f(x, y); glVertex2f(x, y - 2 * l);      glVertex2f(x + 4 * l, y); glVertex2f(x + 4 * l, y - 2 * l);
	glEnd();
	glLineWidth(1);

	//glColor3ub(100, 100, 100);
	//glLineWidth(5);
	//glBegin(GL_LINE_LOOP);
	////glVertex2f(x+n,y-n);glVertex2f(x+n,y-4*l+n);glVertex2f(x+4*l-n,y-4*l+n);glVertex2f(x+4*l-n,y-n);
	//glVertex2f(x, y); glVertex2f(x, y - 4 * l); glVertex2f(x + 4 * l, y - 4 * l); glVertex2f(x + 4 * l, y);
	//glEnd();
	//glLineWidth(1);

}
void Map::wall4(int x, int y) { // gray solid wall
	glColor3ub(200, 200, 200);
	glBegin(GL_QUADS);
	glVertex2d(x, y); glVertex2d(x, y - 4 * l); glVertex2d(x + l, y - 3 * l); glVertex2d(x + l, y - l);
	glEnd();
	glColor3ub(190, 190, 190);
	glBegin(GL_QUADS);
	glVertex2d(x, y - 4 * l); glVertex2d(x + 4 * l, y - 4 * l); glVertex2d(x + 3 * l, y - 3 * l); glVertex2d(x + l, y - 3 * l);
	glEnd();
	glColor3ub(150, 150, 150);
	glBegin(GL_QUADS);
	glVertex2d(x + 4 * l, y - 4 * l); glVertex2d(x + 4 * l, y - 0 * l); glVertex2d(x + 3 * l, y - 1 * l); glVertex2d(x + 3 * l, y - 3 * l);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_QUADS);
	glVertex2d(x + 0 * l, y - 0 * l); glVertex2d(x + 1 * l, y - 1 * l); glVertex2d(x + 3 * l, y - 1 * l); glVertex2d(x + 4 * l, y - 0 * l);
	glEnd();
	glColor3ub(240, 240, 240);
	glBegin(GL_QUADS);
	glVertex2d(x + 1 * l, y - 1 * l); glVertex2d(x + 1 * l, y - 3 * l); glVertex2d(x + 3 * l, y - 3 * l); glVertex2d(x + 3 * l, y - 1 * l);
	glEnd();
}
void Map::wall5(int x, int y) { // land point //red dot
	glLineWidth(5);
	glColor3ub(150, 150, 150);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + m, y - m); glVertex2f(x + m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - m); glEnd();

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + l, y - l); glVertex2f(x + l, y - 3 * l); glVertex2f(x + 3 * l, y - 3 * l); glVertex2f(x + 3 * l, y - l);   // inner square
	glEnd();
	glPointSize(10);
	glColor3ub(250, 150, 150);  //light red
	glBegin(GL_POINTS);
	glVertex2f(x + 2 * l, y - 2 * l);
	glEnd();
	glLineWidth(1);
}
void Map::wall7(int x, int y) { // land point //green dot
	glLineWidth(5);
	glColor3ub(150, 150, 150);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + m, y - m); glVertex2f(x + m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - m); glEnd();

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + l, y - l); glVertex2f(x + l, y - 3 * l); glVertex2f(x + 3 * l, y - 3 * l); glVertex2f(x + 3 * l, y - l);   // inner square
	glEnd();
	glPointSize(10);
	glColor3ub(100, 200, 150);  //light green
	glBegin(GL_POINTS);
	glVertex2f(x + 2 * l, y - 2 * l);
	glEnd();
	glLineWidth(1);
}
void Map::wall6(int x, int y) {
	glLineWidth(5);
	glColor3ub(150, 150, 150);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + m, y - m); glVertex2f(x + m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - 4 * l + m); glVertex2f(x + 4 * l - m, y - m);
	glEnd();
	glLineWidth(1);
}




void Map::print_map(int mapp[18][32]) {   //mapp[wid][len]  //
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapp[j][i] == 1) {
				wall1(i * L, j * L + L);
			}
			else if (mapp[j][i] == 2) {
				wall2(i * L, j * L + L);
			}
			else if (mapp[j][i] == 3) {
				wall3(i * L, j * L + L);
			}
			else if (mapp[j][i] == 4) {
				wall4(i * L, j * L + L);
			}
			else if (mapp[j][i] == 5) {
				wall5(i * L, j * L + L);
			}
			else if (mapp[j][i] == 6) {
				wall6(i * L, j * L + L);
			}
			else if (mapp[j][i] == 7) {
				wall7(i * L, j * L + L);
			}

		}
	}
}


bool Map::checkCollision(int boxX, int boxY, int wallI, int wallJ) {  // tank
	int boxLeft = boxX + of;   // leave 5 pixels offset to do presice control for deleting blocks
	int boxRight = boxX + L - of;
	int boxTop = boxY - of;
	int boxBottom = boxY - (L - of);

	int wallLeft = wallI * L;
	int wallRight = (wallI + 1) * L;
	int wallBottom = wallJ * L;
	int wallTop = (wallJ + 1) * L;

	if (boxRight < wallLeft || boxLeft > wallRight || boxTop < wallBottom || boxBottom > wallTop) {
		return false;  // No collision
	}
	return true;  // Collision detected
}

bool Map::checkCollision2(int boxX, int boxY, int wallI, int wallJ) { // for landing block
	int boxLeft = boxX + of2;
	int boxRight = boxX + L - of2;
	int boxTop = boxY - of2;
	int boxBottom = boxY - (L - of2);

	int wallLeft = wallI * L;
	int wallRight = (wallI + 1) * L;
	int wallBottom = wallJ * L;
	int wallTop = (wallJ + 1) * L;

	if (boxRight < wallLeft || boxLeft > wallRight || boxTop < wallBottom || boxBottom > wallTop) {
		return false;  // No collision
	}
	return true;  // Collision detected
}
bool Map::checkCollision3(int boxX, int boxY, int wallI, int wallJ) { // bullet
	boxX += L / 2; boxY -= L / 2; int d = 10;
	int boxLeft = boxX - d;
	int boxRight = boxX + d;
	int boxTop = boxY - d;
	int boxBottom = boxY + d;

	int wallLeft = (wallI * L) - 30;
	int wallRight = (wallI + 1) * L;
	int wallBottom = wallJ * L;
	int wallTop = (wallJ + 1) * L;

	//printf("%d %d %d %d\n%d %d %d %d\n\n", boxLeft, boxRight, boxTop, boxBottom, wallLeft, wallRight, wallBottom, wallTop);
	if (boxRight < wallLeft || boxLeft > wallRight || boxTop < wallBottom || boxBottom > wallTop) {
		return false;  // No collision
	}
	return true;  // Collision detected
}

void Map::deleteWall(int i, int j) {
	if (i >= 0 && i < len && j >= 0 && j < wid) {
		mapf[j][i] = 0;
	}
}

void Map::do_delete(int& x, int& y) {  // tank   //, int mapp[18][32]
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0 && checkCollision(x, y, i, j)
				&& mapf[j][i] != 1 && mapf[j][i] != 2 && mapf[j][i] != 3
				&& mapf[j][i] != 4 && mapf[j][i] != 5 && mapf[j][i] != 6 && mapf[j][i] != 7
				) { // this can set to delete which block After Collision Detection
				deleteWall(i, j);
				//printf("hit\n");   //
			}
		}
	}
}
void Map::do_delete2(int& x, int& y) {   // bullet // , int mapp[18][32]
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {  // destroy 1 3 
			if (mapf[j][i] != 0 && checkCollision3(x, y, i, j)    //
				//&& mapp[j][i] != 1 && mapp[j][i] != 3
				&& mapf[j][i] != 2
				&& mapf[j][i] != 4 && mapf[j][i] != 5
				&& mapf[j][i] != 6 && mapf[j][i] != 7
				) { // this can set to delete which block After Collision Detection
				deleteWall(i, j);
			}
		}
	}
}
bool Map::not_move(int& x, int& y, int& prex, int& prey) {  // for non-destructive //需要实时数据 （在main里） // tank
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0 && checkCollision(x, y, i, j)) {
				if (mapf[j][i] == 4 || mapf[j][i] == 3) {
					x = prex, y = prey;
					return false;
				}
			}
		}
	}
	return true;
}
bool Map::not_move2(int& x, int& y, int& prex, int& prey) {  // for non-destructive //需要实时数据 （在main里） // bullet
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0 && checkCollision(x, y, i, j)) {
				if (mapf[j][i] == 4) {  //2
					x = prex, y = prey;
					return false;
				}
			}
		}
	}
	return true;
}
//using Clock = std::chrono::high_resolution_clock;
//using TimePoint = std::chrono::time_point<Clock>;
//using Seconds = std::chrono::seconds;

void Map::change_block(int& x, int& y) { // landing block   //, int mapp[18][32]
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0 && checkCollision(x, y, i, j)) { //&& checkCollision(x, y, i, j)  && mapp[j][i] == 5
				TimePoint startTime = Clock::now();
				while (checkCollision2(x, y, i, j) && mapf[j][i] == 5) {
					TimePoint currentTime = Clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
					//if (duration > 1) {
					mapf[j][i] = 7;   //
					//printf(" [%d] ", mapf[j][i]);
					break;
					//}
				}
				if (  !(checkCollision2(x, y, i, j))   //!(checkCollision(x, y, i, j))
					&& 
					mapf[j][i] == 7
					) {
					mapf[j][i] = 2;  // Change back to other walls if no collision
					score1 += 10;
					//printf("hit\n");
					//break;
				}
			}
		}
	}
}
void Map::change_block2(int& x, int& y) {   //, int mapp[18][32]
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0) { //&& checkCollision(x, y, i, j)  && mapp[j][i] == 5
				TimePoint startTime = Clock::now();
				while (checkCollision2(x, y, i, j) && mapf[j][i] == 5) {
					TimePoint currentTime = Clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
					//if (duration > 1) {
					mapf[j][i] = 7;   //
					break;
					//}
				}
				if (!checkCollision2(x, y, i, j) && mapf[j][i] == 7) {
					mapf[j][i] = 2;  // Change back to other walls if no collision
					score2 += 10;
					//break;
				}
			}
		}
	}
}

void Map::copymap(int mapp[18][32]) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			mapf[j][i] = mapp[j][i];
		}
	}
}
void Map::choosemap(int choicei) {   //change the input value to switch maps
	if (choicei == 1) { copymap(map1); }
	else if (choicei == 2) { copymap(map2); }
	else if (choicei == 3) { copymap(map3); }
	else if (choicei == 0) { copymap(map0); }  //map0 - just for test purpose
}
void Map::testbox(int& x, int& y) {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP); int d = 40;
	glVertex2d(x, y); glVertex2d(x, y - d); glVertex2d(x + d, y - d); glVertex2d(x + d, y);
	glEnd();
}
void Map::testbullet(int& x, int& y) {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP); int d = 10;
	glVertex2d(x, y); glVertex2d(x, y - d); glVertex2d(x + d, y - d); glVertex2d(x + d, y);
	glEnd();
}


//TimePoint t0 = Clock::now();
void Map::countdown(int mapi, int timenum) {
	//auto t0 = time(NULL);


	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t0).count();
	if (elapsedTime > timenum) {
		//printf("score=%d ", score1);
		ter = 1;
	}
}
Map::~Map() {
	score1 = 0;
	score2 = 0;
}
