#include<graphics.h>//一个简单的绘图库
#include<ctime>//时间
#include<conio.h>//按键处理
#define maxNode 100
#define winW 640
#define winH 480
#define nodeSize 10
struct node
{
	int x;
	int y;
};
enum Dir
{
	Stop =0,Up,Right,Down,Left
};
typedef struct node node;
//蛇的一节
node food;//随机
//食物
node snack[maxNode];
//蛇
node head;
Dir headDir;//蛇头前进方向
int snackLen = 0;
//点继承 ，只需要蛇头方向
void init_game();
void init_snack(node head);
bool move_snack();//移动蛇
void draw_snack();//绘制蛇
Dir keyPro(char c);//按键处理
int main(int arg,char * argv[])
{
	initgraph(winW, winH);//初始化绘图窗口
	init_game();
	init_snack(node{ 200,200 });//初始化蛇
	draw_snack();
	while (true)
	{
		//循环游戏
		while (!_kbhit()) {
			move_snack();
			draw_snack();
			Sleep(100);
			cleardevice();
		}
		char c = _getch();
		headDir = keyPro(c);
	}
	_getch();
	return 0;
}
void init_game()
{
	srand(time(nullptr));//设置随机数种子，用于食物生成
	food.x = rand() % winW;
	food.y = rand() % winH;
}
void init_snack(node head)
{
	//初始化一个 五节蛇
	//方向  右
	for (int i = 0; i < 5; i++)
	{
		snack[i] = { head.x - nodeSize * i ,head.y };
	}snackLen = 5;
	headDir = Dir::Right;

}
void draw_snack()
{
    fillcircle(food.x, food.y, nodeSize);
	for (int i = 0; i < snackLen; i++)
	{
		fillcircle(snack[i].x, snack[i].y, nodeSize);
	}
}
bool move_snack()
{
	node newhead = snack[0];
	switch (headDir)
	{
	case Stop:
		// do nothing
		return false;
		break;
	case Up:
		newhead.y -= nodeSize;
		break;
	case Right:
		newhead.x += nodeSize;
		break;
	case Down:
		newhead.y += nodeSize;
		break;
	case Left:
		newhead.x -= nodeSize;
		break;
	default:
		break;
	}
	//新头生成，是否撞到身子 或者墙？

	for (int i = 1; i < snackLen; i++)
	{
		if(snack[i].x ==newhead.x)
		{
			if (snack[i].y == newhead.y)
			{
				return false;
			}
		}
	}
	if (newhead.x < 0) return false;
	if (newhead.y < 0) return false;
	if (newhead.x > winW) return false;
	if (newhead.y > winH) return false;
	//撞墙

	//撞食物？
	bool falg = false;
	if ((newhead.x -food.x)* (newhead.x - food.x)<nodeSize*nodeSize*2)
	{
		if ((newhead.y - food.y) * (newhead.y - food.y) < nodeSize * nodeSize * 2)
		{
			//吃到了加上
			falg = true;
			food.x = rand() % winW;
			food.y = rand() % winH;
			//重新生成一个
		}
	}
	if (falg)
	{
		snack[snackLen] = snack[snackLen - 1];
	}
	
	for (int i = snackLen-1; i >=1; i--)
	{
		snack[i] = snack[i-1];
	}
	snack[0] = newhead;
	if(falg)
	snackLen++;

	return true;
}
Dir keyPro(char c)
{
	switch (c)
	{
	case 'w' :
	case 'W':
		return Dir::Up;
		break;
	case 'd':
	case 'D':
		return Dir::Right;
		break;
	case 's':
	case 'S':
		return Dir::Down;
		break;
	case 'a':
	case 'A':
		return Dir::Left;
			break;
	default:
		break;
	}
}