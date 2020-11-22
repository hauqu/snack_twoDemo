#pragma once
#include<list>
using namespace std;

struct node
{
	int x;
	int y;
};
enum class Dir
{
	Stop = 0, Up, Right, Down, Left
};
class Snack
{
public:
	Snack(node head,int K,int w,int h);
	list<node>s;
	Dir  headDir;
	bool move();

	node food;
	int  nodeSize;
	int winW;
	int winH;
};