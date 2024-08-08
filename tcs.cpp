#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>//sleep
#include<time.h>//�����������
/****************************************************
*		��������
*		������
*		ʳ������
*		
* 
*****************************************************/
//��������
typedef struct pointXY 
{
	int x;
	int y;

}MYPOINT;
//������
struct Snake 
{
	int num;	//�ߵĽ���
	MYPOINT xy[100];	//��
	char position;

}snake;
//ʳ������
struct Food
{
	MYPOINT  fdxy;	//ʳ�������
	int eatgrade;	//�Ե�food�ķ���
	int flag = 0;	//�Ƿ񱻳Ե�
}food;
//�����������
HWND hwnd = NULL;
//����
enum movPosition {right=100,left=97,down=115,up=119};
/****************************************************
*		��ʼ����:  initSnake
*		����:	   drawSnake
*		�ƶ���:    moveSanke
*		��������:  keyDown
*		��ʼ��ʳ��:initFood
*		��ʳ��:    drawFood
*		��ʳ��:    eatFood
*		ײǽ:      snakeDie
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
	hwnd = initgraph(640,480);	//���ڴ�С
	setbkcolor(WHITE);		//������ɫ��ɫ
	
	initSnake();
	initFood();
	drawFood();
	while(1)
	{
		cleardevice();
		
		if (food.flag == 0)//û��ʳ��ʱ�Ż�ʳ��
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
		while (_kbhit())	// �Ƿ��а�������
		{
			keyDown();
		}
		Sleep(100);
	}
	//getchar();	//��ֹ����
	closegraph();
	return 0;
}
void initSnake() 
{
	//��ʼ��ǰ������
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
		setlinecolor(WHITE);	//���α߿��ߵ���ɫ��ɫ
		setfillcolor(GREEN);	//�����ɫ
		fillrectangle(snake.xy[i].x,snake.xy[i].y, snake.xy[i].x+10, snake.xy[i].y+10);
	}
}
void moveSnake()
{
	//���˵�һ�������Ĵ���
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//��һ�ڵĴ���
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
		food.fdxy.x = rand()%64*10;	//10�ı���
		food.fdxy.y = rand()%46*10;
		//ʳ��������ߵ�����
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
	
	setlinecolor(WHITE);	//���α߿��ߵ���ɫ��ɫ
	setfillcolor(RED);	//�����ɫ
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

