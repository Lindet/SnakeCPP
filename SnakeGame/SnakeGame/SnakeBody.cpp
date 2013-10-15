#include "SnakeBody.h"

SnakeBody::SnakeBody(void)
{
	for(int i = 0; i<9; i++)
	{
		SnakeDirection.push_back(std::make_pair(300.f+10*i,200.f));
	}
	dead = false;
	head = 3;
}

void SnakeBody::Move()
{
	for(int i =  SnakeDirection.size()-1; i > 0; i--)
	{
		SnakeDirection[i] = SnakeDirection[i-1];
	}
	switch(head)
	{
		case 1:
			if(SnakeDirection[0].first == 570)	SnakeDirection[0].first = 10;
			else	SnakeDirection[0].first = SnakeDirection[0].first+10.f;
			break;
		case 2:
			if(SnakeDirection[0].second == 450)	SnakeDirection[0].second = 10;
			else	SnakeDirection[0].second = SnakeDirection[0].second+10.f;
			break;
		case 3:
			if(SnakeDirection[0].first == 10)	SnakeDirection[0].first = 570;
			else	SnakeDirection[0].first = SnakeDirection[0].first-10.f;
			break;
		case 4:
			if(SnakeDirection[0].second == 10)	SnakeDirection[0].second = 450;
			else	SnakeDirection[0].second = SnakeDirection[0].second-10.f;
			break;
	}
}

