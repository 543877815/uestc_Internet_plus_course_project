#include "autosprite.h"
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
//宏替换PAINT
#define MONSTERPAINT(id) case id:																			\
putImageTransparent(&monster, monster_x##id, monster_y##id, monsterWidth, monsterHeight, WHITE);            \
break;	
//宏替换COLLISION以建立多个对象生成点的判断
#define COLLISION(id) case id:																				\
if (monster_x##id <= x && monster_x##id + monsterWidth >= x)												\
{																											\
	if (monster_y##id >= y && monster_y##id <= y + height)return c;											\
	if (monster_y##id <= y && monster_y##id + monsterHeight >= y)return c;									\
}																											\
else																										\
{																											\
	if (monster_x##id >= x && x + width >= monster_x##id)													\
	{																										\
		if (monster_y##id >= y && monster_y##id <= y + height)return c;										\
		if (monster_y##id <= y && monster_y##id + monsterHeight >= y)return c;								\
	}																										\
}																											\
break;					
//宏替换MOVE
#define MOVE(id) case id:																					\
 x = position_Lx;  y = position_Ly;																		    \
 k1 = (y - monster_y##id) / (x - monster_x##id);															\
if (x >= monster_x##id)																						\
{																											\
	if (k1 >= 1)																							\
	{																										\
		monster_x##id += speed / k1;																		\
		monster_y##id += speed;																				\
	}																										\
	else if (k1 <= -1)																						\
	{																										\
		monster_x##id += -speed / k1;																		\
		monster_y##id += -speed;																			\
	}																										\
	else																									\
	{																										\
		monster_x##id += speed;																				\
		monster_y##id += speed * k1;																		\
	}																										\
	if (x < monster_x##id)																					\
	{																										\
		monster_x##id = x;																					\
		monster_y##id = y;																					\
	}																										\
}																											\
else																										\
{																											\
	if (k1 >= 1)																							\
	{																										\
		monster_x##id -= speed / k1;																		\
		monster_y##id -= speed;																				\
	}																										\
	else if (k1 <= -1)																						\
{																											\
		monster_x##id -= -speed / k1;																		\
		monster_y##id -= -speed;																			\
}																											\
	else																									\
	{																										\
		monster_x##id -= speed;																				\
		monster_y##id -= speed * k1;																		\
	if (x > monster_x##id)																					\
	{																										\
		monster_x##id = x;																					\
		monster_y##id = y;																					\
	}																										\
	}																										\
}																											\
break;



int x = 0, y = 0;
//析构函数
autosprite::~autosprite()
{}
//对象复制
autosprite::autosprite(autosprite &a)
{
	strcpy_s(name, a.name);
	loadImage(name, &monster);
	monster_x1 = a.monster_x1;
	monster_y1 = a.monster_y1;
	monster_x2 = a.monster_x2;
	monster_y2 = a.monster_y2;
	monster_x3 = a.monster_x3;
	monster_y3 = a.monster_y3;
	monsterWidth = a.monsterWidth;
	monsterHeight = a.monsterHeight;
}
//构造函数
autosprite::autosprite(const char *name, int width, int height, float position_x, float position_y, int queenwidth, int queenheight, int windowWidth, int windowHeight)
{
	strcpy_s(this->name, name);
	loadImage(name, &monster);
	monsterWidth = width;
	monsterHeight = height;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->position_x = position_x;
	this->position_y = position_y;
	this->queenheight = queenheight;
	this->queenwidth = queenwidth;
	srand((unsigned)time(NULL));
	monster_x1 = rand() % 1300;
	monster_y1 = rand() % 700;
	monster_x2 = rand() % 1300;
	monster_y2 = rand() % 700;
	monster_x3 = rand() % 1300;
	monster_y3 = rand() % 700;
	skill_x = rand() % 1300;
	skill_y = rand() % 700;
	if (collision(position_x, position_y, queenheight, queenwidth, 1) == 1)
	{
		monster_x1 = windowWidth - monsterWidth;
		monster_y1 = windowHeight - monsterHeight;
	}
	if (collision(position_x, position_y, queenheight, queenwidth, 2) == 1)
	{
		monster_x2 = windowWidth - monsterWidth;
		monster_y2 = 0;
	}
	if (collision(position_x, position_y, queenheight, queenwidth, 3) == 1)
	{
		monster_x3 = 0;
		monster_y3 = windowHeight - monsterHeight;
	}
	dx1 = rand() % 10 + 1;
	dy1 = rand() % 10 + 1;
	dx2 = rand() % 10 + 1;
	dy2 = rand() % 10 + 1;
}
//水平移动
void autosprite::horizontal_move()
{
	monster_x1 -= dx1;
}
//生成对象测试
void autosprite::test()
{
	monster_x1 = monster_x1;
	monster_y1 = monster_y1;
}
//随机移动+躲避移动
void autosprite::random_move(float position_Lx, float position_Ly)
{
	float x = position_Lx, y = position_Ly;
	float k1 = (y - skill_y) / (x - skill_x);
	if (((skill_x - position_Lx)*(skill_x - position_Lx) + (skill_y - position_Ly)*(skill_y - position_Ly)) <= distance2*distance2)
		skillspeed = 5;//变速
	if (((skill_x - position_Lx)*(skill_x - position_Lx) + (skill_y - position_Ly)*(skill_y - position_Ly)) <= distance3*distance3)
		skillspeed = 6;//变速
	if (((skill_x - position_Lx)*(skill_x - position_Lx) + (skill_y - position_Ly)*(skill_y - position_Ly)) <= distance1*distance1)
	{
		if (x >= skill_x)
		{
			if (k1 >= 1)
			{
				skill_x -= skillspeed / k1;
				skill_y -= skillspeed;
			}
			else if (k1 <= -1)
			{
				skill_x -= -skillspeed / k1;
				skill_y -= -skillspeed;
			}
			else
			{
				skill_x -= skillspeed;
				skill_y -= skillspeed * k1;
			}
			if (x < skill_x)
			{
				skill_x = x;
				skill_y = y;
			}
		}
		else
		{
			if (k1 >= 1)
			{
				skill_x += skillspeed / k1;
				skill_y += skillspeed;
			}
			else if (k1 <= -1)
			{
				skill_x += -skillspeed / k1;
				skill_y += -skillspeed;
			}
			else
			{
				skill_x += skillspeed;
				skill_y += skillspeed * k1;
				if (x > skill_x)
				{
					skill_x = x;
					skill_y = y;
				}
			}
		}
		if (skill_x < safe_distance)
			skill_x = windowWidth - monsterWidth - safe_distance;
		if (skill_x > windowWidth - monsterWidth - safe_distance)
			skill_x = 0;
		if (skill_y < safe_distance)
			skill_y = windowHeight - monsterHeight - safe_distance;
		if (skill_y > windowHeight - monsterHeight - safe_distance)
			skill_y = 0;
		dx1 *= -1;
		dy1 *= -1;
	}
	else
	{
		skill_x += dx1;
		skill_y += dy1;
		if (skill_x > windowWidth - monsterWidth || skill_x < 0)
			dx1 *= -1;
		if (skill_y > windowHeight - monsterHeight || skill_y < 0)
			dy1 *= -1;
	}


}
//绘制对象位置
void autosprite::drawImageScale(int i)
{
	switch (i)
	{
		MONSTERPAINT(1);
		MONSTERPAINT(2);
		MONSTERPAINT(3);
	}
}
//绘制技能对象的位置
void autosprite::drawskill()
{
	putImageTransparent(&monster, skill_x, skill_y, monsterWidth, monsterHeight, WHITE);
}
//追踪移动
void autosprite::chasemove(float position_Lx, float position_Ly, int id)
{
	float x, y, k1;
	switch (id)
	{
		MOVE(1);
		MOVE(2);
		MOVE(3);
	}

}
//碰撞检测
int autosprite::collision(float x, float y, int height, int width, int id)
{
	int c = 1;
	switch (id)
	{
		COLLISION(1)
			COLLISION(2)
			COLLISION(3)
	case 4:
		if (skill_x <= x && skill_x + monsterWidth >= x)												\
		{																											\
			if (skill_y >= y && skill_y <= y + height)return c;											\
				if (skill_y <= y && skill_y + monsterHeight >= y)return c;									\
		}																											\
		else																										\
				{																											\
			if (skill_x >= x && x + width >= skill_x)													\
			{																										\
				if (skill_y >= y && skill_y <= y + height)return c;										\
					if (skill_y <= y && skill_y + monsterHeight >= y)return c;								\
			}																										\
				}																											\
			break;
	}
	c = 0;
	return c;
}



