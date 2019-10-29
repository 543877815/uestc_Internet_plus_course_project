#include "avoidsprites.h"
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <iostream>
using namespace std;

//宏替换COLLISION
#define COLLISION(id) case id:																				\
if (skill##id##_x <= x && skill##id##_x + skillWidth >= x)													\
{																											\
	if (skill##id##_y >= y && skill##id##_y <= y + height)return c;											\
	if (skill##id##_y <= y && skill##id##_y + skillHeight >= y)return c;									\
}																											\
else																										\
{																											\
	if (skill##id##_x >= x && x + width >= skill##id##_x)													\
	{																										\
		if (skill##id##_y >= y && skill##id##_y <= y + height)return c;										\
		if (skill##id##_y <= y && skill##id##_y + skillHeight >= y)return c;								\
	}																										\
}																											\
break;	
//析构函数
avoidsprites::~avoidsprites()
{
}
//构造函数
avoidsprites::avoidsprites(const char *skill1_name,int width, int height, float position_x, float position_y, int queenwidth, int queenheight, int windowWidth, int windowHeight)
{
	strcpy_s(this->skill1_name, skill1_name);
	loadImage(skill1_name, &skill_1);
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->position_x = position_x;
	this->position_y = position_y;
	this->queenheight = queenheight;
	this->queenwidth = queenwidth;
	srand((unsigned)time(NULL));
	skill1_x = rand() % 1300;
	skill1_y = rand() % 700;
	dx = rand() % 10 + 10;
	dy = rand() % 10 + 10;
}
//对象复制
avoidsprites::avoidsprites(avoidsprites &a)
{
	strcpy_s(skill1_name, a.skill1_name);
	strcpy_s(skill2_name, a.skill2_name);
	strcpy_s(skill3_name, a.skill3_name);
	loadImage(skill1_name, &skill_1);
	loadImage(skill2_name, &skill_2);
	loadImage(skill3_name, &skill_3);
	skill1_x = a.skill1_x;
	skill1_y = a.skill1_y;
	skill2_x = a.skill2_x;
	skill2_y = a.skill2_y;
	skill3_x = a.skill3_x;
	skill3_y = a.skill3_y;
}
//随机移动
void avoidsprites::random_move()
{
	skill1_x -= dx;
	skill1_y -= dy;
	if (skill1_x >= windowWidth - skillWidth || skill1_x <= 0)
		dx *= -1;
	if (skill1_y >= windowHeight - skillHeight || skill1_y <= 0)
		dy *= -1;
}
void avoidsprites::drawskill_1()
{
	putImageTransparent(&skill_1, skill1_x, skill1_y, skillHeight, skillWidth, WHITE);
}
void avoidsprites::drawskill_2()
{
	putImageTransparent(&skill_2, skill2_x, skill2_y, skillHeight, skillWidth, WHITE);
}
void avoidsprites::drawskill_3()
{
	putImageTransparent(&skill_3, skill3_x, skill3_y, skillHeight, skillWidth, WHITE);
}
int avoidsprites::collision(float x, float y, int height, int width, int id)
{
	int c = 1;
	switch (id)
	{
		COLLISION(1)
		COLLISION(2)
		COLLISION(3)
	}
	c = 0;
	return c;
}