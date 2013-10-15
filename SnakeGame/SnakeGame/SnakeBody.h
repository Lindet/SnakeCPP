#pragma once
#include <vector>
#include <utility>

class SnakeBody
{
public:
	SnakeBody(void);
	bool dead;
	std::vector<std::pair<float,float>> SnakeDirection;
	int head;
	void Move();
};

