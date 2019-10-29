#pragma once
#include"acllib.h"
#include <iostream>
using namespace std;
class avoidsprites
{
private:
	ACL_Image skill_1;
	ACL_Image skill_2;
	ACL_Image skill_3;
	int skillheight_1, skillwidth_1, skillheight_2, skillwidth_2;
	const int speed = 4;
	char skill1_name[20];
	char skill2_name[20];
	char skill3_name[20];
	int windowWidth, windowHeight;
	int skill1_x, skill1_y, skill2_x, skill2_y, skill3_x, skill3_y;
	int skillHeight, skillWidth;
	float position_x, position_y, queenwidth, queenheight;
	int dx, dy;
public:
	avoidsprites(const char *skill1_name, int width, int height, float position_x, float position_y, int queenwidth, int queenheight, int windowWidth = 1400, int windowHeight = 800);
	~avoidsprites();
	avoidsprites(avoidsprites &);
	void random_move();
	void drawskill_1();
	void drawskill_2();
	void drawskill_3();
	int collision(float x, float y, int height, int width, int id);
};

