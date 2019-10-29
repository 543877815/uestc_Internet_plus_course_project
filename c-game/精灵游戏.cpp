#include "acllib.h"
#include "autosprite.h"
#include "avoidsprites.h"
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#define CASE(NAME,INDEX)															   \
    case INDEX:																		   \
	putImageScale(&NAME##INDEX, NAME##_x, NAME##_y, NAME##Width, NAME##Height);        \
	break;
const int protect_width = 250, protect_height = 250, protect_position_x = -protect_width, protect_position_y = -protect_height;												//记录盾牌技能的宽高和隐藏的位置
float position_snow_x = -300, position_snow_y = -300, snowclick_x, snowclick_y, magicclick_x = -500, magicclick_y = -500;													//记录雪花技能和魔法阵技能隐藏位置
float position_Lx = 0, position_Ly = 0, position_Rx = -50, position_Ry = -50, temp_x, temp_y, tempsnow_x;																	//记录普通攻击和用户精灵的位置
const int WindowWidth = 1400, WindowHeight = 800, monsterWidth = 60, monsterHeight = 60, queenWidth = 100, queenHeight = 100;												//生成的屏幕宽高、用户精灵和怪物精灵的宽高
int speed = 44, speed_Cooling_time = 0, shield_Cooling_time = 0, magic_Cooling_time = 0, magic_matrix_times = 3, hand_sword_times = 5, flash_move_times = 10;               //记录用户精灵移动的速度，记录技能倒计时和剩余使用次数																															
float  Lmouse_x, Lmouse_y, Rmouse_x, Rmouse_y, Mmouse_x, Mmouse_y;																											//记录鼠标左、右、中键点击后记录的位置
const int  NA_Width = 20, NA_Height = 20, snow_attack_width = 75, snow_attack_height = 75, magicWidth = 500, magicHeight = 500;												//记录普通攻击图片的宽高，F3攻击技能的宽高，F4攻击技能的宽高
const int upHeight = 70, upWidth = 70, up_x = 1300, up_y = 700;																												//记录加速技能栏的位置和宽高
const int shieldHeight = 70, shieldWidth = 70, shield_x = 1200, shield_y = 700;																								//记录盾牌技能栏的位置和宽高
const int magic_matrixHeight = 70, magic_matrixWidth = 70, magic_matrix_x = 1100, magic_matrix_y = 700;																		//记录魔法阵技能栏的位置和宽高
const int hand_swordHeight = 70, hand_swordWidth = 70, hand_sword_x = 1000, hand_sword_y = 700;																				//记录雪花技能栏的位置和宽高
const int flash_moveHeight = 70, flash_moveWidth = 70, flash_move_x = 900, flash_move_y = 700;																				//记录闪现技能栏的位置和宽高
const int skillWidth = 50, skillHeight = 50;																															    //记录躲避精灵的宽高
bool shield_judge = false, speed_counttime, shield_counttime, snowattack_counttime, snowattack_judge = false, magic_matrix_judge = false;									//记录键盘事件转到鼠标事件的判断
bool GAVEOVER_judge = false, DELETE_judge = false;																															//终结判断
const int move_speed = 10;																																					//记录控制精灵移动速度
int score = 0, level = 1, level2Num = 20, level3Num = 40;																													//记录得分和等级,判断等级2和3所需的得分
const int buildpoint_MAX1 = 50;//生成精灵点1
int buildpoint1 = 0;//已经生成的精灵数目1
autosprite *sprites1[buildpoint_MAX1] = { 0 };

const int buildpoint_MAX2 = 50;//生成精灵点2
int buildpoint2 = 0;//已经生成的精灵数目2
autosprite *sprites2[buildpoint_MAX2] = { 0 };

const int buildpoint_MAX3 = 50;//生成精灵点3
int buildpoint3 = 0;//已经生成的精灵数目3
autosprite *sprites3[buildpoint_MAX3] = { 0 };

const int horizon_Max = 50;//水平精灵
int buildhorizon = 0;//水平精灵
autosprite *sprites_of_horizon[horizon_Max] = { 0 };

const int skill1_Max = 2;//技能一
int skill1_Num = 0;
autosprite *skill_1[skill1_Max] = { 0 };

const int skill2_Max = 1;//技能二
int skill2_Num = 0;
autosprite *skill_2[skill2_Max] = { 0 };

const int skill3_Max = 1;//技能三
int skill3_Num = 0;
autosprite *skill_3[skill3_Max] = { 0 };

const char *name = "monster.jpg";
const char *skill1_name = "skill_hand_sword.jpg";
const char *skill2_name = "skill_magic_matrix.jpg";
const char *skill3_name = "skill_flash_move.jpg";
ACL_Sound GAMEOVER;
ACL_Sound getskill;
ACL_Sound Magic_matrix;
ACL_Sound Hand_sword;
ACL_Sound Speedup;
ACL_Sound Shield;
ACL_Sound Attack;
ACL_Sound Attackhit;
ACL_Sound steadymove;
ACL_Image protect;
ACL_Image monster;
ACL_Image snowqueen;
ACL_Image normal_attack;
ACL_Image snow_attack;
ACL_Image speedup;
ACL_Image up;
ACL_Image up1;
ACL_Image up2;
ACL_Image up3;
ACL_Image up4;
ACL_Image up5;
ACL_Image shield;
ACL_Image shield1;
ACL_Image shield2;
ACL_Image shield3;
ACL_Image shield4;
ACL_Image shield5;
ACL_Image shield6;
ACL_Image shield7;
ACL_Image shield8;
ACL_Image shield9;
ACL_Image shield10;
ACL_Image flash_move0;
ACL_Image flash_move1;
ACL_Image flash_move2;
ACL_Image flash_move3;
ACL_Image flash_move4;
ACL_Image flash_move5;
ACL_Image flash_move6;
ACL_Image flash_move7;
ACL_Image flash_move8;
ACL_Image flash_move9;
ACL_Image flash_move10;
ACL_Image hand_sword0;
ACL_Image hand_sword1;
ACL_Image hand_sword2;
ACL_Image hand_sword3;
ACL_Image hand_sword4;
ACL_Image hand_sword5;
ACL_Image magic_matrix;
ACL_Image magic_matrix0;
ACL_Image magic_matrix1;
ACL_Image magic_matrix2;
ACL_Image magic_matrix3;
ACL_Image matrix_attack;
ACL_Image skill1;
ACL_Image skill2;
ACL_Image skill3;
void timerEvent(int id);
void mouseEvent(int x, int y, int button, int event);
void keyboardEvent(int key, int event);
void mouseMove();
void timeEvent(int id);
void attack();
void snowattack();
int Setup()
{
	initWindow("宫爆LOL", 0, 0, WindowWidth, WindowHeight);
	loadImage("normal_attack.jpg", &normal_attack);
	loadImage("snowattack.jpg", &snow_attack);
	loadImage("monster.jpg", &monster);
	loadImage("snowqueen.jpg", &snowqueen);
	loadImage("speedup.jpg", &speedup);
	loadImage("protect.jpg", &protect);
	loadImage("up.jpg", &up);
	loadImage("up1.jpg", &up1);
	loadImage("up2.jpg", &up2);
	loadImage("up3.jpg", &up3);
	loadImage("up4.jpg", &up4);
	loadImage("up5.jpg", &up5);
	loadImage("shield.jpg", &shield);
	loadImage("shield1.jpg", &shield1);
	loadImage("shield2.jpg", &shield2);
	loadImage("shield3.jpg", &shield3);
	loadImage("shield4.jpg", &shield4);
	loadImage("shield5.jpg", &shield5);
	loadImage("shield6.jpg", &shield6);
	loadImage("shield7.jpg", &shield7);
	loadImage("shield8.jpg", &shield8);
	loadImage("shield9.jpg", &shield9);
	loadImage("shield10.jpg", &shield10);
	loadImage("flash_move0.jpg", &flash_move0);
	loadImage("flash_move1.jpg", &flash_move1);
	loadImage("flash_move2.jpg", &flash_move2);
	loadImage("flash_move3.jpg", &flash_move3);
	loadImage("flash_move4.jpg", &flash_move4);
	loadImage("flash_move5.jpg", &flash_move5);
	loadImage("flash_move6.jpg", &flash_move6);
	loadImage("flash_move7.jpg", &flash_move7);
	loadImage("flash_move8.jpg", &flash_move8);
	loadImage("flash_move9.jpg", &flash_move9);
	loadImage("flash_move10.jpg", &flash_move10);
	loadImage("hand_sword0.jpg", &hand_sword0);
	loadImage("hand_sword1.jpg", &hand_sword1);
	loadImage("hand_sword2.jpg", &hand_sword2);
	loadImage("hand_sword3.jpg", &hand_sword3);
	loadImage("hand_sword4.jpg", &hand_sword4);
	loadImage("hand_sword5.jpg", &hand_sword5);
	loadImage("magic_matrix.jpg", &magic_matrix);
	loadImage("magic_matrix0.jpg", &magic_matrix0);
	loadImage("magic_matrix1.jpg", &magic_matrix1);
	loadImage("magic_matrix2.jpg", &magic_matrix2);
	loadImage("magic_matrix3.jpg", &magic_matrix3);
	loadImage("skill_hand_sword.jpg", &skill1);
	loadImage("skill_magic_matrix.jpg", &skill2);
	loadImage("magic_matrix3.jpg", &skill3);
	loadSound("speedup.mp3", &Speedup);
	loadSound("shield.mp3", &Shield);
	loadSound("Attackbefore.mp3", &Attack);
	loadSound("steadymove.mp3", &steadymove);
	loadSound("attackhit.wav", &Attackhit);
	loadSound("hand_sword.mp3", &Hand_sword);
	loadSound("Magic_matrix.mp3", &Magic_matrix);
	loadSound("getskill.mp3", &getskill);
	loadSound("GAMEOVER.mp3", &GAMEOVER);
	registerMouseEvent(mouseEvent);
	registerTimerEvent(timeEvent);
	registerKeyboardEvent(keyboardEvent);
	startTimer(10, 1000);//第一个生成点
	startTimer(11, 50);
	startTimer(12, 1000);//第一个技能
	startTimer(13, 50);
	startTimer(14, 3000);//第二个技能
	startTimer(15, 50);
	return 0;
}
void keyboardEvent(int key, int event)
{
	if (event != KEY_DOWN)
		return;
	switch (key)
	{
	case VK_F1:																		//F1为加速技能
		speed_counttime = true;
		if (speed_counttime == true && speed_Cooling_time == 0)
		{
			speed = 15;
			playSound(Speedup, 0);
			speed_Cooling_time = 5;//技能1冷却时间
			startTimer(3, 2000);
		}
		break;
	case VK_F2:																		//F2为盾牌技能
		shield_counttime = true;
		if (shield_counttime == true && shield_Cooling_time == 0)
		{
			shield_judge = true;
			playSound(Shield, 0);
			shield_Cooling_time = 10;												//技能2冷却时间
			startTimer(4, 5000);
		}
		break;
	case VK_F3:
		magic_matrix_judge = false;													//F3为攻击技能
		if (hand_sword_times > 0)
		{
			snowattack_judge = true;
		}
		break;
	case VK_F4:																		//F4为范围技能
		snowattack_judge = false;
		if (magic_matrix_times > 0)
		{
			magic_matrix_judge = true;
			magic_Cooling_time = 3;
		}
		break;
	}
}
void mouseEvent(int x, int y, int button, int event)
{
	if (event != BUTTON_DOWN)
		return;
	switch (button)
	{
	case LEFT_BUTTON:
	{
		if (true == snowattack_judge&&magic_matrix_judge == false)//F3技能判断																	
		{
			magic_matrix_judge = false;
			snowattack_judge = false;
			if (hand_sword_times > 0)
			{
				snowclick_x = x;
				snowclick_y = y;
				tempsnow_x = position_Lx + 100;
				position_snow_x = position_Lx + 100;
				position_snow_y = position_Ly;
				hand_sword_times--;
				playSound(Hand_sword, 0);
				startTimer(2, 10);
				break;
			}
		}
		if (true == magic_matrix_judge&&snowattack_judge == false)
		{
			magic_matrix_judge = false;
			snowattack_judge = false;
			if (magic_matrix_times > 0)
			{
				magicclick_x = x;
				magicclick_y = y;
				playSound(Magic_matrix, 0);
				magic_matrix_times--;
				startTimer(5, 1000);
				break;
			}
		}
		Lmouse_x = x;//控制控制精灵移动
		Lmouse_y = y;
		startTimer(0, speed);   //speed
		break;
		//}
	}
	case RIGHT_BUTTON:																						//控制炮弹发出
		playSound(Attack, 0);
		Rmouse_x = x;
		Rmouse_y = y;
		temp_x = position_Lx + 100;
		position_Rx = position_Lx + 100;
		position_Ry = position_Ly;
		startTimer(1, 10);
		break;
	case MIDDLE_BUTTON:	//控制精灵瞬移
		if (flash_move_times > 0)
		{
			playSound(steadymove, 0);
			Mmouse_x = x;
			Mmouse_y = y;
			position_Lx = x;
			position_Ly = y;
			Lmouse_x = x;
			Lmouse_y = y;
			flash_move_times--;
			startTimer(102, 10000);
			break;
		}
		else
			break;
	default:
		break;
	}
}
void timeEvent(int id)
{
	int i, j, record1 = 0, record2 = 0, record3 = 0;
	int record_skill1 = 0, record_skill2 = 0, record_skill3 = 0;
	beginPaint();
	switch (id)
	{
	case 0:
		mouseMove();
		break;
	case 1:
		attack();
		break;
	case 2:
		snowattack();
		startTimer(102, 1000);
		break;
	case 3:
		speed_counttime = false;
		if (false == speed_counttime)
		{
			speed_Cooling_time = 5;
			speed = 40;
			cancelTimer(3);
			startTimer(100, 1000);
		}
		break;
	case 4:
		shield_counttime = false;
		if (false == shield_counttime)
		{
			shield_judge = false;
			cancelTimer(4);
			shield_Cooling_time = 10;
			startTimer(101, 1000);
		}
		break;
	case 5:
		magic_Cooling_time--;
		if (0 == magic_Cooling_time)
		{
			cancelTimer(5);
			magicclick_x = -magicWidth;
			magicclick_y = -magicHeight;
		}
		break;
	case 6:
		if (buildpoint3 < buildpoint_MAX3)//生成點3
		{
			sprites3[buildpoint3] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
			if (sprites3[buildpoint3] == NULL)
			{
				break;
			}
			++buildpoint3;
		}
		for (int g = 0; g < buildpoint3; g++)
		{
			if (sprites3[g] == NULL)
			{
				record3 = g;
			}
		}
		if (sprites3[record3] == NULL)
			sprites3[record3] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
		break;
	case 7:
		for (j = 0; j < buildpoint3; ++j)//移動函數
		{
			if (sprites3[j] == NULL)continue;
			sprites3[j]->chasemove(position_Lx, position_Ly, 3);
		}
		break;
	case 8:
		if (buildpoint2 < buildpoint_MAX2)//生成點2
		{
			sprites2[buildpoint2] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
			if (sprites2[buildpoint2] == NULL)
			{
				break;
			}
			++buildpoint2;
		}
		for (int g = 0; g < buildpoint2; g++)
		{
			if (sprites2[g] == NULL)
			{
				record2 = g;
			}
		}
		if (sprites2[record2] == NULL)
			sprites2[record2] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
		break;
	case 9:
		for (j = 0; j < buildpoint2; ++j)//移動函數
		{
			if (sprites2[j] == NULL)continue;
			sprites2[j]->chasemove(position_Lx, position_Ly, 2);
		}
		break;
	case 10:
		if (buildpoint1 < buildpoint_MAX1)//生成点1
		{
			sprites1[buildpoint1] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
			if (sprites1[buildpoint1] == NULL)
			{
				break;
			}
			++buildpoint1;
		}
		for (int i = 0; i < buildpoint1; i++)
		{
			if (sprites1[i] == NULL)
			{
				record1 = i;
			}
		}
		if (sprites1[record1] == NULL)
			sprites1[record1] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
		break;
	case 11:
		for (i = 0; i < buildpoint1; ++i)//移動函數
		{
			if (sprites1[i] == NULL)continue;
			sprites1[i]->chasemove(position_Lx, position_Ly, 1);
		}
		break;
	case 12:
		if (skill1_Num < skill1_Max)//技能1
		{
			skill_1[skill1_Num] = new autosprite(skill1_name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
			if (skill_1[skill1_Num] == NULL)
			{
				break;
			}
			++skill1_Num;
		}
		for (int i = 0; i < skill1_Num; i++)
		{
			if (skill_1[i] == NULL)
			{
				record_skill1 = i;
			}
		}
		if (skill_1[record_skill1] == NULL)
			skill_1[record_skill1] = new autosprite(skill1_name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
		break;
	case 13:
		for (i = 0; i < skill1_Num; ++i)//随机移動函數
		{
			if (skill_1[i] == NULL)continue;
			skill_1[i]->random_move(position_Lx, position_Ly);
		}
		break;
	case 14:
		if (skill2_Num < skill2_Max)//技能2
		{
			skill_2[skill2_Num] = new autosprite(skill2_name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
			if (skill_2[skill2_Num] == NULL)
			{
				break;
			}
			++skill2_Num;
		}
		for (int i = 0; i < skill2_Num; i++)
		{
			if (skill_2[i] == NULL)
			{
				record_skill1 = i;
			}
		}
		if (skill_2[record_skill1] == NULL)
			skill_2[record_skill1] = new autosprite(skill2_name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
		break;
	case 15:
		for (i = 0; i < skill2_Num; ++i)//随机移動函數
		{
			if (skill_2[i] == NULL)continue;
			skill_2[i]->random_move(position_Lx, position_Ly);
		}
		break;
	case 100:
		speed_Cooling_time--;
		if (speed_Cooling_time == 0)
			cancelTimer(100);
		break;
	case 101:
		shield_Cooling_time--;
		if (shield_Cooling_time == 0)
			cancelTimer(101);
		break;
	case 102:
		if (flash_move_times < 10)
			flash_move_times++;
		break;
	}
	clearDevice();
	if (score >= level2Num && score < level3Num)
	{
		level = 2;
		startTimer(8, 1300);//第二个生成点
		startTimer(9, 50);
	}
	if (score >= level3Num)
	{
		level = 3;
		startTimer(6, 1800);//第三个生成点
		startTimer(7, 50);
	}
	char s[20];											//进行得分显示
	char s1[20];										//进行得分显示
	setPenColor(BLACK);
	setTextSize(20);
	sprintf_s(s, "score:%d", score);
	paintText(20, 20, s);
	sprintf_s(s1, "level:%d", level);
	paintText(20, 40, s1);
	//第一个精灵随机精灵
	for (int i = 0; i < buildpoint_MAX1; ++i)   //进行普通攻击碰撞检验
	{
		if (sprites1[i] == NULL)continue;
		if (sprites1[i]->collision(position_Rx, position_Ry, NA_Height, NA_Width, 1) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			position_Rx = -NA_Width;
			position_Ry = -NA_Height;
			cancelTimer(1);
			playSound(Attackhit, 0);
			delete sprites1[i];
			sprites1[i] = NULL;
		}
	}
	for (int i = 0; i < buildpoint_MAX1; ++i)   //进行F3技能碰撞检验
	{
		if (sprites1[i] == NULL)continue;
		if (sprites1[i]->collision(position_snow_x, position_snow_y, snow_attack_height, snow_attack_width, 1) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites1[i];
			sprites1[i] = NULL;
		}
	}
	for (int i = 0; i < buildpoint_MAX1; ++i)   //进行F4技能碰撞检验
	{
		if (sprites1[i] == NULL)continue;
		if (sprites1[i]->collision(magicclick_x - magicWidth / 2, magicclick_y - magicHeight / 2, magicWidth, magicHeight, 1) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites1[i];
			sprites1[i] = NULL;
		}
	}
	if (shield_judge == true)		//绘制盾牌位置，并对盾牌碰撞进行检验
	{
		putImageTransparent(&protect, position_Lx - 75, position_Ly - 75, protect_width, protect_height, WHITE);
		for (int i = 0; i < buildpoint_MAX1; ++i)
		{
			if (sprites1[i] == NULL)continue;
			if (sprites1[i]->collision(position_Lx - 75, position_Ly - 75, protect_height, protect_width, 1) == 1)
			{
				if (false == GAVEOVER_judge)
					score++;
				delete sprites1[i];
				sprites1[i] = NULL;
			}
		}
	}
	for (int i = 0; i < buildpoint1; ++i)  //绘制生成点1的控制精灵
	{
		if (sprites1[i] == NULL)continue;
		sprites1[i]->drawImageScale(1);
	}
	//第二个精灵随机精灵
	for (int j = 0; j < buildpoint_MAX2; ++j)   //进行普通攻击碰撞检验
	{
		if (sprites2[j] == NULL)continue;
		if (sprites2[j]->collision(position_Rx, position_Ry, NA_Height, NA_Width, 2) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			position_Rx = -NA_Width;
			position_Ry = -NA_Height;
			cancelTimer(1);
			playSound(Attackhit, 0);
			delete sprites2[j];
			sprites2[j] = NULL;
		}
	}
	for (int j = 0; j < buildpoint_MAX2; ++j)//进行F3技能碰撞检验
	{
		if (sprites2[j] == NULL)continue;
		if (sprites2[j]->collision(position_snow_x, position_snow_y, snow_attack_height, snow_attack_width, 2) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites2[j];
			sprites2[j] = NULL;
		}
	}
	for (int j = 0; j < buildpoint_MAX2; ++j)   //进行F4技能碰撞检验
	{
		if (sprites2[j] == NULL)continue;
		if (sprites2[j]->collision(magicclick_x - magicWidth / 2, magicclick_y - magicHeight / 2, magicWidth, magicHeight, 2) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites2[j];
			sprites2[j] = NULL;
		}
	}
	if (shield_judge == true)		//绘制盾牌位置，并对盾牌碰撞进行检验
	{
		for (int j = 0; j < buildpoint_MAX2; ++j)
		{
			if (sprites2[j] == NULL)continue;
			if (sprites2[j]->collision(position_Lx - 75, position_Ly - 75, protect_height, protect_width, 2) == 1)
			{
				if (false == GAVEOVER_judge)
					score++;
				delete sprites2[j];
				sprites2[j] = NULL;
			}
		}
	}
	for (int j = 0; j < buildpoint2; ++j)  //绘制生成点2的控制精灵
	{
		if (sprites2[j] == NULL)continue;
		sprites2[j]->drawImageScale(2);
	}
	//第三个精灵随机精灵
	for (int k = 0; k < buildpoint_MAX3; ++k)   //进行普通攻击碰撞检验
	{
		if (sprites3[k] == NULL)continue;
		if (sprites3[k]->collision(position_Rx, position_Ry, NA_Height, NA_Width, 3) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			position_Rx = -NA_Width;
			position_Ry = -NA_Height;
			cancelTimer(1);
			playSound(Attackhit, 0);
			delete sprites3[k];
			sprites3[k] = NULL;
		}
	}
	for (int k = 0; k < buildpoint_MAX3; ++k)//进行F3技能碰撞检验
	{
		if (sprites3[k] == NULL)continue;
		if (sprites3[k]->collision(position_snow_x, position_snow_y, snow_attack_height, snow_attack_width, 3) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites3[k];
			sprites3[k] = NULL;
		}
	}
	for (int k = 0; k < buildpoint_MAX3; ++k)   //进行F4技能碰撞检验
	{
		if (sprites3[k] == NULL)continue;
		if (sprites3[k]->collision(magicclick_x - magicWidth / 2, magicclick_y - magicHeight / 2, magicWidth, magicHeight, 3) == 1)
		{
			if (false == GAVEOVER_judge)
				score++;
			delete sprites3[k];
			sprites3[k] = NULL;
		}
	}
	if (shield_judge == true)		//绘制盾牌位置，并对盾牌碰撞进行检验
	{


		for (int j = 0; j < buildpoint_MAX3; ++j)
		{
			if (sprites3[j] == NULL)continue;
			if (sprites3[j]->collision(position_Lx - 75, position_Ly - 75, protect_height, protect_width, 3) == 1)
			{
				if (false == GAVEOVER_judge)
					score++;
				delete sprites3[j];
				sprites3[j] = NULL;
			}
		}
	}
	for (int k = 0; k < buildpoint3; ++k)  //绘制生成点3的控制精灵
	{
		if (sprites3[k] == NULL)continue;
		sprites3[k]->drawImageScale(3);
	}
	//第一个技能
	for (int i = 0; i < skill1_Max; ++i)
	{
		if (skill_1[i] == NULL)continue;
		if (skill_1[i]->collision(position_Lx, position_Ly, queenHeight, queenWidth, 4) == 1)
		{
			playSound(getskill, 0);
			if (hand_sword_times < 5)
				hand_sword_times++;
			delete skill_1[i];
			skill_1[i] = NULL;
		}
	}
	for (int i = 0; i < skill1_Num; ++i)	//绘制技能一
	{
		if (skill_1[i] == NULL)continue;
		skill_1[i]->drawskill();
	}
	//第二个技能
	for (int j = 0; j < skill2_Max; ++j)
	{
		if (skill_2[j] == NULL)continue;
		if (skill_2[j]->collision(position_Lx, position_Ly, queenHeight, queenWidth, 4) == 1)
		{
			playSound(getskill, 0);
			if (magic_matrix_times < 3)
				magic_matrix_times++;
			delete skill_2[j];
			skill_2[j] = NULL;
		}
	}
	for (int i = 0; i < skill2_Num; ++i)	//绘制技能二
	{
		if (skill_2[i] == NULL)continue;
		skill_2[i]->drawskill();
	}
	//终结判断
	for (int i = 0; i < buildpoint1; ++i)
	{
		if (sprites1[i] == NULL)continue;
		if (sprites1[i]->collision(position_Lx, position_Ly, queenHeight, queenWidth, 1) == 1)
		{
			GAVEOVER_judge = true;
		}
	}
	for (int i = 0; i < buildpoint2; ++i)
	{
		if (sprites2[i] == NULL)continue;
		if (sprites2[i]->collision(position_Lx, position_Ly, queenHeight, queenWidth, 2) == 1)
		{
			GAVEOVER_judge = true;
		}
	}
	for (int i = 0; i < buildpoint3; ++i)
	{
		if (sprites3[i] == NULL)continue;
		if (sprites3[i]->collision(position_Lx, position_Ly, queenHeight, queenWidth, 3) == 1)
		{
			GAVEOVER_judge = true;
		}
	}
	if (magic_Cooling_time != 0)
		putImageTransparent(&magic_matrix, magicclick_x - magicWidth / 2, magicclick_y - magicHeight / 2, magicWidth, magicHeight, WHITE);  //绘制攻击技能F4
	putImageTransparent(&snow_attack, position_snow_x, position_snow_y, snow_attack_width, snow_attack_height, WHITE);						//绘制攻击技能F3
	putImageTransparent(&snowqueen, position_Lx, position_Ly, queenWidth, queenHeight, WHITE);												//绘制控制精灵
	putImageTransparent(&normal_attack, position_Rx, position_Ry, NA_Width, NA_Height, WHITE);												//绘制普通攻击
	putImageTransparent(&up, up_x, up_y, upWidth, upHeight, WHITE);																			//绘制加速技能面板
	putImageTransparent(&shield, shield_x, shield_y, shieldWidth, shieldHeight, WHITE);														//绘制盾牌技能面板
	if (speed == 15)//当加速时绘制头上加速图像
		putImageTransparent(&speedup, position_Lx, position_Ly - 50, 100, 50, WHITE);
	//绘制范围攻击技能图片的次数
	switch (magic_matrix_times)
	{
		CASE(magic_matrix, 0)
			CASE(magic_matrix, 1)
			CASE(magic_matrix, 2)
			CASE(magic_matrix, 3)
	}
	//绘制闪现技能图标的次数
	switch (flash_move_times)
	{
		CASE(flash_move, 10)
			CASE(flash_move, 9)
			CASE(flash_move, 8)
			CASE(flash_move, 7)
			CASE(flash_move, 6)
			CASE(flash_move, 5)
			CASE(flash_move, 4)
			CASE(flash_move, 3)
			CASE(flash_move, 2)
			CASE(flash_move, 1)
			CASE(flash_move, 0)

	}
	//绘制雪花攻击图标的次数
	switch (hand_sword_times)
	{
		CASE(hand_sword, 5)
			CASE(hand_sword, 4)
			CASE(hand_sword, 3)
			CASE(hand_sword, 2)
			CASE(hand_sword, 1)
			CASE(hand_sword, 0)
	}
	//绘制加速技能的倒计时
	switch (speed_Cooling_time)
	{
		CASE(up, 5)
			CASE(up, 4)
			CASE(up, 3)
			CASE(up, 2)
			CASE(up, 1)
	default:
		break;
	}
	//绘制盾的倒计时
	switch (shield_Cooling_time)
	{
		CASE(shield, 1)
			CASE(shield, 2)
			CASE(shield, 3)
			CASE(shield, 4)
			CASE(shield, 5)
			CASE(shield, 6)
			CASE(shield, 7)
			CASE(shield, 8)
			CASE(shield, 9)
			CASE(shield, 10)
	}
	//终结删除和最终得分显示
	if (true == GAVEOVER_judge)
	{
		for (int i = 6; i < 16; i++)
			cancelTimer(i);
		playSound(GAMEOVER, 0);
		char s3[50];
		char s4[50];
		setPenColor(RED);
		setTextSize(200);
		sprintf_s(s3, "GAME OVER! ");
		sprintf_s(s4, "YOUR SCORE IS : %d", score);
		paintText(200, 200, s3);
		setTextSize(75);
		paintText(350, 400, s4);
	}
	endPaint();
}
void mouseMove()//鼠标控制控制精灵的移动
{
	float x = Lmouse_x, y = Lmouse_y;
	float k1 = (y - position_Ly) / (x - position_Lx);
	if (x >= position_Lx)
	{
		if (k1 >= 1)//1111111111111111
		{
			position_Lx += move_speed / k1;
			position_Ly += move_speed;
		}
		else if (k1 <= -1)//4444444444444444444
		{
			position_Lx += -move_speed / k1;
			position_Ly += -move_speed;
		}
		else//22222222222222222  3333333333333333
		{
			position_Lx += move_speed;
			position_Ly += move_speed * k1;
		}
		if (x < position_Lx)
		{
			position_Lx = x;
			position_Ly = y;
			cancelTimer(0);
		}
	}
	else
	{
		if (k1 >= 1)//5555555555555555555
		{
			position_Lx -= move_speed / k1;
			position_Ly -= move_speed;
		}
		else if (k1 <= -1)//888888888888888888888
		{
			position_Lx -= -move_speed / k1;
			position_Ly -= -move_speed;
		}
		else//555555555555555555555   666666666666666666666666
		{
			position_Lx -= move_speed;
			position_Ly -= move_speed * k1;
			if (x > position_Lx)
			{
				position_Lx = x;
				position_Ly = y;
				cancelTimer(0);
			}
		}
	}
}
void attack()//控制移动的函数不合并的原因是每个元素的全局变量不同
{
	float x = Rmouse_x, y = Rmouse_y;
	float k1 = (y - position_Ry) / (x - position_Rx);
	if (x >= temp_x)
	{
		if (k1 >= 1)//1111111111111111
		{
			position_Rx += 10 / k1;
			position_Ry += 10;
		}
		else if (k1 <= -1)//4444444444444444444
		{
			position_Rx += -10 / k1;
			position_Ry += -10;
		}
		else//22222222222222222  3333333333333333
		{
			position_Rx += 10;
			position_Ry += 10 * k1;
		}
	}
	else
	{
		if (k1 >= 1)//5555555555555555555
		{
			position_Rx -= 10 / k1;
			position_Ry -= 10;
		}
		else if (k1 <= -1)//888888888888888888888
		{
			position_Rx -= -10 / k1;
			position_Ry -= -10;
		}
		else//555555555555555555555       666666666666666666666666
		{
			position_Rx -= 10;
			position_Ry -= 10 * k1;
		}
	}
	if (position_Rx >= WindowWidth + queenWidth || position_Ry >= WindowHeight + queenHeight || position_Rx <= -NA_Width || position_Ry <= -NA_Height)
	{
		position_Rx = -NA_Width;
		position_Ry = -NA_Height;
		cancelTimer(1);
	}
}
void snowattack()//F3
{
	float x = snowclick_x, y = snowclick_y;
	float k1 = (y - position_snow_y) / (x - position_snow_x);
	if (x >= tempsnow_x)
	{
		if (k1 >= 1)//1111111111111111
		{
			position_snow_x += 10 / k1;
			position_snow_y += 10;
		}
		else if (k1 <= -1)//4444444444444444444
		{
			position_snow_x += -10 / k1;
			position_snow_y += -10;
		}
		else//22222222222222222  3333333333333333
		{
			position_snow_x += 10;
			position_snow_y += 10 * k1;
		}
	}
	else
	{
		if (k1 >= 1)//5555555555555555555
		{
			position_snow_x -= 10 / k1;
			position_snow_y -= 10;
		}
		else if (k1 <= -1)//888888888888888888888
		{
			position_snow_x -= -10 / k1;
			position_snow_y -= -10;
		}
		else//555555555555555555555       666666666666666666666666
		{
			position_snow_x -= 10;
			position_snow_y -= 10 * k1;
		}
	}
	if (position_snow_x >= WindowWidth || position_snow_y >= WindowHeight || position_snow_x <= -snow_attack_width || position_snow_y <= -snow_attack_height)
	{
		position_snow_x = -snow_attack_width;
		position_snow_y = -snow_attack_height;
		cancelTimer(2);
	}
}


//水平精灵
//for (int j = 0; j < horizon_Max; ++j)
//{
//	if (sprites_of_horizon[j] == NULL)continue;
//	if (sprites_of_horizon[j]->collision(position_snow_x, position_snow_y, snow_attack_height, snow_attack_width) == 1)
//	{
//		score++;
//		delete sprites_of_horizon[j];
//		sprites_of_horizon[j] = NULL;
//	}
//}
//for (int j = 0; j < horizon_Max; ++j)
//{
//	if (sprites_of_horizon[j] == NULL)continue;
//	if (sprites_of_horizon[j]->collision(position_Rx, position_Ry, NA_Height, NA_Width) == 1)
//	{
//		score++;
//		position_Rx = -NA_Width;
//		position_Ry = -NA_Height;
//		cancelTimer(1);
//		playSound(Attackhit, 0);
//		delete sprites_of_horizon[j];
//		sprites_of_horizon[j] = NULL;
//	}
//}
//if (shield_judge == true)
//{
//	putImageTransparent(&protect, position_Lx - 75, position_Ly - 75, protect_width, protect_height, WHITE);
//	for (int j = 0; j < horizon_Max; ++j)
//	{
//		if (sprites_of_horizon[j] == NULL)continue;
//		if (sprites_of_horizon[j]->collision(position_Lx - 75, position_Ly - 75, protect_height, protect_width) == 1)
//		{
//			score++;
//			delete sprites_of_horizon[j];
//			sprites_of_horizon[j] = NULL;
//		}
//	}
//}
//for (int j = 0; j < buildhorizon; ++j)
//{
//	if (sprites_of_horizon[j] == NULL)continue;
//	sprites_of_horizon[j]->drawImageScale();
//}
//水平精灵
/*case 8:
if (buildhorizon < horizon_Max)
{
sprites_of_horizon[buildhorizon] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
if (sprites_of_horizon[buildhorizon] == NULL)
{
break;
}
++buildhorizon;
}
for (int i = 0; i < buildhorizon; i++)
{
if (sprites_of_horizon[i] == NULL)
{
record2 = i;
}
}
if (sprites_of_horizon[record2] == NULL)
sprites_of_horizon[record2] = new autosprite(name, monsterWidth, monsterHeight, position_Lx, position_Ly, queenWidth, queenHeight);
break;
case 9:
for (i = 0; i < buildhorizon; ++i)
{
if (sprites_of_horizon[i] == NULL)continue;
sprites_of_horizon[i]->horizontal_move();
}
break;*/

//失敗的構建方法一
/*switch (snow_attack_times)
{
CASE(flash_move,5)
CASE(flash_move, 4)
CASE(flash_move, 3)
CASE(flash_move, 2)
CASE(flash_move, 1)
CASE(flash_move, 0)
}*/

//失敗的構建方法二
//ACL_Image * const ups[5] = { &up1,&up2, &up3 , &up4 , &up5 }; 
//if (1 <= speed_Cooling_time && speed_Cooling_time <= 5)
//{
//	putImageScale(ups[speed_Cooling_time], up_x, up_y, upWidth, upHeight);
//}