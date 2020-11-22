#include "Snack.h"

Snack::Snack(node head,int K,int w,int h)
	:nodeSize(K),winW(w),winH(h)
{
	for (int i = 0; i < 5; i++)
		s.push_back( { head.x - nodeSize * i ,head.y });
	headDir = Dir::Right;
	food.x = rand() % winW;
	food.y = rand() % winH;
}
bool Snack::move()
{
		node newhead = s.front();
		switch (headDir)
		{
		case Dir::Stop:
			// do nothing
			return false;
			break;
		case Dir::Up:
			newhead.y -= nodeSize;
			break;
		case Dir::Right:
			newhead.x += nodeSize;
			break;
		case Dir::Down:
			newhead.y += nodeSize;
			break;
		case Dir::Left:
			newhead.x -= nodeSize;
			break;
		default:
			break;
		}
		for (auto i = s.begin(); i != s.end(); i++)
		{
			if ((*i).x == newhead.x)
				if ((*i).y == newhead.y)
					return false;
		}
		if (newhead.x < 0) return false;
		if (newhead.y < 0) return false;
		if (newhead.x > winW) return false;
		if (newhead.y > winH) return false;
		bool falg = false;
		if ((newhead.x - food.x) * (newhead.x - food.x) < nodeSize * nodeSize * 2)
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
	
		s.push_front(newhead);
		if (!falg)
			s.pop_back();
		return true;
}
