#include"Snack.h"
#include<graphics.h>
#include<ctime>
#include<conio.h>//��������
const int winW = 640;
const int winH = 480;
void init_game();
void draw_snack(Snack snack);//������
Dir keyPro(char c);
int main(int arg, char* argv[])
{
	initgraph(winW, winH);//��ʼ����ͼ����
	init_game();
	Snack s = Snack(node{ 200,200 }, 10, winW, winH);
	draw_snack(s);
	while (true)
	{
		//ѭ����Ϸ
		while (!_kbhit()) {
			s.move();
			draw_snack(s);

			Sleep(100);
			cleardevice();
		}
		char c = _getch();
		s.headDir = keyPro(c);
	}
	_getch();
	return 0;
}
Dir keyPro(char c)
{
	switch (c)
	{
	case 'w':
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
void init_game()
{
	srand(time(nullptr));//������������ӣ�����ʳ������
	setbkcolor(RGB(128, 128, 64));
}
void draw_snack(Snack snack)
{
	
	for (auto i = snack.s.begin(); i != snack.s.end(); i++)
	{
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		fillcircle((*i).x, (*i).y, snack.nodeSize);
	}
	fillcircle(snack.food.x, snack.food.y, snack.nodeSize);
}