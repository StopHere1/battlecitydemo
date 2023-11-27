#include"fssimplewindow.h"
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<chrono>
#include"map.h"

int Map::map0[wid][len] = {  //test map
		{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },


		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
		{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
};
int Map::map1[wid][len] = {  //1280x720  40x40 >> 32x18
	{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,2,3,4,  5,6,0,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },


	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
};
int Map::map2[wid][len] = {
	{1,2,3,4,  5,6,7,1,  1,3,3,1,  1,4,1,4,  4,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,2,2,2,  1,1,1,1,  1,3,3,1,  4,1,1,4,  4,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,  3,3,3,0,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  3,3,3,1,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  3,3,3,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,5,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,6,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },


	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,5,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
};
int Map::map3[wid][len] = {
	{1,2,3,4,  5,6,7,1,  1,3,3,1,  1,4,1,4,  4,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{1,2,2,2,  1,1,1,1,  1,3,3,1,  4,1,1,4,  4,1,1,1,  1,1,1,1,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,1,0,  0,0,0,0,  0,0,0,0,  3,3,3,0,  0,0,0,0,  0,0,0,0 },

	{1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  3,3,3,1,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  3,3,3,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,5,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,6,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },


	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,5,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },

	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
	{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0 },
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




void Map::print_map(int mapp[18][32]) {   //mapp[wid][len]
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


bool Map::checkCollision(int boxX, int boxY, int wallI, int wallJ) {
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
bool Map::checkCollision2(int boxX, int boxY, int wallI, int wallJ) {
	int boxLeft = boxX + of2;   // leave 5 pixels offset to do presice control for deleting blocks
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

void Map::deleteWall(int i, int j) {
	if (i >= 0 && i < len && j >= 0 && j < wid) {
		mapf[j][i] = 0;
	}
}

void Map::do_delete(int& x, int& y, int mapp[18][32]) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapp[j][i] != 0 && checkCollision(x, y, i, j) && mapp[j][i] != 5
				&& mapp[j][i] != 7 && mapp[j][i] != 2 && mapp[j][i] != 6) { //&& mapp[j][i] != 1
				deleteWall(i, j);
			}
		}
	}
}

//using Clock = std::chrono::high_resolution_clock;
//using TimePoint = std::chrono::time_point<Clock>;
//using Seconds = std::chrono::seconds;

void Map::change_block(int& x, int& y, int mapp[18][32]) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapp[j][i] != 0) { //&& checkCollision(x, y, i, j)  && mapp[j][i] == 5
				TimePoint startTime = Clock::now();
				while (checkCollision2(x, y, i, j) && mapp[j][i] == 5) {
					TimePoint currentTime = Clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
					//if (duration > 1) {
					mapp[j][i] = 7;   //
					break;
					//}
				}
				if (!checkCollision(x, y, i, j) && mapp[j][i] == 7) {
					mapp[j][i] = 2;  // Change back to other walls if no collision
					score += 10;
					//break;
				}
			}
		}
	}
}
void Map::change_block2(int& x, int& y, int mapp[18][32]) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapp[j][i] != 0) { //&& checkCollision(x, y, i, j)  && mapp[j][i] == 5
				TimePoint startTime = Clock::now();
				while (checkCollision2(x, y, i, j) && mapp[j][i] == 5) {
					TimePoint currentTime = Clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
					//if (duration > 1) {
					mapp[j][i] = 7;   //
					break;
					//}
				}
				if (!checkCollision(x, y, i, j) && mapp[j][i] == 7) {
					mapp[j][i] = 2;  // Change back to other walls if no collision
					score2 += 10;
					//break;
				}
			}
		}
	}
}


bool Map::not_move(int& x, int& y, int& prex, int& prey) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			if (mapf[j][i] != 0 && checkCollision(x, y, i, j)) {
				if (mapf[j][i] == 4) {
					x = prex, y = prey;
					return false;
				}
			}
		}
	}
	return true;
}
void Map::copymap(int mapp[18][32]) {
	for (int j = 0; j < wid; ++j) {
		for (int i = 0; i < len; ++i) {
			mapf[j][i] = mapp[j][i];
		}
	}
}
void Map::testbox(int& x, int& y) {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP); int d = 40;
	glVertex2d(x, y); glVertex2d(x, y - d); glVertex2d(x + d, y - d); glVertex2d(x + d, y);
	glEnd();
}
void Map::choosemap(int choicei) {   //change the input value to switch maps
	if (choicei == 1) { copymap(map1); }
	else if (choicei == 2) { copymap(map2); }
	else if (choicei == 3) { copymap(map3); }
	else if (choicei == 0) { copymap(map0); }  //map0 - just for test purpose
}

//TimePoint t0 = Clock::now();
void Map::countdown(int mapi, int timenum) {
	//auto t0 = time(NULL);


	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t0).count();
	if (elapsedTime > timenum) {
		printf("score=%d ", score);
		ter = 1;
	}
}
//Map::~Map() {
//	for (int i = 0; i < 18; ++i) {
//		delete[] Map::map0[i];
//		delete[] Map::map1[i];
//		delete[] Map::map2[i];
//		delete[] Map::map3[i];
//	}
//	delete[] Map::map0;
//	delete[] Map::map1;
//	delete[] Map::map2;
//	delete[] Map::map3;
//}

//int main() {
//	Map map;
//	map.choosemap(map.choice);
//
//	FsOpenWindow(0, 0, 1280, 720, 2);
//	int x, y, d;
//	x = 200, y = 200, d = 5;
//
//	while (map.ter != 1) {
//		map.c();
//
//		map.testbox(x, y);
//		map.print_map(map.mapf);
//
//		map.countdown(map.choice, 60);  //map.timeInt
//
//		int prex = x, prey = y;
//
//		map.do_delete(x, y, map.mapf);  //
//		map.change_block(x, y, map.mapf);
//
//
//		FsPollDevice();		auto key = FsInkey();
//		switch (key) {
//		case FSKEY_ESC:
//			map.ter = 1; break;
//		case FSKEY_W:
//			y -= d; break;
//		case FSKEY_S:
//			y += d; break;
//		case FSKEY_A:
//			x -= d; break;
//		case FSKEY_D:
//			x += d; break;
//		}
//
//		map.not_move(x, y, prex, prey);
//		printf("score=%d ", map.score);
//
//		FsSwapBuffers();
//		FsSleep(20);
//	}
//	return 0;
//}