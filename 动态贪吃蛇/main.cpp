#include<graphics.h>//һ���򵥵Ļ�ͼ��
#include<ctime>//ʱ��
#include<conio.h>//��������
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
//�ߵ�һ��
node food;//���
//ʳ��
node snack[maxNode];
//��
node head;
Dir headDir;//��ͷǰ������
int snackLen = 0;
//��̳� ��ֻ��Ҫ��ͷ����
void init_game();
void init_snack(node head);
bool move_snack();//�ƶ���
void draw_snack();//������
Dir keyPro(char c);//��������
int main(int arg,char * argv[])
{
	initgraph(winW, winH);//��ʼ����ͼ����
	init_game();
	init_snack(node{ 200,200 });//��ʼ����
	draw_snack();
	while (true)
	{
		//ѭ����Ϸ
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
	srand(time(nullptr));//������������ӣ�����ʳ������
	food.x = rand() % winW;
	food.y = rand() % winH;
}
void init_snack(node head)
{
	//��ʼ��һ�� �����
	//����  ��
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
	//��ͷ���ɣ��Ƿ�ײ������ ����ǽ��

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
	//ײǽ

	//ײʳ�
	bool falg = false;
	if ((newhead.x -food.x)* (newhead.x - food.x)<nodeSize*nodeSize*2)
	{
		if ((newhead.y - food.y) * (newhead.y - food.y) < nodeSize * nodeSize * 2)
		{
			//�Ե��˼���
			falg = true;
			food.x = rand() % winW;
			food.y = rand() % winH;
			//��������һ��
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