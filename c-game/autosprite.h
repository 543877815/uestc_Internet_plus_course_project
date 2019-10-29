#pragma once
#include "acllib.h"
#include <iostream>
using namespace std;
class autosprite
{
private:
	int dx1, dy1, dx2, dy2;
	const int speed = 4;  //怪物的速度
	int skillspeed = 4;//技能的速度
	const int safe_distance = 5;
	const int distance1 = 300;
	const int distance2 = 200;
	const int distance3 = 100;
	int monsterWidth, monsterHeight;
	char name[50];
	int windowWidth, windowHeight;
	float position_x, position_y, queenwidth, queenheight;
	int monster_x1, monster_y1, monster_x2, monster_y2, monster_x3, monster_y3;
	int skill_x, skill_y;
	ACL_Image monster;
public:
	autosprite(autosprite &);
	autosprite(const char *name, int width, int height, float position_x, float postion_y, int queenwidth, int queenheight, int windowWidth = 1400, int windowHeight = 800);
	~autosprite();
	void random_move(float position_Lx, float position_Ly);
	void horizontal_move();
	void chasemove(float position_Lx, float position_Ly, int id);
	void drawImageScale(int i);
	void drawskill();
	void test();
	int collision(float x, float y, int height, int width, int id);
};

