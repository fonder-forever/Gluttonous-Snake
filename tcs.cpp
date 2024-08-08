#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>//sleep
#include<time.h>//随机函数种子
/****************************************************
*		坐标属性
*		蛇属性
*		食物属性
*		
* 
*****************************************************/
//坐标属性
typedef struct pointXY 
{
	int x;
	int y;

}MYPOINT;
//蛇属性
struct Snake 
{
	int num;	//蛇的节数
	MYPOINT xy[100];	//蛇
	char position;

}snake;
//食物属性
struct Food
{
	MYPOINT  fdxy;	//食物的坐标
	int eatgrade;	//吃的food的分数
	int flag = 0;	//是否被吃掉
}food;
//句柄，主窗口
HWND hwnd = NULL;
//方向
enum movPosition {right=100,left=97,down=115,up=119};
/****************************************************
*		初始化蛇:  initSnake
*		画蛇:	   drawSnake
*		移动蛇:    moveSanke
*		按键处理:  keyDown
*		初始化食物:initFood
*		画食物:    drawFood
*		吃食物:    eatFood
*		撞墙:      snakeDie
*****************************************************/
void initSnake();
void drawSnake();
void moveSnake();
void keyDown();
void initFood();
void drawFood();
void eatFood();
void snakeDie();
int main()
{
	hwnd = initgraph(640,480);	//窗口大小
	setbkcolor(WHITE);		//窗口颜色白色
	
	initSnake();
	initFood();
	drawFood();
	while(1)
	{
		cleardevice();
		
		if (food.flag == 0)//没有食物时才画食物
		{
			initFood();
			drawFood();
		}
		else
		{
			drawFood();
		}
		
		drawSnake();
		moveSnake();
		eatFood();
		while (_kbhit())	// 是否有按键按下
		{
			keyDown();
		}
		Sleep(100);
	}
	//getchar();	//防止闪屏
	closegraph();
	return 0;
}
void initSnake() 
{
	//初始化前面三节
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;
	
	snake.position = right;
}
void drawSnake()
{	
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(WHITE);	//矩形边框线的颜色黑色
		setfillcolor(GREEN);	//填充颜色
		fillrectangle(snake.xy[i].x,snake.xy[i].y, snake.xy[i].x+10, snake.xy[i].y+10);
	}
}
void moveSnake()
{
	//除了第一节其他的处理
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//第一节的处理
	if (snake.xy[0].x > 630 )
			snake.xy[0].x = 10;
	if (snake.xy[0].x < 0 )
		snake.xy[0].x = 630;
	if (snake.xy[0].y > 470 )
			snake.xy[0].y = 10;
	if (snake.xy[0].y < 0 )
		snake.xy[0].y = 470;
	switch (snake.position)
	{
	
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	default:
		break;
	
	}

}
void keyDown()
{
	char userKey = 0;
	userKey = _getch();
	switch (userKey)
	{
	case right:
		if (snake.position != left)
			snake.position = right;
		break;
	case left:
		if (snake.position != right)
			snake.position = left;
		break;
	case up:
		if (snake.position != down)
			snake.position = up;
		break;
	case down:
		if (snake.position != up)
			snake.position = down;
		break;
	default:
		break;
	}

}
void initFood()
{
	srand((unsigned int)time(NULL));
		food.fdxy.x = rand()%64*10;	//10的倍数
		food.fdxy.y = rand()%46*10;
		//食物出现在蛇的身上
		for (int i = 0; i < snake.num; i++)
		{
			if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
			{
				drawFood();
				break;
			}
		}
	}
void drawFood()
{
	
	setlinecolor(WHITE);	//矩形边框线的颜色黑色
	setfillcolor(RED);	//填充颜色
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
	food.flag = 1;

}
void eatFood()
{
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{
		snake.num ++ ;
		food.eatgrade += 10;
		food.flag = 0;
	}
	
}
void snakeDie()
{
	for (int i = 3; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
			break;
	}
}

